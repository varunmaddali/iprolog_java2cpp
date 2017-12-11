#include "Engine.h"

#include <iostream>
#include <sstream>
#include <map>

#include "Toks.h"


Engine::Engine(std::string fname)
{
	makeHeap();
	clauses = dload(fname);
	cls = toNums(clauses);
	query = init();
	vmaps = vcreate(MAXIND);
	imaps = index(clauses, vmaps);
}


Engine::~Engine()
{
   delete query;
   delete cls;
   delete clauses;
   for(auto m : *vmaps)
      delete m;

   delete vmaps;
}

int Engine::addSym(std::string sym)
{
	auto it = syms.find(sym);
	if (it == syms.end())
	{
		int i = (int)syms.size();
		syms[sym] = i;
		slist.push_back(sym);
		return i;
	}
	return it->second;
}

std::string Engine::getSym(int w)
{
	if (w < 0 || w >= (int)slist.size())
		return std::string("BADSYMREF=") + std::to_string(w);
	return slist[w];
}

void Engine::expand()
{
	int l = (int)heap.size();
	heap.resize(l << 1);
}

std::vector<std::vector<std::string>*>* Engine::maybeExpand(std::vector<std::string>& Ws)
{
	std::string W = Ws[0];
	if (W.size() < 2 || W.substr(0, 2) != std::string("l:"))
		return nullptr;
	int l = (int)Ws.size();
	std::vector<std::vector<std::string>*>* Rss = new std::vector<std::vector<std::string>*>();
	std::string V = W.substr(2);
	for (int i = 1; i < l; i++)
	{
		std::vector<std::string>* Rs = new std::vector<std::string>();
		std::string Vi = (1 == i) ? V : V + "__" + std::to_string(i - 1);
		std::string Vii = V + "__" + std::to_string(i);
		Rs->push_back(std::string("h:") + Vi);
		Rs->push_back("c:list");
		Rs->push_back(Ws[i]);
		Rs->push_back((i == l - 1) ? "c:nil" : std::string("v:") + Vii);
		Rss->push_back(Rs);
	}
	return Rss;
}

std::vector<std::vector<std::string>*>* Engine::mapExpand(std::vector<std::vector<std::string>*>& Wss)
{
	std::vector<std::vector<std::string>*>* Rss = new std::vector<std::vector<std::string>*>();
	for (auto Ws : Wss)
	{
		auto Hss = maybeExpand(*Ws);
		if (Hss == nullptr)
		{
			std::vector<std::string>* ws = new std::vector<std::string>();
			for (unsigned int i = 0; i < Ws->size(); i++)
				ws->push_back((*Ws)[i]);
			Rss->push_back(ws);
		}
		else
		{
			for (auto X : *Hss)
				Rss->push_back(X);
		}
	}
	return Rss;
}

std::vector<Clause>* Engine::dload(std::string s)
{
	bool fromFile = true;
	auto Wsss = Toks::toSentences(s, fromFile);

	std::vector<Clause> Cs;

	for (auto Wss : Wsss)
	{
		// clause starts here

		std::map<std::string, IntStack*> refs;
		IntStack cs;
		IntStack gs;

		std::vector<std::vector<std::string>*>* Rss = mapExpand(*Wss);

      for(auto Ws : *Wss)
         delete Ws;
      delete Wss;



		int k = 0;

		for (std::vector<std::string>* ws : *Rss)
		{
			// head or body element starts here


			int l = (int)ws->size();
			gs.push(tag(R, k++));
			cs.push(tag(A, l));

			IntStack* Is;

			for (std::string w : *ws)
			{
				// head or body subterm starts here

				if (1 == w.length()) {
					w = std::string("c:") + w;
				}

				std::string L = w.substr(2);

				switch (w[0])
				{
				case 'c':
					cs.push(encode(C, L));
					k++;
					break;
				case 'n':
					cs.push(encode(N, L));
					k++;
					break;
				case 'v':
					Is = refs[L];
					if (nullptr == Is) {
						Is = new IntStack();
						refs[L] = Is;
					}
					Is->push(k);
					cs.push(tag(BAD, k)); // just in case we miss this
					k++;
					Is = nullptr;
					break;
				case 'h':
					Is = refs[L];
					if (nullptr == Is) {
						Is = new IntStack();
						refs[L] = Is;
					}
					Is->push(k - 1);
					cs.set(k - 1, tag(A, l - 1));
					gs.pop();
					Is = nullptr;
					break;
				default:
					std::cout << "FORGOTTEN=" << w << std::endl;
				} // end subterm
			} // end element
		} // end clause

	  // linker
		std::map<std::string, IntStack*>::iterator it;
		for (it = refs.begin(); it != refs.end(); it++)
		{
			IntStack* Is = it->second;

			int leader = -1;
			for (int j : Is->toArray()) {
				if (A == tagOf(cs.get(j))) {
					leader = j;

					break;
				}
			}
			if (-1 == leader) {
				// for vars, first V others U
				leader = Is->get(0);
				for (int i : Is->toArray()) {
					if (i == leader) {
						cs.set(i, tag(V, i));
					}
					else {
						cs.set(i, tag(U, leader));
					}
				}
			}
			else
			{
				for (int i : Is->toArray()) {
					if (i == leader) {
						continue;
					}
					cs.set(i, tag(R, leader));
				}
			}
		}
		

		int neck = 1 == gs.size() ? cs.size() : detag(gs.get(1));
		std::vector<int> tgs = gs.toArray();

		Clause C = putClause(cs.toArray(), tgs, neck);

		Cs.push_back(C);

		for (auto it = refs.begin(); it != refs.end(); it++)
			delete it->second;
		for (unsigned int i = 0; i < Rss->size(); i++)
			delete (*Rss)[i];
		delete Rss;
	} // end clause set
	
	int ccount = (int)Cs.size();
	std::vector<Clause>* cls = new std::vector<Clause>();
	for (int i = 0; i < ccount; i++) {
		cls->push_back(Cs[i]);
	}



	return cls;
}

