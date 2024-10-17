//
// Created by os on 8/27/22.
//

#include "../h/scheduler.hpp"


List<TCB> Scheduler::readyThreadQueue;

TCB *Scheduler::get()
{
    return readyThreadQueue.removeFirst();
}

void Scheduler::put(TCB *thread)
{
    readyThreadQueue.addLast(thread);
}

TCB *Scheduler::peekFirst() {
    return readyThreadQueue.peekFirst();
}
