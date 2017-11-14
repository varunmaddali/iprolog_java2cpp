
#include<iostream>
#include <vector>

template<typename T>
	class ObStack1 : public std::vector<T>
	{

  private:
	//  static long serialVersionUID = 1LL;

  public:
	  T pop()
	  {
		int last = this->size() - 1;
		return this->remove(last);
	  }

	  void push(T const O)
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
ObStack1 <int>o;
o.push(5);
std::cout<<o.peek()<<std::endl;
o.push(6);
std::cout<<o.peek()<<std::endl;
}