std::vector<int>* Engine::toNums(std::vector<Clause>* clauses)
{
	int l = (int)clauses->size();
	std::vector<int>* cls = new std::vector<int>();
	for (int i = 0; i < l; i++)
		cls->push_back(i);
	return cls;
}

int Engine::encode(int t, std::string s)
{
	int w;
	try {
		w = std::stoi(s);
	}
	catch (...)
	{
		if (C == t)
			w = addSym(s);
		else
			return tag(BAD, 666);
	}

	return tag(t, w);
}

int Engine::deref(int x)
{
	while (isVAR(x)) {
		int r = getRef(x);
		if (r == x) {
			break;
		}
		x = r;
	}
	return x;
}

std::string Engine::showTerm(Object O)
{
	return O.toString();
}

Object Engine::exportTerm(int x)
{
	x = deref(x);

	int t = tagOf(x);
	int w = detag(x);

	switch (t) {
	case C:
		return getSym(w);
		break;
	case N:
		return w;
		break;
	case V:
		//case U:
		return std::string("V") + std::to_string(w);
		break;
	case R: {

		int a = heap[w];
		if (A != tagOf(a))
			return std::string("*** should be A, found=") + showCell(a);
		int n = detag(a);
		std::vector<Object> arr;
		int k = w + 1;
		for (int i = 0; i < n; i++) {
			int j = k + i;
			arr.push_back(exportTerm(heap[j]));
		}
		return arr;
	}
			break;
	default:
		return std::string("*BAD TERM*") + showCell(x);
	}
}

std::vector<int>* Engine::getSpine(std::vector<int>& cs)
{
	int a = cs[1];
	int w = detag(a);
	std::vector<int>* rs = new std::vector<int>(w - 1);
	for (int i = 0; i < w - 1; i++) {
		int x = cs[3 + i];
		int t = tagOf(x);
		if (R != t) {
			std::cout<< "*** getSpine: unexpected tag=" << t << std::endl;
			return nullptr;
		}
		(*rs)[i] = detag(x);
	}
	return rs;
}

std::string Engine::showCell(int w)
{
	int t = tagOf(w);
	int val = detag(w);
	std::string s;

	switch (t) {
	case V:
		s = std::string("v:") + std::to_string(val);
		break;
	case U:
		s = std::string("u:") + std::to_string(val);
		break;
	case N:
		s = std::string("n:") + std::to_string(val);
		break;
	case C:
		s = std::string("c:") + getSym(val);
		break;
	case R:
		s = std::string("r:") + std::to_string(val);
		break;
	case A:
		s = std::string("a:") + std::to_string(val);
		break;
	default:
		s = std::string("*BAD*=") + std::to_string(w);
	}
	return s;
}

std::string Engine::showCells(int base, int len)
{
	std::ostringstream buf;
	for (int k = 0; k < len; k++)
	{
		int instr = heap[base + k];
		buf << "[" << base + k << "]";
		buf << showCell(instr);
		buf << " ";
	}
	return buf.str();
}

