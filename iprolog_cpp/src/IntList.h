#ifndef __INTLIST_H__
#define __INTLIST_H__

#include "IntStack.h"
#include <vector>

class IntList
{
public:
	~IntList();

	static bool isEmpty(const IntList* Xs);
	static int head(const IntList* Xs);
	static IntList* tail(const IntList* Xs);
	static IntList* cons(const int head, IntList* tail);
	static IntList* app(const std::vector<int>& xs, IntList* Ys);
	static IntStack toInts(IntList* Xs);
	static int len(IntList* Xs);





private:
	IntList(const int head);
	IntList(const int head, IntList* tail);


	const int head_;
	IntList* tail_;
};


#endif
