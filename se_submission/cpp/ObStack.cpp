
#include<iostream>
#include <vector>

template<typename T>
	class ObStack : public std::vector<T>
	{

  private:
	//  static long serialVersionUID = 1LL;

  public:
	  T pop() //removing elements from the stack
	  {
		int last = this->size() - 1;
		return this->remove(last);
	  }

	  void push(T const O) //inserting elements from the stack
	  {
		this->push_back(O);
	  }

	  T peek()
	  {
		return this->at(this->size() - 1);
	  }
	};

int main()
{
ObStack <int>o; //defining a variable of obstack of type integer
o.push(5); //inserting values
std::cout<<o.peek()<<std::endl; //displaying
o.push(6); //inserting values
std::cout<<o.peek()<<std::endl; //displaying
}


