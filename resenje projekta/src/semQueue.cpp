//
// Created by os on 9/7/22.
//

#include "../h/semQueue.hpp"


TCB* SemQueue::get() {
    return waitingThreads->removeFirst();
}

void SemQueue::put(TCB *thread) {
    waitingThreads->addLast(thread);
}
