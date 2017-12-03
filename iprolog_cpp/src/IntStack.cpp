#include "IntStack.h"

namespace iProlog
{

int IntStack::SIZE = 16;
int IntStack::MINSIZE = 1 << 15;

	IntStack::IntStack() : IntStack(SIZE)
	{
	}

	IntStack::IntStack(int const size)
	{
	  stack = std::vector<int>(size);
	  clear();
	}

	int IntStack::getTop()
	{
	  return top;
	}

	int IntStack::setTop(int const top)
	{
	  return this->top = top;
	}

	void IntStack::clear()
	{
	  top = -1;
	}

	bool IntStack::isEmpty()
	{
	  return top < 0;
	}

	void IntStack::push(int const i)
	{
	  if (++top >= stack.size())
	  {
		expand();
	  }
	  stack[top] = i;
	}

	int IntStack::pop()
	{
	  constexpr int r = stack[top--];
	  shrink();
	  return r;
	}

	int IntStack::get(int const i)
	{
	  return stack[i];
	}

	void IntStack::set(int const i, int const val)
	{
	  stack[i] = val;
	}

	int IntStack::size()
	{
	  return top + 1;
	}

	void IntStack::expand()
	{
	  constexpr int l = stack.size();
	  const std::vector<int> newstack = std::vector<int>(l << 1);

	  System::arraycopy(stack, 0, newstack, 0, l);
	  stack = newstack;
	}

	void IntStack::shrink()
	{
	  int l = stack.size();
	  if (l <= MINSIZE || top << 2 >= l)
	  {
		return;
	  }
	  l = 1 + (top << 1);
	  if (top < MINSIZE)
	  {
		l = MINSIZE;
	  }

	  const std::vector<int> newstack = std::vector<int>(l);
	  System::arraycopy(stack, 0, newstack, 0, top + 1);
	  stack = newstack;
	}

	std::vector<int> IntStack::toArray()
	{
	  const std::vector<int> array_Renamed = std::vector<int>(size());
	  if (size() > 0)
	  {
		System::arraycopy(stack, 0, array_Renamed, 0, size());
	  }
	  return array_Renamed;
	}

	void IntStack::reverse()
	{
	  int l = size();
	  int h = l >> 1;
	  for (int i = 0; i < h; i++)
	  {
		int temp = stack[i];
		stack[i] = stack[l - i - 1];
		stack[l - i - 1] = temp;
	  }
	}

	std::wstring IntStack::toString()
	{
	  return Arrays->toString(toArray());
	}
}
