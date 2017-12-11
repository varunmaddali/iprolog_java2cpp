#include "ObStack.h"
#include "IMap.h"
#include "Toks.h"
#include "Object.h"
#include "Engine.h"


#include <iostream>
#include <chrono>




bool testToks_show(std::string fname, std::string cppout, std::string javaout)
{
   bool fail = false;
   if(cppout != javaout)
   {
      fail = true;
      int pos = 0;
      unsigned long len = cppout.length();
      if (len > javaout.length())
         len = javaout.length();
      for (int i = 0 ; i < len ; i++)
         if(cppout[i] != javaout[i])
         {
            pos = i;
            break;
         }
      std::cout << fname << " failed: at position " << pos << std::endl;
      std::cout << "c++ : " << cppout << std::endl;
      std::cout << "java: " << javaout << std::endl;
   }
   return !fail;
}

bool testToks()
{
   std::string java_add =     "[[[c:add, n:0, v:X, v:X]], [[c:add, v:_0, v:Y, v:_1], [h:_0, c:s, v:X], [h:_1, c:s, v:Z], [c:add, v:X, v:Y, v:Z]], [[c:goal, v:R], [c:add, v:_0, v:_1, v:R], [h:_0, c:s, v:_2], [h:_2, c:s, n:0], [h:_1, c:s, v:_3], [h:_3, c:s, n:0]]]";
   std::string java_lambdas = "[[[c:genLambda, v:X, v:Vs, v:N, v:N], [c:memb, v:X, v:Vs]], [[c:genLambda, v:_0, v:Vs, v:_1, v:N2], [h:_0, c:l, v:X, v:A], [h:_1, c:s, v:N1], [c:genLambda, v:A, v:_2, v:N1, v:N2], [h:_2, c:list, v:X, v:Vs]], [[c:genLambda, v:_0, v:Vs, v:_1, v:N3], [h:_0, c:a, v:A, v:B], [h:_1, c:s, v:N1], [c:genLambda, v:A, v:Vs, v:N1, v:N2], [c:genLambda, v:B, v:Vs, v:N2, v:N3]], [[c:memb, v:X, v:_0], [h:_0, c:list, v:X, v:_1]], [[c:memb, v:X, v:_0], [h:_0, c:list, v:_1, v:Xs], [c:memb, v:X, v:Xs]], [[c:genClosedLambdaTerm, v:L, v:T], [c:genLambda, v:T, c:nil, v:L, c:zero]], [[c:nine, v:_0], [h:_0, c:s, v:_1], [h:_1, c:s, v:_2], [h:_2, c:s, v:_3], [h:_3, c:s, v:_4], [h:_4, c:s, v:_5], [h:_5, c:s, v:_6], [h:_6, c:s, v:_7], [h:_7, c:s, v:_8], [h:_8, c:s, c:zero]], [[c:goal, v:Lam], [c:nine, v:Size], [c:genClosedLambdaTerm, v:Size, v:Lam]]]";
   std::string java_perms =   "[[[c:eq, v:X, v:X]], [[c:sel, v:X, v:_0, v:Xs], [h:_0, c:list, v:X, v:Xs]], [[c:sel, v:X, v:_0, v:_1], [h:_0, c:list, v:Y, v:Xs], [h:_1, c:list, v:Y, v:Ys], [c:sel, v:X, v:Xs, v:Ys]], [[c:perm, c:nil, c:nil]], [[c:perm, v:_0, v:Zs], [h:_0, c:list, v:X, v:Xs], [c:perm, v:Xs, v:Ys], [c:sel, v:X, v:Zs, v:Ys]], [[c:app, c:nil, v:Xs, v:Xs]], [[c:app, v:_0, v:Ys, v:_1], [h:_0, c:list, v:X, v:Xs], [h:_1, c:list, v:X, v:Zs], [c:app, v:Xs, v:Ys, v:Zs]], [[c:nrev, c:nil, c:nil]], [[c:nrev, v:_0, v:Zs], [h:_0, c:list, v:X, v:Xs], [c:nrev, v:Xs, v:Ys], [c:app, v:Ys, v:_1, v:Zs], [l:_1, v:X]], [[c:input, v:_0], [l:_0, n:1, n:2, n:3, n:4, n:5, n:6, n:7, n:8, n:9, n:10, n:11]], [[c:goal, v:Y], [c:input, v:X], [c:nrev, v:X, v:Y], [c:perm, v:X, v:Y], [c:perm, v:Y, v:X]]]";
   std::string java_queens =  "[[[c:place_queen, v:I, v:_0, v:_1, v:_2], [h:_0, c:list, v:I, v:_3], [h:_1, c:list, v:I, v:_4], [h:_2, c:list, v:I, v:_5]], [[c:place_queen, v:I, v:_0, v:_1, v:_2], [h:_0, c:list, v:_3, v:Cs], [h:_1, c:list, v:_4, v:Us], [h:_2, c:list, v:_5, v:Ds], [c:place_queen, v:I, v:Cs, v:Us, v:Ds]], [[c:place_queens, c:nil, v:_0, v:_1, v:_2]], [[c:place_queens, v:_0, v:Cs, v:Us, v:_1], [h:_0, c:list, v:I, v:Is], [h:_1, c:list, v:_2, v:Ds], [c:place_queens, v:Is, v:Cs, v:_3, v:Ds], [h:_3, c:list, v:_4, v:Us], [c:place_queen, v:I, v:Cs, v:Us, v:Ds]], [[c:gen_places, c:nil, c:nil]], [[c:gen_places, v:_0, v:_1], [h:_0, c:list, v:_2, v:Qs], [h:_1, c:list, v:_3, v:Ps], [c:gen_places, v:Qs, v:Ps]], [[c:qs, v:Qs, v:Ps], [c:gen_places, v:Qs, v:Ps], [c:place_queens, v:Qs, v:Ps, v:_0, v:_1]], [[c:goal, v:Ps], [c:qs, v:_0, v:Ps], [l:_0, n:0, n:1, n:2, n:3, n:4, n:5, n:6, n:7, n:8, n:9, n:10, n:11]]]";
   std::string java_sud4x =   "[[[c:s4x4, v:_0], [l:_0, v:_1, v:_2, v:_3], [l:_1, v:_4, v:_5, v:_6, v:_7], [l:_4, v:S11, v:S12, v:S13, v:S14], [l:_5, v:S21, v:S22, v:S23, v:S24], [l:_6, v:S31, v:S32, v:S33, v:S34], [l:_7, v:S41, v:S42, v:S43, v:S44], [l:_2, v:_8, v:_9, v:_10, v:_11], [l:_8, v:S11, v:S21, v:S31, v:S41], [l:_9, v:S12, v:S22, v:S32, v:S42], [l:_10, v:S13, v:S23, v:S33, v:S43], [l:_11, v:S14, v:S24, v:S34, v:S44], [l:_3, v:_12, v:_13, v:_14, v:_15], [l:_12, v:S11, v:S12, v:S21, v:S22], [l:_13, v:S13, v:S14, v:S23, v:S24], [l:_14, v:S31, v:S32, v:S41, v:S42], [l:_15, v:S33, v:S34, v:S43, v:S44]], [[c:sudoku, v:Xss], [c:s4x4, v:_0], [h:_0, c:list, v:Xss, v:Xsss], [c:map11, c:permute, v:_1, v:_2], [l:_1, n:1, n:2, n:3, n:4], [h:_2, c:list, v:Xss, v:Xsss]], [[c:map1x, v:_0, v:_1, c:nil]], [[c:map1x, v:F, v:Y, v:_0], [h:_0, c:list, v:X, v:Xs], [v:F, v:Y, v:X], [c:map1x, v:F, v:Y, v:Xs]], [[c:map11, v:_0, v:_1, c:nil]], [[c:map11, v:F, v:X, v:_0], [h:_0, c:list, v:Y, v:Ys], [c:map1x, v:F, v:X, v:Y], [c:map11, v:F, v:X, v:Ys]], [[c:permute, c:nil, c:nil]], [[c:permute, v:_0, v:Zs], [h:_0, c:list, v:X, v:Xs], [c:permute, v:Xs, v:Ys], [c:ins, v:X, v:Ys, v:Zs]], [[c:ins, v:X, v:Xs, v:_0], [h:_0, c:list, v:X, v:Xs]], [[c:ins, v:X, v:_0, v:_1], [h:_0, c:list, v:Y, v:Xs], [h:_1, c:list, v:Y, v:Ys], [c:ins, v:X, v:Xs, v:Ys]], [[c:goal, v:Xss], [c:sudoku, v:Xss]]]";
   std::string java_mperms =  "[[[c:metaint, c:nil]], [[c:metaint, v:_0], [h:_0, c:list, v:G, v:Gs], [c:cls, v:_1, v:Gs], [h:_1, c:list, v:G, v:Bs], [c:metaint, v:Bs]], [[c:cls, v:_0, v:Tail], [h:_0, c:list, v:_1, v:Tail], [h:_1, c:sel, v:X, v:_2, v:Xs], [h:_2, c:list, v:X, v:Xs]], [[c:cls, v:_0, v:Tail], [h:_0, c:list, v:_1, v:_2], [h:_1, c:sel, v:X, v:_3, v:_4], [h:_3, c:list, v:Y, v:Xs], [h:_4, c:list, v:Y, v:Ys], [h:_2, c:list, v:_5, v:Tail], [h:_5, c:sel, v:X, v:Xs, v:Ys]], [[c:cls, v:_0, v:Tail], [h:_0, c:list, v:_1, v:Tail], [h:_1, c:perm, c:nil, c:nil]], [[c:cls, v:_0, v:Tail], [h:_0, c:list, v:_1, v:_2], [h:_1, c:perm, v:_3, v:Zs], [h:_3, c:list, v:X, v:Xs], [h:_2, c:list, v:_4, v:_5], [h:_4, c:perm, v:Xs, v:Ys], [h:_5, c:list, v:_6, v:Tail], [h:_6, c:sel, v:X, v:Zs, v:Ys]], [[c:input, v:_0, v:_1], [l:_0, n:1, n:2, n:3, n:4, n:5, n:6, n:7, n:8, n:9, n:10, n:11], [l:_1, n:11, n:10, n:9, n:8, n:7, n:6, n:5, n:4, n:3, n:2, n:1]], [[c:goal, v:Y], [c:input, v:X, v:Y], [c:metaint, v:_0], [l:_0, v:_1, v:_2], [h:_1, c:perm, v:X, v:Y], [h:_2, c:perm, v:Y, v:X]]]";
   std::string java_big =     "[[[c:app, c:nil, v:Ys, v:Ys]], [[c:app, v:_0, v:Ys, v:_1], [h:_0, c:list, v:X, v:Xs], [h:_1, c:list, v:X, v:Zs], [c:app, v:Xs, v:Ys, v:Zs]], [[c:nrev, c:nil, c:nil]], [[c:nrev, v:_0, v:Zs], [h:_0, c:list, v:X, v:Xs], [c:nrev, v:Xs, v:Ys], [c:app, v:Ys, v:_1, v:Zs], [l:_1, v:X]], [[c:s, n:0, n:1]], [[c:s, n:1, n:2]], [[c:s, n:2, n:3]], [[c:s, n:3, n:4]], [[c:s, n:4, n:5]], [[c:s, n:5, n:6]], [[c:s, n:6, n:7]], [[c:s, n:7, n:8]], [[c:s, n:8, n:9]], [[c:s, n:9, n:10]], [[c:s, n:10, n:11]], [[c:s, n:11, n:12]], [[c:s, n:12, n:13]], [[c:s, n:13, n:14]], [[c:s, n:14, n:15]], [[c:s, n:15, n:16]], [[c:s, n:16, n:17]], [[c:s, n:17, n:18]], [[c:dup, n:0, v:X, v:X]], [[c:dup, v:N, v:X, v:R], [c:s, v:N1, v:N], [c:app, v:X, v:X, v:XX], [c:dup, v:N1, v:XX, v:R]], [[c:goal, v:_0], [l:_0, v:X, v:Y], [c:dup, n:18, v:_1, v:_2], [l:_1, c:a, c:b, c:c, c:d], [h:_2, c:list, v:X, v:_3], [h:_3, c:list, v:Y, v:_4]]]";


   std::cout << "Testing Toks class..." << std::endl;

   bool fail = false;

   std::string curfile = "../progs/add.pl.nl";
   std::string cur = Toks::toString(Toks::toSentences(curfile, true));
   if (!testToks_show(curfile, cur, java_add))
      fail = true;
   
   curfile = "../progs/lambdas.pl.nl";
   cur = Toks::toString(Toks::toSentences(curfile, true));
   if (!testToks_show(curfile, cur, java_lambdas))
      fail = true;

   curfile = "../progs/perms.pl.nl";
   cur = Toks::toString(Toks::toSentences(curfile, true));
   if (!testToks_show(curfile, cur, java_perms))
      fail = true;

   curfile = "../progs/queens.pl.nl";
   cur = Toks::toString(Toks::toSentences(curfile, true));
   if (!testToks_show(curfile, cur, java_queens))
      fail = true;

   curfile = "../progs/sud4x.pl.nl";
   cur = Toks::toString(Toks::toSentences(curfile, true));
   if (!testToks_show(curfile, cur, java_sud4x))
      fail = true;

   curfile = "../progs/mperms.pl.nl";
   cur = Toks::toString(Toks::toSentences(curfile, true));
   if (!testToks_show(curfile, cur, java_mperms))
      fail = true;

   curfile = "../progs/big.pl.nl";
   cur = Toks::toString(Toks::toSentences(curfile, true));
   if (!testToks_show(curfile, cur, java_big))
      fail = true;


   if(!fail)
      std::cout << "All Tests Passed!\n";

   return !fail;
}


