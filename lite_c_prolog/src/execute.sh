#rm -f progs/*.pl.nl
g++ -std=c++11 -O3 -o cProlog Clause.cpp Main.cpp Engine.cpp Prog.cpp IntList.cpp IntMap.cpp IntStack.cpp Spine.cpp Toks.cpp
#swipl -f pl2nl.pl -g "pl('$1'),halt"
./cProlog "pl/$1.pl.nl"
ls pl/*.pl