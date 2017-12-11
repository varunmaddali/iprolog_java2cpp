#include "IntStack.h"



IntStack::IntStack()
{
//	stack = new int[SIZE];
//	stacklen = SIZE;
//	clear();
   stack.reserve(SIZE);
}

IntStack::IntStack(const int size)
{
//	stack = new int[size];
//	stacklen = size;
//	clear();
   stack.reserve(size);
}

IntStack::~IntStack()
{
//	delete[] stack;
}



int IntStack::getTop()
{
//	return top;
   return (int)stack.size()-1;
}
/*
int IntStack::setTop(const int top)
{
	this->top = top;
	return this->top;
}
*/
void IntStack::clear()
{
	top = -1;
   stack.clear();
}

bool IntStack::isEmpty()
{
//	return top < 0;
   return stack.empty();
}



int IntStack::get(const int i)
{
	return stack[i];
}

void IntStack::set(const int i, const int val)
{
	stack[i] = val;
}

int IntStack::size()
{
//	return top + 1;
   return (int)stack.size();
}


void IntStack::reverse()
{
	int l = size();
	int h = l >> 1;
	for (int i = 0; i < h; i++) {
		int temp = stack[i];
		stack[i] = stack[l - i - 1];
		stack[l - i - 1] = temp;
	}
}


std::vector<int> IntStack::toArray()
{
//	std::vector<int> V(stack, stack + size());
//	return V;
   return stack;
}