bool Assert(bool value, std::string msg, int n = -1)
{
   if(!value) {
      std::cout << "Assert failed: " << msg;
      if(n > 0)
         std::cout << " " << n;
      std::cout << std::endl;
   }
   return value;
}

bool testIntStack()
{
   std::cout << "Testing IntStack Class...\n";
   int success = true;
   IntStack stack;
   
   success = success && Assert(stack.getTop() == -1, "Test 1");

   for(int i = 0 ; i < 1000 ; i++)
      stack.push(i);

   success = success && Assert(stack.size() == 1000 , "Test 2");

   for (int i = 0 ; i < 100 ; i++)
      stack.pop();

   success = success && Assert(stack.pop() == 899, "Test 3");
   success = success && Assert(stack.size() == 899, "Test 4");

   for (int i = 0 ; i < 100 ; i++)
      stack.push(i);

   success = success && Assert(stack.pop() == 99, "Test 5");
   success = success && Assert(stack.size() == 998, "Test 6");

   success = success && Assert(stack.isEmpty() == false, "Test 7");
   success = success && Assert(stack.getTop() == 997, "Test 8");

   stack.set(997, 15);
   success = success && Assert(stack.get(997) == 15, "Test 9");
   success = success && Assert(stack.pop() == 15, "Test 10");



   stack.clear();
   success = success && Assert(stack.isEmpty() == true, "Test 11");
   success = success && Assert(stack.getTop() == -1, "Test 12");
   success = success && Assert(stack.size() == 0, "Test 13");



   if(success)
      std::cout << "All Tests Passed!\n";

   return success;
}





