#ifndef __OBSTACK_H__
#define __OBSTACK_H__

#include <vector>

template <typename T> class ObStack : public std::vector<T>
{
public:
	T pop()
	{
		T val = this->back();
		this->pop_back();
		return val;
	}

	void push(T const & val)
	{
		this->push_back(val);
	}

	T peek()
	{
		return this->back();
	}



};

#endif
