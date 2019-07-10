#pragma once

#include <iostream>

class String_iter;

class String
{
private:
    struct Srep;
    Srep *rep;
    class Cref;

public:
    class Range {};
    String();
    String(const char *);
    String(const String&);
    String& operator=(const char *);
    String& operator=(const String&);
    ~String();

    void check(int i) const;
    char read(int i) const;
    void write(int i, char c);

    Cref operator[](int i);
    char operator[](int i) const;

    int size() const;

    String& operator+=(const String&);
    String& operator+=(const char*);

    friend std::ostream& operator<<(std::ostream&, const String&);
    friend std::istream& operator>>(std::istream&, String&);

    friend bool operator==(const String& x, const String& y);
    friend bool operator==(const String& x, const char* s);
    friend bool operator!=(const String& x, const String& y);
    friend bool operator!=(const String& x, const char* s);

    friend class String_iter;
    String_iter begin();
    String_iter end();
};

String operator+(const String&, const String&);
String operator+(const String&, const char*);

class String::Cref
{
public:
    operator char() const { s.check(i); return s.read(i); }
    void operator=(char c) { s.write(i, c); }

private:
    friend class String;

    String& s;
    int i;

    Cref(String& ss, int ii): s(ss), i(ii) {}
    Cref(const Cref& r) : s(r.s), i(r.i) {}
    Cref();
};

class String_iter
{
public:
    String_iter(String& s): s(s), i(0) {}

    char& next()
    {
        ch = s[++i];
        return ch;
    }

    char operator*()
    {
       return s[i];
    }

    String_iter& operator++()
    {
       ++i;
       return *this;
    }

    String_iter& operator++(int a)
    {
       String_iter si(*this);
       ++(*this);
       return si;
    }

    void setPosition(int ii) { i = ii; }
    int getPosition() const { return i; }

    friend bool operator==(const String_iter& x, const String_iter& y);
    friend bool operator!=(const String_iter& x, const String_iter& y);

private:
   String& s;
   char ch;
   int i;
};

