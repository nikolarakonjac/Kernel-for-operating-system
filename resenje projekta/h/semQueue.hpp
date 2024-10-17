//
// Created by os on 9/7/22.
//

#ifndef PROJECT_BASE_V1_1_SEMQUEUE_HPP
#define PROJECT_BASE_V1_1_SEMQUEUE_HPP

#include "list.hpp"

class TCB;

class SemQueue {
private:
    List<TCB>* waitingThreads;
public:
    SemQueue(){
        waitingThreads = new List<TCB>();
    }

    ~SemQueue(){
        delete waitingThreads;
        waitingThreads = nullptr;
    }

    TCB* get();

    void put(TCB* thread);

    int queueSize(){ return waitingThreads->listSize(); }
};


#endif //PROJECT_BASE_V1_1_SEMQUEUE_HPP
