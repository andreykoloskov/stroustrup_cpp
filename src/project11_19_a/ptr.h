#pragma once

#include <iostream>
#include <string>

struct Rec
{
   std::string name;
};

class RecPtr
{
public:
   RecPtr(const char *p);
   ~RecPtr();
   Rec *operator->();

private:
   const char *identifier;
   Rec *inCoreAddress;
};
