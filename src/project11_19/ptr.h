#pragma once

#include <iostream>

template <class T>
class PtrT
{
public:
    PtrT(T *p, T *array, int s) : p(p), array(array), size(s) {}
    PtrT(const PtrT& ptr) : p(ptr.p), array(ptr.array), size(ptr.size) {}

    PtrT& operator=(const PtrT& ptr)
    {
        if (this == &ptr) {
            return *this;
        }

        p = ptr.p;
        array = ptr.array;
        size = ptr.size;

        return *this;
    }

    PtrT& operator++()
    {
        ++p;
        return *this;
    }

    PtrT operator++(int)
    {
        PtrT res = *this;
        ++p;
        return res;
    }

    PtrT& operator--()
    {
        --p;
        return *this;
    }

    PtrT operator--(int)
    {
        PtrT res = *this;
        --p;
        return res;
    }

    T& operator*()
    {
        if (p - array < size && p - array >= 0) {
            return *p;
        }
        else {
            throw("Error");
        }
    }

private:
   T *p;
   T* array;
   int size;
};