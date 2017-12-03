#ifndef __SPINE_H__
#define __SPINE_H__
#include "IntList.h
/**
* runtime representation of an immutable list of goals
* together with top of heap and trail pointers
* and current clause tried out by head goal
* as well as registers associated to it
*
* note that parts of this immutable lists
* are shared among alternative branches
*/
class Spine
{
public:
	/**
	* creates a spine - as a snapshot of some runtime elements
	*/
	//constructor and destructor 
	//constructor based on the input values for the spine object
	Spine(std::vector<int> const & gs0, int base, IntList* gs, int ttop, int k, std::vector<int> * cs);
	/**
	* creates a specialized spine returning an answer (with no goals left to solve)
	*/
	Spine(int hd, int ttop);
    //destructor
	~Spine();
	const int hd;			// head of the clause to which this corresponds
	const int base;			// top of the heap when this was created
	IntList* gs;			// goals - with the top one ready to unfold
	const int ttop;			// top of the trail when this was created
	int k;
	std::vector<int> xs;	// index elements
	std::vector<int>* cs;	// array of  clauses known to be unifiable with top goal in gs
};
#endif
