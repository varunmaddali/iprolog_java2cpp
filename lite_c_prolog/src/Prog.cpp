
#include "Prog.h"

#include <iostream>

Prog::Prog(std::string fname)
:  Engine(fname)
{

}


std::string Prog::showTerm(Object o)
{
   if(o.getType() == Object::T_ARRAY)
      return st0(*(o.getInternalArray()));
   return o.toString();
}


std::string Prog::mapToString(const std::map<std::string, int> &m)
{
   std::ostringstream oss;
   oss << "{";
   bool first = true;
   for (auto it = m.begin(); it != m.end(); it++)
   {
      if(!first)
      {
         oss << ", ";
      }
      first = false;
      oss << it->first << ":" << it->second;
   }
   oss << "}";
   return oss.str();
}

std::string Prog::maybeNull(Object &o)
{
   if(o.isNull())
      return "$null";
   if(o.getType() == Object::T_ARRAY)
      return st0(*o.getInternalArray());
   return o.toString();
}

bool Prog::isListCons(std::string o)
{
   return (o == "." || o == "[|]" || o == "list");
}

bool Prog::isOp(std::string o)
{
   return (o == "/" || o == "-" || o == "+" || o == "=");
}


std::string Prog::st0(std::vector<Object>& v)
{
   std::ostringstream oss;
   std::string name = v[0].toString();
   if(v.size() == 3 && isOp(name))
   {
      oss << "(";
      oss << maybeNull(v[0]);
      oss << " " << name << " ";
      oss << maybeNull(v[1]);
      oss << ")";
   }
   else if(v.size() == 3 && isListCons(name))
   {
      oss << "[";
      oss << maybeNull(v[1]);
      Object tail(v[2]);
      for(;;)
      {
         if(tail.equals("[]") || tail.equals("nil"))
            break;
         if(tail.getType() != Object::T_ARRAY)
         {
            oss << "|";
            oss << maybeNull(tail);
            break;
         }
         std::vector<Object>* list = tail.getInternalArray();
         if(!(list->size() == 3 && isListCons((*list)[0].toString())))
         {
            oss << "|";
            oss << maybeNull(tail);
            break;
         }
         else
         {
            oss << ",";
            oss << maybeNull((*list)[1]);
            tail = (*list)[2];
         }
      }
      oss << "]";
   }
   else if(v.size() == 2 && name == "$VAR")
   {
      oss << "_" << v[1].toString();
   }
   else
   {
      std::string qname = maybeNull(v[0]);
      oss << qname;
      oss << "(";
      for (int i = 1; i < v.size(); i++) {
         Object O = v[i];
         oss << maybeNull(O);
         if (i < v.size() - 1) {
            oss << ",";
         }
      }
      oss << ")";
   }


   return oss.str();
}


void Prog::ppCode()
{
   std::cout << "\nSYMS:\n";
   std::cout << mapToString(syms) << std::endl;
   std::cout << "\nCLAUSES\n\n";

   for (int i = 0 ; i < clauses->size(); i++)
   {
      std::cout << "[" << i << "]" << showClause((*clauses)[i]) << std::endl;
   }
   std::cout << std::endl;
}


std::string Prog::showClause(Clause& s)
{
   std::ostringstream buf;
   int l = (int)s.hgs.size();
   buf << "---base:[" << s.base << "] neck: " << s.neck << "-----\n";
   buf << showCells(s.base, s.len); // TODO
   buf << "\n";
   buf << showCell(s.hgs[0]);

   buf << " :- [";
   for (int i = 1; i < l; i++) {

      int e = s.hgs[i];
      buf << showCell(e);
      if (i < l - 1) {
         buf << ", ";
      }
   }

   buf << "]\n";

   buf << Engine::showTerm(s.hgs[0]);
   if (l > 1) {
      buf << " :- \n";
      for (int i = 1; i < l; i++) {
         int e = s.hgs[i];
         buf << "  ";
         buf << Engine::showTerm(e);
         buf << "\n";
      }
   } else {
      buf << "\n";
   }

   return buf.str();

}












