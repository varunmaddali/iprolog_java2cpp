#include <vector>
#include<iostream>
#include <boost/assign/list_of.hpp>
using namespace std;
int a[15];
class random;
class Clause
{
  public:
Clause(int const len, std::vector<int> *hgs, int const base, int const neck, std::vector<int> *xs);

	  int len;

	  std::vector<int> hgs;
	   int base;
	   int neck;
	  std::vector<int> xs;
void print_values()
{
cout<<"the values are len"<<len<<endl;
cout<<"the values are neck"<<neck<<endl;
cout<<"the values are base"<<base<<endl;
std::copy(hgs.begin(), hgs.end(), std::ostream_iterator<int>(std::cout, " "));
cout<<endl;
std::copy(xs.begin(), xs.end(), std::ostream_iterator<int>(std::cout, " "));

/*for (std::vector<int>::const_iterator i = hgs.begin(); i != hgs.end(); ++i)
{
  cout<<"in loop";
    cout << *i << ' ';
}*/
/*for(int i=0;i<=len-1;i++)
System.out.println("the values are hgs:"+hgs[i]);
System.out.println("the values are base:"+base);
System.out.println("the values are neck:"+neck);
for(int i=0;i<=len-1;i++)
System.out.println("the values are xs:"+xs[i]);
*/

}


};

Clause::Clause(int const len,vector<int> *hgs, int const base, int const neck, vector<int> *xs) 
{
this->len=len;
this->base=base;
this->neck=neck;
this->hgs=*hgs;
this->xs=*xs;
}

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


std::vector<int> r = boost::assign::list_of(a[1])(a[2])(a[3])(a[4])(a[5]);
 Clause c(a[6],&r,a[7],a[8],&r);
 c.print_values();
}