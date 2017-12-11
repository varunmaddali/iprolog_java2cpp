#include "Clause.h"

//declaring a constructor 
Clause::Clause::Clause(const int len, const std::vector<int>& hgs, const int base, const int neck, const std::vector<int>& xs)
	: hgs(hgs), base(base), len(len), neck(neck), xs(xs)
{
}

//destructor to take care of the completed objects
Clause::~Clause()
{
}

#include <sstream>
//clause class that gets all the values
std::string Clause::toString()
{
	std::ostringstream os;
	os << "len: " << len << std::endl;
	os << "hgs size: " << hgs.size() << std::endl;
	os << "base: " << base << std::endl;
	os << "neck: " << neck << std::endl;
	os << "xs size: " << xs.size() << std::endl;

	return os.str();
}
