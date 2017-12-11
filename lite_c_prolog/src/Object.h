#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>
#include <sstream>


/**
*	This Class can hold a single value. It's either a std::string, an int, or a std::vector<Object>
*/

class Object
{
public:
	static const int T_NULL = 0;
	static const int T_STRING = 1;
	static const int T_INT = 2;
	static const int T_ARRAY = 3;


	Object()
		: sval("NULL"), type(T_NULL)
	{
	}

	Object(std::string s)
		: sval(s), type(T_STRING)
	{
	}

	Object(int i)
		: ival(i), type(T_INT)
	{

	}

	Object(std::vector<Object>& v)
		: vval(v), type(T_ARRAY)
	{

	}

   Object(const Object& rhs)
   : type(rhs.type), ival(rhs.ival), sval(rhs.sval), vval(rhs.vval)
   {

   }

   Object& operator=(const Object& rhs)
   {
      type = rhs.type;
      ival = rhs.ival;
      sval = rhs.sval;
      vval = rhs.vval;
      return *this;
   }


   std::vector<Object>* getInternalArray()
   {
      if(type != T_ARRAY)
         return nullptr;
      return &vval;
   }

   bool equals(std::string s)
   {
      if(type == T_STRING && sval == s)
         return true;
      return false;
   }


	std::string toString() const
	{
		if (type == T_NULL)
			return sval;
		if (type == T_STRING)
			return sval;
		if (type == T_INT)
			return std::to_string(ival);

		// vector
		std::ostringstream os;
		os << "[";
		for (unsigned int i = 0 ; i < vval.size() ; i++)
		{
			if (i > 0)
				os << ", ";
			os << vval[i].toString();
		}
		os << "]";
		return os.str();
	}

	bool isNull() const
	{
		return type == T_NULL;
	}

   int getType() const
   {
      return type;
   }


private:
	std::vector<Object> vval;
	int ival;
	std::string sval;
	int type;
};

#endif
