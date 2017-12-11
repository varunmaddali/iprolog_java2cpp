#include "IntList.h"




IntList::IntList(const int head)
	:	head_(head), tail_(nullptr)
{
}

IntList::IntList(const int head, IntList* tail)
	: head_(head), tail_(tail)
{
}

IntList::~IntList()
{
}

bool IntList::isEmpty(const IntList * Xs)
{
	return Xs == nullptr;
}

int IntList::head(const IntList * Xs)
{
	return Xs->head_;
}

IntList * IntList::tail(const IntList * Xs)
{
	return Xs->tail_;
}

IntList * IntList::cons(const int head, IntList * tail)
{
	return new IntList(head, tail);
}

IntList * IntList::app(const std::vector<int>& xs, IntList * Ys)
{
	IntList* Zs = Ys;
	for (int i = (int)xs.size() - 1; i >= 0; i--) {
		Zs = cons(xs[i], Zs);
	}
	return Zs;
}

IntStack IntList::toInts(IntList * Xs)
{
	IntStack is;
	while (!isEmpty(Xs)) {
		is.push(head(Xs));
		Xs = tail(Xs);
	}
	return is;
}

int IntList::len(IntList * Xs)
{
	return toInts(Xs).size();
}
