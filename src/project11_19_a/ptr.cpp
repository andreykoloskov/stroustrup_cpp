#include "ptr.h"

RecPtr::RecPtr(const char *p): identifier(p), inCoreAddress(nullptr) {}

RecPtr::~RecPtr()
{
   std::cout << "Write to disk: " << inCoreAddress->name << std::endl;
   if (inCoreAddress != nullptr) {
      delete inCoreAddress;
   }
}

Rec *RecPtr::operator->()
{
    if (inCoreAddress == nullptr) {
        std::cout << "Read from disk" << std::endl;
        inCoreAddress = new Rec();
    }
    return inCoreAddress;
}
