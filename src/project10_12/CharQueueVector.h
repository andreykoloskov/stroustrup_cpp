#pragma once

#include <vector>
#include "CharQueue.h"

namespace Queue
{

class CharQueueVector : public CharQueue
{
public:
    CharQueueVector();
    ~CharQueueVector();
    void push_back(char ch) override;
    void pop_back() override;
    void print() override;

private:
    std::vector<char> queue;
};

}