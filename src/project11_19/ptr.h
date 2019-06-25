#pragma once

template <class T>
class PtrT
{
public:
   PtrT(T *p, T *v, int s);
   PtrT(T *p);

   PtrT& operator++();
   PtrT operator++(int);

   PtrT& operator--();
   PtrT operator--(int);

   T& operator*();

private:
   T *p;
   T *array;
   int size;
};