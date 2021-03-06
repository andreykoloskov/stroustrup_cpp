#pragma once

#include <iostream>

class String_iter;
class SubString;

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
    char& read2(int i);
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

    SubString operator() (int pos, int count) const;
};

String operator+(const String&, const String&);
String operator+(const String&, const char*);

class String::Cref
{
public:
    operator char() const { s.check(i); return s.read(i); }
    operator char&() { s.check(i); return s.read2(i); }
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
    char& next() { return s[++i]; }
    //const char operator*() { return s[i]; }
    char& operator*() { return s[i]; }
    String_iter& operator++() { ++i; return *this; }
    String_iter operator++(int a) { String_iter si(*this); ++(*this); return si; }
    void setPosition(int ii) { i = ii; }
    int getPosition() const { return i; }
    friend bool operator==(const String_iter& x, const String_iter& y);
    friend bool operator!=(const String_iter& x, const String_iter& y);
private:
   String& s;
   int i;
};


class SubString
{
public:
    SubString(String& str, String& subStr, int pos, int count): str(str), subStr(subStr), pos(pos), count(count) {}
    operator String&() { return subStr; }
    void operator=(String& s);
    void operator=(const char* s);
   
private:
    String& str;
    String subStr;
    int pos;
    int count;
};

