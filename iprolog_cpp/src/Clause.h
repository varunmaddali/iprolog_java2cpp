#ifndef __CLAUSE_H__
#define __CLAUSE_H__
/**
* representation of a clause and also declaration of all the required varibles for this clause class
*/

#include <vector>
#include <string>

class Clause
{
public:
	Clause(const int len, const std::vector<int>& hgs, const int base, const int neck, const std::vector<int>& xs);
	~Clause();

	std::string toString();

	int len;// length of heap slice
	std::vector<int> xs;// indexables in head
	std::vector<int> hgs;// head+goals pointing to cells in cs
	int base;// heap where this starts
	int neck;// first after the end of the head
};
#endif
