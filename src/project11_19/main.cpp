#include <iostream>
#include "ptr.h"


template<class T>
void f(T a)
{
   T v[200];
   PtrT(&v[0], v, 200);

   //p--;
   //*p = a;
   p++;
   *p = a;
}

int main(int argc, char **argv)
{
   f(5);
	return 0;
}