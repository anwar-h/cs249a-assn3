#include "Queue.h"
#include "QueueReactor.h"

int main(int argc, char* argv[]) {
    
    Queue::Ptr q = new Queue();
    q->lastNotifieeIs(new QueueReactor(q.ptr()));

    q->enQ(1);
    q->enQ(2);
    q->enQ(3);
    q->enQ(4);

    q->deQ();
    q->deQ();
    q->deQ();
    q->deQ();

    return 0;
}
