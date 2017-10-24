//.h file code:

#include <string>
#include <vector>

namespace iProlog
{
	class IntList
	{

  private:
//JAVA TO C++ CONVERTER NOTE: Fields cannot have the same name as methods:
	  const int head_Renamed;
//JAVA TO C++ CONVERTER NOTE: Fields cannot have the same name as methods:
	  IntList *const tail_Renamed;

  public:
	  virtual ~IntList()
	  {
		  delete tail;
	  }

  private:
	  IntList(int const head);

	  IntList(int const X, IntList *const Xs);

  public:
	  static bool isEmpty(IntList *const Xs);

	  static int head(IntList *const Xs);

	  static constexpr IntList *empty = nullptr;

	  static IntList *tail(IntList *const Xs);

	  static IntList *cons(int const X, IntList *const Xs);

	  static IntList *app(std::vector<int> &xs, IntList *const Ys);

	  static IntStack *toInts(IntList *Xs);

	  static int len(IntList *const Xs);

	  std::wstring toString() override;
	};
}

//.cpp file code:

namespace iProlog
{

	IntList::IntList(int const head) : head(head), tail(nullptr)
	{
	}

	IntList::IntList(int const X, IntList *const Xs) : head(X), tail(Xs)
	{
	}

	bool IntList::isEmpty(IntList *const Xs)
	{
	  return nullptr == Xs;
	}

	int IntList::head(IntList *const Xs)
	{
	  return Xs->head_Renamed;
	}

	IntList *IntList::tail(IntList *const Xs)
	{
	  return Xs->tail_Renamed;
	}

	IntList *IntList::cons(int const X, IntList *const Xs)
	{
	  return new IntList(X, Xs);
	}

	IntList *IntList::app(std::vector<int> &xs, IntList *const Ys)
	{
	  IntList *Zs = Ys;
	  for (int i = xs.size() - 1; i >= 0; i--)
	  {
		Zs = cons(xs[i], Zs);
	  }
	  return Zs;
	}

	IntStack *IntList::toInts(IntList *Xs)
	{
	  IntStack * const is = new IntStack();
	  while (!isEmpty(Xs))
	  {
		is->push(head(Xs));
		Xs = tail(Xs);
	  }
	  return is;
	}

	int IntList::len(IntList *const Xs)
	{
	  return toInts(Xs)->size();
	}

	std::wstring IntList::toString()
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	  return toInts(this)->toString();
	}
}
