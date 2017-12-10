#include "Clause.h"



Clause::Clause::Clause(const int len, const std::vector<int>& hgs, const int base, const int neck, const std::vector<int>& xs)
	: hgs(hgs), base(base), len(len), neck(neck), xs(xs)
{
}


Clause::~Clause()
{
}

#include <sstream>
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
