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
            memcpy(s, p, len);
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
            memcpy(s, p, len);
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

char& String::read2(int i)
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

String_iter String::begin()
{
    String_iter it(*this);
    return it;
}

String_iter String::end()
{
    String_iter it(*this);
    it.setPosition(rep->sz);
    return it;
}

SubString String::operator() (int pos, int count) const
{
    check(pos);
    check(count);
    check(pos + count);
    char* str = new char[count + 1];

    if (count > 0)
        memcpy(str, &rep->s[pos], count);

    str[count] = '\0';
    String s = str;
    delete[] str;
    return SubString((String&) *this, s, pos, count);
}

void SubString::operator=(String& s)
{
    int len = pos + s.size() + str.size() - pos - count + 1;
    char* st = new char[len];
    for (int i = 0; i < pos; ++i)
        st[i] = str[i];
    for (int i = pos; i < pos + s.size(); ++i)
        st[i] = s[i - pos];
    for (int i = pos + s.size(); i < len - 1; ++i)
        st[i] = str[i + count - s.size()];
    st[len - 1] = '\0';

    str = st;
    delete[] st;
}

void SubString::operator=(const char* s)
{
    int len = pos + strlen(s) + str.size() - pos - count + 1;
    char* st = new char[len];
    for (int i = 0; i < pos; ++i)
        st[i] = str[i];
    for (int i = pos; i < pos + strlen(s); ++i)
        st[i] = s[i - pos];
    for (int i = pos + strlen(s); i < len - 1; ++i)
        st[i] = str[i + count - strlen(s)];
    st[len - 1] = '\0';

    str = st;
    delete[] st;
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

bool operator==(const String_iter& x, const String_iter& y)
{
   return x.s == y.s && x.getPosition() == y.getPosition();
}

bool operator!=(const String_iter& x, const String_iter& y)
{
   return !(x == y);
}

