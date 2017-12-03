#ifndef __TOKS_H__
#define __TOKS_H__

#include <string>
#include <istream>
#include <vector>

class Toks
{
public:
	Toks(std::string s, bool fromFile);
	~Toks();

	std::string getWord();
	std::string toString();
	int nextToken();

	static std::vector<std::vector<std::vector<std::string>*>*> toSentences(std::string s, bool fromFile);
	static std::string toString(const std::vector<std::vector<std::vector<std::string>*>*> & Wsss);


	static const std::string IF;
	static const std::string AND;
	static const std::string DOT;
	static const std::string HOLDS;
	static const std::string LISTS;
	static const std::string IS;

	static const int TT_EOF = -1;
	static const int TT_WORD = -2;

private:
	std::istream* iStream;
	std::string sval;


	bool isOrdinaryChar(char c);
	bool isWordChar(char c);
	void parseComment();
	void parseCppComment();
};



#endif

