#pragma once

namespace Queue
{

class CharQueue
{
public:
    CharQueue() {};
    virtual ~CharQueue() {};
    virtual void push_back(char ch) = 0;
    virtual void pop_back() = 0;
    virtual void print() = 0;
};

}
