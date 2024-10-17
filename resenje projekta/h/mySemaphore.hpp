//
// Created by os on 9/7/22.
//

#ifndef PROJECT_BASE_V1_1_MYSEMAPHORE_HPP
#define PROJECT_BASE_V1_1_MYSEMAPHORE_HPP

#include "../h/tcb.hpp"
#include "../h/semQueue.hpp"
#include "../h/riscv.hpp"
#include "syscall_c.h"


class MySemaphore {
public:
    explicit MySemaphore(unsigned short init = 1):value(init){  queue = new SemQueue(); }
    ~MySemaphore() {
        delete queue;
        queue = nullptr;
    }
    static int createSem(sem_t* handle, unsigned init);
    int freeSem();  //odblokira sve niti koje su blokirane na semaforu
    int wait();
    int signal();

    int getValue()const{return value;}

protected:
    void block();
    void unblock();

private:
    int value;
    SemQueue* queue;
};


#endif //PROJECT_BASE_V1_1_MYSEMAPHORE_HPP