bool Engine::unify(int base)
{
	while (!ustack.isEmpty()) {
		int x1 = deref(ustack.pop());
		int x2 = deref(ustack.pop());
		if (x1 != x2) {
			int t1 = tagOf(x1);
			int t2 = tagOf(x2);
			int w1 = detag(x1);
			int w2 = detag(x2);

			if (isVAR(x1)) { /* unb. var. v1 */
				if (isVAR(x2) && w2 > w1) { /* unb. var. v2 */
					heap[w2] = x1;
					if (w2 <= base) {
						trail.push(x2);
					}
				}
				else { // x2 nonvar or older
					heap[w1] = x2;
					if (w1 <= base) {
						trail.push(x1);
					}
				}
			}
			else if (isVAR(x2)) { /* x1 is NONVAR */
				heap[w2] = x1;
				if (w2 <= base) {
					trail.push(x2);
				}
			}
			else if (R == t1 && R == t2) { // both should be R
				if (!unify_args(w1, w2))
					return false;
			}
			else
				return false;
		}
	}
	return true;
}

bool Engine::unify_args(int w1, int w2)
{
	int v1 = heap[w1];
	int v2 = heap[w2];
	// both should be A
	int n1 = detag(v1);
	int n2 = detag(v2);
	if (n1 != n2)
		return false;


   int b1 = 1 + w1;
	int b2 = 1 + w2;
	for (int i = n1 - 1; i >= 0; i--) {
      int i1 = b1 + i;
		int i2 = b2 + i;
		int u1 = heap[i1];
		int u2 = heap[i2];
		if (u1 == u2) {
         continue;
		}
		ustack.push(u2);
		ustack.push(u1);
	}
	return true;
}

Clause Engine::putClause(std::vector<int> cs, std::vector<int>& gs, int neck)
{
	int base = size();
	int b = tag(V, base);
	int len = (int)cs.size();
	pushCells(b, 0, len, cs);
	for (unsigned int i = 0; i < gs.size(); i++) {
		gs[i] = relocate(b, gs[i]);
	}
	std::vector<int>* pxs = getIndexables(gs[0]);
	std::vector<int> xs(*pxs);
	delete pxs;
	return Clause(len, gs, base, neck, xs);
}

void Engine::pushCells(int b, int from, int to, int base)
{
	ensureSize(to - from);
	for (int i = from; i < to; i++) {
		push(relocate(b, heap[base + i]));
	}
}

void Engine::pushCells(int b, int from, int to, std::vector<int>& cs)
{
	ensureSize(to - from);
	for (int i = from; i < to; i++) {
		push(relocate(b, cs[i]));
	}
}

int Engine::pushHead(int b, Clause & C)
{
	pushCells(b, 0, C.neck, C.base);
	int head = C.hgs[0];
	return relocate(b, head);
}

std::vector<int>* Engine::pushBody(int b, int head, Clause& C)
{
	pushCells(b, C.neck, C.len, C.base);
	int l = (int)C.hgs.size();
	std::vector<int>* gs = new std::vector<int>(l);
	(*gs)[0] = head;
	for (int k = 1; k < l; k++) {
		int cell = C.hgs[k];
		(*gs)[k] = relocate(b, cell);
	}
	return gs;
}

void Engine::makeIndexArgs(Spine & G, int goal)
{
	if (!G.xs.empty())
		return;

	int p = 1 + detag(goal);
	int n = std::min(MAXIND, detag(getRef(goal)));

//	std::vector<int> xs(MAXIND);
   G.xs.reserve(MAXIND);
	for (int i = 0; i < n; i++) {
		int cell = deref(heap[p + i]);
//		xs[i] = cell2index(cell);
      G.xs.push_back(cell2index(cell));
   }

//	G.xs = xs;

	if (nullptr == imaps)
		return;
	std::vector<int> cs = IMap<int>::get(imaps, vmaps, G.xs);
   G.cs = new std::vector<int>(cs);

}

std::vector<int>* Engine::getIndexables(int ref)
{
	int p = 1 + detag(ref);
	int n = detag(getRef(ref));
	std::vector<int>* xs = new std::vector<int>(MAXIND);
	for (int i = 0; i < MAXIND && i < n; i++) {
		int cell = deref(heap[p + i]);
		(*xs)[i] = cell2index(cell);
	}
	return xs;
}

int Engine::cell2index(int cell)
{
	int x = 0;
	int t = tagOf(cell);
	switch (t) {
	case R:
		x = getRef(cell);
		break;
	case C:
	case N:
		x = cell;
		break;
		// 0 otherwise - assert: tagging with R,C,N <>0
	}
	return x;
}


bool Engine::match(std::vector<int>& xs, Clause & C0)
{
   int tot = std::min((int)xs.size(), (int)MAXIND);
   tot = std::min(tot, (int)C0.xs.size());

//	for (int i = 0; i < MAXIND; i++) {
   for (int i = 0 ; i < tot ; i++) {
      int x = xs[i];
		int y = C0.xs[i];
		if (0 == x || 0 == y) {
			continue;
		}
		if (x != y)
			return false;
	}
	return true;
}