bool testIntList()
{
   std::cout << "Testing IntList Class...\n";
   bool success = true;
   IntList* Xs = nullptr;
   int c = 0;
   success = success && Assert(IntList::isEmpty(Xs), "Test ", ++c);

   Xs = IntList::cons(5, Xs);
   success = success && Assert(IntList::isEmpty(Xs) == false, "Test ", ++c);
   success = success && Assert(IntList::head(Xs) == 5, "Test ", ++c);
   success = success && Assert(IntList::tail(Xs) == nullptr, "Test ", ++c);

   
   Xs = IntList::cons(8, Xs);
   success = success && Assert(IntList::isEmpty(Xs) == false, "Test ", ++c);
   success = success && Assert(IntList::head(Xs) == 8, "Test ", ++c);
   success = success && Assert(IntList::head(IntList::tail(Xs)) == 5, "Test ", ++c);

   success = success && Assert(IntList::len(Xs) == 2, "Test ", ++c);

   for (int i = 0 ; i < 10 ; i++)
      Xs = IntList::cons(i, Xs);

   success = success && Assert(IntList::len(Xs) == 12, "Test ", ++c);
   success = success && Assert(IntList::toInts(Xs).size() == 12, "Test ", ++c);

   for (int i = 0 ; i < 8 ; i++)
      Xs = IntList::tail(Xs);

   success = success && Assert(IntList::head(Xs) == 1, "Test ", ++c);
   success = success && Assert(IntList::head(IntList::tail(Xs)) == 0, "Test ", ++c);
   success = success && Assert(IntList::len(Xs) == 4, "Test ", ++c);

   std::vector<int> vapp = {3, 4, 5, 6};
   Xs = IntList::app(vapp, Xs);
   success = success && Assert(IntList::head(Xs) == 3, "Test ", ++c);
   success = success && Assert(IntList::head(IntList::tail(Xs)) == 4, "Test ", ++c);
   success = success && Assert(IntList::len(Xs) == 8, "Test ", ++c);

   if(success)
      std::cout << "Tests Passed.\n";



   std::cout << "Stress Testing IntList...\n";
   for(int i = 0 ; i < 100000000 ; i++)
      Xs = IntList::cons(i, Xs);
   success = success && Assert(IntList::head(Xs) == 99999999, "Test ", ++c);
   success = success && Assert(IntList::len(Xs) == 100000008, "Test ", ++c);

   if(success)
      std::cout << "All Tests Passed!\n";

   return success;
}

