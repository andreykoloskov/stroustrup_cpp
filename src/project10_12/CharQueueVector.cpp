#include <iterator>
#include <iostream>
#include <algorithm>
#include "CharQueueVector.h"

Queue::CharQueueVector::CharQueueVector()
{
}

Queue::CharQueueVector::~CharQueueVector()
{  
}

void Queue::CharQueueVector::push_back(char ch)
{
   queue.push_back(ch);
}

void Queue::CharQueueVector::pop_back()
{
   queue.pop_back();
}

void Queue::CharQueueVector::print()
{
   std::copy(queue.begin(), queue.end(),
         std::ostream_iterator<char>(std::cout, " "));
   std::cout << std::endl;
}