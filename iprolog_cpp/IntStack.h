#pragma once

#include <string>
#include <vector>

namespace iProlog
{

	class IntStack
	{

  private:
	  std::vector<int> stack;

	  int top = 0;

  public:
	  static int SIZE;

	  static int MINSIZE; 

	  IntStack();

	  IntStack(int const size);

	  int getTop();

	  int setTop(int const top);

	  void clear();

	  bool isEmpty();

	  void push(int const i);

	  int pop();

	  int get(int const i);

	  void set(int const i, int const val);

	  int size();

  private:
	  void expand();

	  void shrink();

  public:
	  virtual std::vector<int> toArray();

	  void reverse();

	  std::wstring toString() override;

	};

}
