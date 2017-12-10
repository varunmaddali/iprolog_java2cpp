#include "ObStack.h"
#include "IMap.h"
#include "Toks.h"
#include "Object.h"
#include "Engine.h"


#include <iostream>


bool testToks(std::string fname)
{
	std::cout << "Testing Toks class." << std::endl;
	std::string ref = "[[[c:eq, v:X, v:X]], [[c:sel, v:X, v:_0, v:Xs], [h:_0, c:list, v:X, v:Xs]], [[c:sel, v:X, v:_0, v:_1], [h:_0, c:list, v:Y, v:Xs], [h:_1, c:list, v:Y, v:Ys], [c:sel, v:X, v:Xs, v:Ys]], [[c:perm, c:nil, c:nil]], [[c:perm, v:_0, v:Zs], [h:_0, c:list, v:X, v:Xs], [c:perm, v:Xs, v:Ys], [c:sel, v:X, v:Zs, v:Ys]], [[c:app, c:nil, v:Xs, v:Xs]], [[c:app, v:_0, v:Ys, v:_1], [h:_0, c:list, v:X, v:Xs], [h:_1, c:list, v:X, v:Zs], [c:app, v:Xs, v:Ys, v:Zs]], [[c:nrev, c:nil, c:nil]], [[c:nrev, v:_0, v:Zs], [h:_0, c:list, v:X, v:Xs], [c:nrev, v:Xs, v:Ys], [c:app, v:Ys, v:_1, v:Zs], [l:_1, v:X]], [[c:input, v:_0], [l:_0, n:1, n:2, n:3, n:4, n:5, n:6, n:7, n:8, n:9, n:10, n:11]], [[c:goal, v:Y], [c:input, v:X], [c:nrev, v:X, v:Y], [c:perm, v:X, v:Y], [c:perm, v:Y, v:X]]]";
	std::string res = Toks::toString(Toks::toSentences(fname, true));
	
	if (res == ref)
	{
		std::cout << "Passed!" << std::endl;
		return true;
	}
	std::cout << "Failed!" << std::endl;
	return false;
}


void run(std::string fname)
{
	Engine P(fname);

	std::cout << "RUNNING..." << std::endl;

   std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


	P.run();
   std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
   std::cout << "Time = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 <<std::endl;

}



int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cout << "Usage: cProlog <program_file_name>" << std::endl;
      return 0;
   }
	
	run(argv[1]);
	return 0;
}

