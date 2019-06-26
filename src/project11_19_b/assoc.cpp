#include "assoc.h"

double& Assoc::operator[](std::string& s)
{
   for (std::vector<Pair>::iterator p = vec.begin(); p != vec.end(); ++p) {
      if (s == p->name) {
         return p->val;
      }
   }

   vec.push_back(Pair(s, 0));
   return vec.back().val;
}

const double& Assoc::operator[](const std::string& s)
{
   for (std::vector<Pair>::iterator p = vec.begin(); p != vec.end(); ++p) {
      if (s == p->name) {
         return p->val;
      }
   }

   vec.push_back(Pair(s, 0));
   return vec.back().val;
}

void Assoc::printAll() const
{
   for (std::vector<Pair>::const_iterator p = vec.begin(); p != vec.end(); ++p) {
      std::cout << p->name << " : " << p->val << '\n';
   }
}