Spine * Engine::unfold(Spine& G)
{
	int ttop = trail.getTop();
	int htop = getTop();
	int base = htop + 1;

	int goal = IntList::head(G.gs);

	makeIndexArgs(G, goal);

	int last = (int)G.cs->size();
	for (int k = G.k; k < last; k++) {
		Clause* C0 = &(*clauses)[(*G.cs)[k]];

		if (!match(G.xs, *C0))
			continue;

		int base0 = base - C0->base;
		int b = tag(V, base0);
		int head = pushHead(b, *C0);

		ustack.clear(); // set up unification stack

		ustack.push(head);
		ustack.push(goal);

		if (!unify(base)) {
			unwindTrail(ttop);
			setTop(htop);
			continue;
		}
		std::vector<int>* gs = pushBody(b, head, *C0);
      IntList* tmp = IntList::app(*gs, IntList::tail(G.gs));
      IntList* newgs = IntList::tail(tmp);
      //		IntList* newgs = IntList::tail(IntList::app(*gs, IntList::tail(G.gs)));
		G.k = k + 1;
      bool isEmpty = IntList::isEmpty(newgs);


      IntList* notOurs = IntList::tail(G.gs);
      
      while(tmp != notOurs)
      {
         IntList* tmp2 = IntList::tail(tmp);
         delete tmp;
         tmp = tmp2;
      }



      if (!isEmpty)
      {
			Spine* ret = new Spine(*gs, base, IntList::tail(G.gs), ttop, 0, cls);
         delete gs;
         return ret;
      }
		else
      {
         delete gs;
			return answer(ttop);
      }
	} // end for
	return nullptr;
}

Spine * Engine::init()
{
	int base = size();

	Clause* G = getQuery();
	Spine* Q = new Spine(G->hgs, base, nullptr, trail.getTop(), 0, cls);
	spines.push(Q);
   return nullptr;
   return Q;
}

void Engine::popSpine()
{
	Spine* G = spines.pop();
	unwindTrail(G->ttop);
	setTop(G->base - 1);
   delete G;
}

Spine * Engine::yield()
{
//   int iter = 0	;
	while (!spines.empty()) {
//      iter++;
//      if(iter % 1000000 == 0)
//      std::cout << iter/1000000 << "M: " << spines.size() << std::endl;
		Spine* G = spines.peek();
		if (!hasClauses(*G)) {
			popSpine(); // no clauses left
			continue;
		}
		Spine* C = unfold(*G);
		if (nullptr == C) {
			popSpine(); // no matches
			continue;
		}
		if (hasGoals(*C)) {
			spines.push(C);
			continue;
		}
		return C; // answer
	}
	return nullptr;
}

Object Engine::ask()
{
   if(query != nullptr)
      delete query;
	query = yield();
	if (query == nullptr)
		return Object();

   Spine* tmp = answer(query->ttop);
	int res = tmp->hd;
   delete tmp;

   Object R = exportTermFlag_? exportTerm(res) : Object("Not Displayable!");
	unwindTrail(query->ttop);
   return R;
}



void Engine::run()
{
	long ctr = 0L;
	for (;; ctr++) {
		Object A = ask();
		if (A.isNull()) {
			break;
		}
		if (ctr<5)
			std::cout << "[" << ctr << "] " << "*** ANSWER=" << showTerm(A) << std::endl;
      else
         exportTermFlag_ = false;
	}
	if (ctr > 5)
		std::cout << "..." << std::endl;
	std::cout << "TOTAL ANSWERS=" << ctr << std::endl;
}

std::vector<IntMap*>* Engine::vcreate(int l)
{
	std::vector<IntMap*>* vss = new std::vector<IntMap*>(l);
	for (int i = 0; i < l; i++) {
		(*vss)[i] = new IntMap();
	}
	return vss;
}

void Engine::put(std::vector<IMap<int>*>* imaps, std::vector<IntMap*>* vss, std::vector<int>* keys, int val)
{
	for (unsigned int i = 0; i < imaps->size(); i++) {
		int key = (*keys)[i];
		if (key != 0) {
			IMap<int>::put(imaps, i, key, val);
		}
		else {
			(*vss)[i]->add(val);
		}
	}
}

std::vector<IMap<int>*>* Engine::index(std::vector<Clause>* clauses, std::vector<IntMap*>* vmaps)
{
	if (clauses->size() < START_INDEX)
		return nullptr;

	std::vector<IMap<int>*>* imaps = IMap<int>::create((int)vmaps->size());
	for (unsigned int i = 0; i < clauses->size(); i++) {
		Clause c = (*clauses)[i];

		put(imaps, vmaps, &(c.xs), i + 1); // $$$ UGLY INC

	}
	return imaps;
}


const int Engine::MAXIND;




