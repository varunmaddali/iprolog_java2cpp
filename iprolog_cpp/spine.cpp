#include <vector>

namespace iProlog
{
	class Spine
	{
  public:
	  virtual ~Spine()
	  {
		  delete gs;
	  }

	  Spine(std::vector<int> &gs0, int const base, IntList *const gs, int const ttop, int const k, std::vector<int> &cs);
	  Spine(int const hd, int const ttop);

	  const int hd; 
	  const int base; 

	  IntList *const gs; 
	  const int ttop; 

	  int k = 0;

	  std::vector<int> xs; 
	  std::vector<int> cs; 
	};
}


namespace iProlog
{

	Spine::Spine(std::vector<int> &gs0, int const base, IntList *const gs, int const ttop, int const k, std::vector<int> &cs) : hd(gs0[0]), base(base), gs(IntList::tail(IntList::app(gs0, gs))) / * prepends the goals of clause with head hs */, ttop(ttop)
	{
	  this->k = k;
	  this->cs = cs;
	}

	Spine::Spine(int const hd, int const ttop) : hd(hd), base(0), gs(IntList::empty), ttop(ttop)
	{

	  k = -1;
	  cs.clear();
	}
}
