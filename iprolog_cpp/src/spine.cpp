#include "Spine.h"




Spine::Spine(std::vector<int> const & gs0, int base, IntList * gs, int ttop, int k, std::vector<int> * cs)
	: hd(gs0[0]), base(base), ttop(ttop), k(k), cs(cs)
{

	IntList* i = IntList::app(gs0, gs);
	this->gs = IntList::tail(i);
	delete (i);

}

Spine::Spine(int hd, int ttop)
	: hd(hd), base(0), gs(nullptr), ttop(ttop), k(-1)
{
}

Spine::~Spine()
{
}

