#include<iostream>
#include <vector>
class random;
int a[15];

template<typename T>
	class ObStack : public std::vector<T>
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
int f= 435,b=786,m=85,i=0;
a[0]=6;
while(i<10)
{
int result=((a[i]*f)*b)%m;
i++;
a[i]=result;
}

ObStack <int>o;
o.push(a[1]);
std::cout<<o.peek()<<std::endl;
o.push(a[2]);
std::cout<<o.peek()<<std::endl;
}