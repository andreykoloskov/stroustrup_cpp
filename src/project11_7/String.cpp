#include "String.h"
#include <string.h>

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
        int len = static_cast<int>(strlen(p));
        len = (len < sz) ? len : sz;
        if (len > 0) {
            std::memcpy(s, p, len);
            s[len] = '\0';
        }
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
        int len = static_cast<int>(strlen(p));
        len = (len < sz) ? len : sz;
        if (len > 0) {
            std::memcpy(s, p, len);
            s[len] = '\0';
        }
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

String& String::operator=(const String& x)
{
    x.rep->n++;
    if (--rep->n == 0) delete rep;
    rep = x.rep;
    return *this;
}

String::String(const char *s)
{
    rep = new Srep((int) strlen(s), s);
}

String& String::operator=(const char *s)
{
    if (rep->n == 1)
        rep->assign((int) strlen(s), s);
    else {
        rep->n--;
        rep = new Srep((int) strlen(s), s);
    }
    return *this;
}

void String::check(int i) const
{
    if (i < 0 || rep->sz <= i) throw Range();
}

char String::read(int i) const
{
    return rep->s[i];
}

void String::write(int i, char c)
{
    rep = rep->get_own_copy();
    rep->s[i] = c;
}

String::Cref String::operator[](int i)
{
    check(i);
    return Cref(*this, i);
}

char String::operator[](int i) const
{
    check(i);
    return rep->s[i];
}

int String::size() const
{
    return rep->sz;
}

std::ostream& operator<<(std::ostream& os, const String& s)
{
    return os << s.rep->s;
}

std::istream& operator>>(std::istream& is, String& s)
{
    char ss[256];
    is >> ss;
    s = ss;
    return is;
}

bool operator==(const String& x, const String& y)
{
    return strcmp(x.rep->s, y.rep->s) == 0;
}

bool operator==(const String& x, const char* s)
{
    return strcmp(x.rep->s, s) == 0;
}

bool operator!=(const String& x, const String& y)
{
    return strcmp(x.rep->s, y.rep->s) != 0;
}

bool operator!=(const String& x, const char* s)
{
    return strcmp(x.rep->s, s) != 0;
}

