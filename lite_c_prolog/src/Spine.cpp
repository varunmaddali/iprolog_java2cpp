#include "Spine.h"




Spine::Spine(std::vector<int> const & gs0, int base, IntList * gs, int ttop, int k, std::vector<int> * cs)
	: hd(gs0[0]), base(base), ttop(ttop), k(k), cs(cs), notOurs(gs)
{

	IntList* i = IntList::app(gs0, gs);
	this->gs = IntList::tail(i);
	delete i;

}

Spine::Spine(int hd, int ttop)
	: hd(hd), base(0), gs(nullptr), ttop(ttop), k(-1), notOurs(nullptr)
{

}

Spine::~Spine()
{
   IntList* tmp;
   while (gs != nullptr && gs != notOurs)
   {
      tmp = IntList::tail(gs);
      delete gs;
      gs = tmp;
   }
}
