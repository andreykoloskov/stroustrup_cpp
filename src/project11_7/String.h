#pragma once


class String
{
public:
    class Range {};
    String();
    String(const char *);
    String(const String&);
    String& operator=(const char *);
    String& operator=(const String&);
    ~String();

    void check(int i) const { if (i < 0 || rep->sz <= i) throw Range(); }
    char read(int i) const { return rep->s[i]; }
    void write(int i, char c) { rep = rep->get_own_copy(); rep->s[i] = c; }

    Cref operator[](int i) { check(i); return Cref(*this, i); }
    char operator[](int i) const { check(i); return rep->s[i]; }

    int size() const { return rep->sz; }

private:
    struct Srep;
    Srep *rep;
    class Cref;
};

