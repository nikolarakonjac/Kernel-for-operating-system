//
// Created by os on 8/31/22.
//

#ifndef PROJECT_BASE_V1_0_SYSCALL_CPP_H
#define PROJECT_BASE_V1_0_SYSCALL_CPP_H

#include "../h/syscall_c.h"
#include "../lib/hw.h"
#include "../h/tcb.hpp"
#include "../h/scheduler.hpp"

typedef TCB*  thread_t;

class Thread {

public:
    Thread(void (*body)(void*), void* arg);

    int start();

    static void dispatch();

    //virtual ~Thread(){ thread_exit();}

    virtual ~Thread(){ delete myhandle;}

    thread_t getHandle()const{ return myhandle; }



protected:
    Thread();
    virtual void run(){}

private:
    thread_t myhandle;  //rucka do tcb objekta

    static void wrapper(void* thread_pointer);

};


class Semaphore{
public:
    Semaphore(unsigned init=1){
        sem_open(&myHandle,init);
    }

    virtual ~Semaphore(){ sem_close(myHandle);}

    int wait(){ return sem_wait(myHandle);}

    int signal(){ return sem_signal(myHandle);}


private:
    sem_t myHandle;
};





#endif //PROJECT_BASE_V1_0_SYSCALL_CPP_H
