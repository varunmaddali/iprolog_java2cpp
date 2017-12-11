#include "IntStack.h"



IntStack::IntStack()
{
	stack.reserve(SIZE);
}

IntStack::IntStack(const int size)
{
   stack.reserve(size);
}

IntStack::~IntStack()
{
}



int IntStack::getTop()
{
   return (int)stack.size()-1;
}
void IntStack::clear()
{
	top = -1;
   stack.clear();
}

bool IntStack::isEmpty()
{
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
   return stack;
}


