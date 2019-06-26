#pragma once

#include <iostream>
#include <string>
#include <vector>

class Assoc
{
   struct Pair
   {
      std::string name;
      double val;
      Pair(std::string n = "", double v = 0): name(n), val(v) {}
   };

   std::vector<Pair> vec;

   Assoc(const Assoc&) = default;
   Assoc& operator=(const Assoc&) = default;

public:
   Assoc() = default;
   const double& operator[](const std::string&);
   double& operator[](std::string&);
   void printAll() const;
};

