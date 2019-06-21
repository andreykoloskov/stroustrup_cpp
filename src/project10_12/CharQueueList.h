#pragma once

#include <list>
#include "CharQueue.h"

namespace Queue
{

class CharQueueList : public CharQueue
{
public:
    CharQueueList();
    ~CharQueueList();
    void push_back(char ch) override;
    void pop_back() override;
    void print() override;

private:
    std::list<char> queue;
};

}
