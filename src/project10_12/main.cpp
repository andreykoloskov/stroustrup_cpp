#include "CharQueue.h"
#include "CharQueueList.h"
#include "CharQueueVector.h"

using namespace Queue;

void
queueProcess(CharQueue *queue)
{
    queue->push_back('a');
    queue->push_back('b');
    queue->pop_back();
    queue->push_back('d');
    queue->print();
}

int
main(int argc, char **argv)
{
    CharQueueList charQueueList;
    CharQueueVector charQueueVector;

    queueProcess(&charQueueList);
    queueProcess(&charQueueVector);

    return 0;
}