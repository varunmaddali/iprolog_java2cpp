
#ifndef Prog_hpp
#define Prog_hpp


#include "Engine.h"


class Prog : public Engine
{
public:
   Prog(std::string fname);

   std::string showTerm(Object o) override;
   static std::string mapToString(const std::map<std::string, int>& m);
   static std::string st0(std::vector<Object>& v);

   static std::string maybeNull(Object& o);
   static bool isListCons(std::string o);
   static bool isOp(std::string o);

   void ppCode();
   std::string showClause(Clause& C);

};



#endif /* Prog_hpp */
