#include <string.h>
#include "String.h"


struct String::Srep
{
    char *s;
    int sz;
    int n;

    Srep(int nsz, const char *p)
    {
        n = 1;
        sz = nsz;
        s = new char[sz + 1];
        strcpy(s, p);
    }

    ~Srep() { delete[] s; }

    Srep *get_own_copy()
    {
        if (n == 1) return this;
        n--;
        return new Srep(sz, s);
    }

    void assign(int nsz, const char *p)
    {
        if (sz != nsz) {
            delete[] s;
            sz = nsz;
            s = new char[sz + 1];
        }
        strcpy(s, p);
    }
private:
    Srep(const Srep&);
    Srep& operator=(const Srep&);
};

String::String()
{
    rep = new Srep(0, "");
}

String::String(const String& x)
{
    x.rep->n++;
    rep = x.rep;
}

String::~String()
{
    if (--rep->n == 0) delete rep;
}

String& String::operator=(const STring& x)
{
    x.rep->n++;
    if (--rep->n == 0) delete rep;
    rep = x.rep;
    return *this;
}

String::String(const char *s)
{
    rep = new Srep(strlen(s), s);
}

String& String::operator=(const char *s)
{
    if (rep->n == 1)
        rep->assign(strlen(s), s);
    else {
        rep->n--;
        rep = new Srep(strlen(s), s);
    }
    return *this;
}
