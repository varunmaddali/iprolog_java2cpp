clause.cpp

compiling and output.

vm0241@cse02:~/se/se_submission/cpp$ g++ Clause.cpp
vm0241@cse02:~/se/se_submission/cpp$ ./a.out
the values are len5
the values are neck7
the values are base1
2 3 4 5 6
2 3 4 5 6 

clause.java
compiling and output.

vm0241@cse02:~/se/se_submission/java$ javac Clause.java
vm0241@cse02:~/se/se_submission/java$ java Clause
the values are len:5
the values are base:1
the values are neck:7
23456
23456


obstack.cpp
compiling and output.


vm0241@cse02:~/se/se_submission/cpp$ g++ ObStack.cpp
vm0241@cse02:~/se/se_submission/cpp$ ./a.out
5
6


obstack.java
compiling and output.

vm0241@cse02:~/se/se_submission/java$ javac ObStack.java
Note: ObStack.java uses unchecked or unsafe operations.
Note: Recompile with -Xlint:unchecked for details.
vm0241@cse02:~/se/se_submission/java$ java ObStack
5
6



intstack.cpp
compiling and output.

vm0241@cse02:~/se/se_submission/cpp$ g++ IntStack.cpp
IntStack.cpp:8:11: warning: non-static data member initializers only available with -std=c++11 or -std=gnu++11
  int SIZE=16;
           ^
IntStack.cpp:9:25: warning: non-static data member initializers only available with -std=c++11 or -std=gnu++11
  int minsize =1<<(SIZE-1);
                         ^
vm0241@cse02:~/se/se_submission/cpp$ ./a.out
3




intstack.java
compiling and output.

vm0241@cse02:~/se/se_submission/java$ javac IntStack.java
vm0241@cse02:~/se/se_submission/java$ java IntStack
3




toks.cpp
compiling and output.


toks.java
compiling and output.


vm0241@cse02:~/se/se_submission/java$ javac Toks.java
vm0241@cse02:~/se/se_submission/java$ java Toks
[[[f:this, c:a, c:test, c:file, c:for, c:toks]], [[c:java], [], [c:given, c:to, c:the, c:program, c:it, c:gives, c:out, c:the, c:tokens]]]
