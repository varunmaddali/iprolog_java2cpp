#echo go.sh <name_of_prog> assumed in dir ./progs
mkdir out
mkdir out/production
mkdir out/production/IP
export TARGET="out/production/IP"
mkdir "$TARGET"
rm -r -f $TARGET/iProlog
rm -f progs/*.pl.nl
#to be continued.