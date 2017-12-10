#echo go.sh <name_of_prog> assumed in dir ./progs
#making a directory out for all the class files and .pl.nl files
mkdir out
mkdir out/production
mkdir out/production/IP
#saving the location of the created directory
export TARGET="out/production/IP"
mkdir "$TARGET"
rm -r -f $TARGET/iProlog
rm -f progs/*.pl.nl
#to be continued.
g++ -std=c++11 -O3 -o cProlog Clause.cpp main.cpp Engine.cpp Prog.cpp IntList.cpp IntMap.cpp IntStack.cpp Spine.cpp Toks.cpp
