#ifndef __INTSTACK_H__
#define __INTSTACK_H__

#include <vector>

class IntStack
{
public:
	IntStack(); //contructor
	IntStack(const int size); //constructor
	~IntStack(); // destructor
//function declarations
	int getTop(); 
	void clear();
	bool isEmpty();
// function to inserting into stack
   void push(const int i)
   {
//      if (++top >= stacklen)
//         expand();
//      stack[top] = i;
      stack.push_back(i);
   }
   

   int pop()
   {
//      const int r = stack[top--];
//      shrink();
//      return r;
      int r = stack.back();
      stack.pop_back();
      return r;
   }

	int get(const int i);
	void set(const int i, const int val);
	int size();

	void reverse();
	std::vector<int> toArray();

private:
//   int setTop(const int top);
   void expand() // doubling the size of stack when memory is insufficient
   {/*
      const int l = stacklen;
      int* newstack = new int[l << 1];
      for (int i = 0; i < l; ++i)
         newstack[i] = stack[i];
      delete[] stack;
      stack = newstack;
      stacklen = l << 1;
   */
   }
//reducing the size of stack by 2 when there is more space
   void shrink()
   {
      /*
      if (stacklen <= MINSIZE || top << 2 >= stacklen)
         return;
      int l = stacklen;
      l = 1 + (top << 1);		// still means shrink to at 1/2 or less of the heap
      if (top < MINSIZE) {
         l = MINSIZE;
      }
      int* newstack = new int[l];
      for (int i = 0; i < l; ++i)
         newstack[i] = stack[i];
      delete[] stack;
      stack = newstack;
      stacklen = l;
       */
   }
   


	static const int SIZE = 128;
	static const int MINSIZE = 1 << 15;

   std::vector<int> stack;
	int stacklen;
	int top;


};

#endif