#include "Toks.h"

#include <fstream>
#include <sstream>


Toks::Toks(std::string s, bool fromFile)
{
	if (fromFile)
		iStream = new std::ifstream(s);
	else
		iStream = new std::istringstream(s);
}

Toks::~Toks()
{
	delete iStream;
}

std::string Toks::getWord()
{

	int c = nextToken();
	if (c == TT_EOF)
	{
		return "";
	}
	if (c == TT_WORD)
	{
		char first = sval[0];
		if (isupper(first) || first == '_')
		{
			return std::string("v:") + sval;
		}

		try {
			long n = std::stol(sval, nullptr, 10);
			if (std::abs(n) < 1 << 28)
				return std::string("n:") + sval;
			else
				return std::string("c:") + sval;
		}
		catch (...) {
			return std::string("c:") + sval;
		}

	}
	return std::string("") + (char)c;


}

std::string Toks::toString()
{
	return std::string();
}

int Toks::nextToken()
{
	char c = iStream->get();
	if (!iStream->good())
		return TT_EOF;

	while (!isOrdinaryChar(c) && !isWordChar(c))
	{
		c = iStream->get();
		if (!iStream->good())
			return TT_EOF;
	}

	if (isOrdinaryChar(c))
		return c;

	// WordChar
	sval = std::string(1, c);
	while (true)
	{
		char n = iStream->peek();
		if (!iStream->good() || !isWordChar(n))
			break;
		sval += iStream->get();
	}
	return TT_WORD;
}



std::vector<std::vector<std::vector<std::string>*>*> Toks::toSentences(std::string s, bool fromFile)
{
	std::vector<std::vector<std::vector<std::string>*>*> Wsss;
	std::vector<std::vector<std::string>*> * Wss = new std::vector<std::vector<std::string>*>();
	std::vector<std::string> * Ws = new std::vector<std::string>();

	Toks toks(s, fromFile);
	std::string t;

	while ((t = toks.getWord()).size() > 0)
	{
		if (t == DOT)
		{
			Wss->push_back(Ws);
			Wsss.push_back(Wss);

			Wss = new std::vector<std::vector<std::string>*>();
			Ws = new std::vector<std::string>();
		}
		else if (t == std::string("c:") + IF)
		{
			Wss->push_back(Ws);
			Ws = new std::vector<std::string>();
		}
		else if (t == std::string("c:") + AND)
		{
			Wss->push_back(Ws);
			Ws = new std::vector<std::string>();
		}
		else if (t == std::string("c:") + HOLDS)
		{
			(*Ws)[0][0] = 'h';
		}
		else if (t == std::string("c:") + LISTS)
		{
			(*Ws)[0][0] = 'l';
		}
		else if (t == std::string("c:") + IS)
		{
			(*Ws)[0][0] = 'f';
		}
		else
		{
			Ws->push_back(t);
		}
	}

	return Wsss;
}

std::string Toks::toString(const std::vector<std::vector<std::vector<std::string>*>*>& Wsss)
{
	std::ostringstream os;
	os << '[';
	for (unsigned int i = 0 ; i < Wsss.size() ; ++i)
	{
		auto *Wss = Wsss[i];
		if (Wss == nullptr)
			continue;
		if (i > 0)
			os << ", ";
		os << '[';
		for (unsigned int j = 0 ; j < Wss->size(); ++j)
		{
			auto *Ws = (*Wss)[j];
			if (Ws == nullptr)
				continue;
			if (j > 0)
				os << ", ";
			os << '[';
			for (unsigned int k = 0 ; k < Ws->size() ; ++k)
			{
				if (k > 0)
					os << ", ";
				os << (*Ws)[k];
			}
			os << ']';
		}
		os << ']';
	}
	os << ']';

	return os.str();
}

bool Toks::isOrdinaryChar(char c)
{
	if (c == '.')
		return true;
	if (c == '%')
		return true;
	if (c >= '!' && c <= '/')
		return true;
	if (c >= ':' && c <= '@')
		return true;
	if (c >= '[' && c <= '^')
		return true;
	if (c == '`')
		return true;
	if (c >= '{' && c <= '~')
		return true;
	return false;
}

bool Toks::isWordChar(char c)
{
	if (c == '_')
		return true;
	if (c >= 'a' && c <= 'z')
		return true;
	if (c >= 'A' && c <= 'Z')
		return true;
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

void Toks::parseComment()		// pre: istream is past "/*"
{
	char c = iStream->get();
	while (true) {
		if (c != '*')
			c = iStream->get();
		else
		{
			c = iStream->get();
			if (c == '/')
				return;
		}
	}	
}

void Toks::parseCppComment()
{
	char c = iStream->get();
	while (c != '\n' && c != '\r')
		c = iStream->get();
}



const std::string Toks::IF = "if";
const std::string Toks::AND = "and";
const std::string Toks::DOT = ".";
const std::string Toks::HOLDS = "holds";
const std::string Toks::LISTS = "lists";
const std::string Toks::IS = "is";

