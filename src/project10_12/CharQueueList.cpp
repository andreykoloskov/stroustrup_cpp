#include <iterator>
#include <iostream>
#include <algorithm>
#include "CharQueueList.h"

Queue::CharQueueList::CharQueueList()
{
}

Queue::CharQueueList::~CharQueueList()
{  
}

void Queue::CharQueueList::push_back(char ch)
{
   queue.push_back(ch);
}

void Queue::CharQueueList::pop_back()
{
   queue.pop_back();
}

void Queue::CharQueueList::print()
{
   std::copy(queue.begin(), queue.end(),
         std::ostream_iterator<char>(std::cout, " "));
   std::cout << std::endl;
}