bool testIntMap()
{
   std::cout << "Testing IntMap Class...\n";
   bool success = true;
   IntMap map;
   int c = 0;


   success = success && Assert(map.isEmpty(), "Test " , ++c);
   success = success && Assert(map.size() == 0, "Test " , ++c);

   for(int i = 1 ; i < 101 ; i++)
   {
      map.put(i, i*2);
   }
   success = success && Assert(map.isEmpty() == false, "Test " , ++c);
   success = success && Assert(map.size() == 100, "Test " , ++c);

   c++;
   for(int i = 1 ; i < 101 ; i++)
   {
      int x = map.get(i);
      success = success && Assert(x == i*2, "Test ", c);
      success = success && Assert(map.contains(i), "Test ", c+1);
   }
   c++;

   success = success && Assert(map.contains(400) == false, "Test " , ++c);

   for(int i = 500; i < 600; i++)
      map.add(i);

   c++;
   for(int i = 500 ; i < 600 ; i++)
   {
      success = success && Assert(map.contains(i), "Test ", c);
   }

   // del and remove are not called from anywhere.

   if(success)
      std::cout << "Tests Passed!\nStress Testing...\n";

   for(int i = 1; i <= 100000000 ; i++)
      map.put(i, i+100);

   success = success && Assert(map.get(10) == 110, "Test " , ++c);

   success = success && Assert(map.size() == 100000000, "Test " , ++c);

   if(success)
      std::cout << "All Tests Passed!\n";

   return success;
}



#include "Prog.h"
void run(std::string fname)
{
	Prog P(fname);
   std::cout << "CODE" << std::endl;
   P.ppCode();
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

//   testToks();
//   testIntStack();
//   testIntList();
//   testIntMap();
	return 0;
}

