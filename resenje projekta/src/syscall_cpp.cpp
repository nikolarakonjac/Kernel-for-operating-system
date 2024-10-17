//
// Created by os on 9/8/22.
//

#include "../h/syscall_cpp.hpp"

Thread::Thread(void (*body)(void *), void *arg) {
    thread_create(&myhandle, body, arg);
    myhandle->setStartFlag(false);  //blokira nit; nit moze da se odblokira start metodom
}

int Thread::start() {
    if(getHandle()){
        myhandle->setStartFlag(true);
        return 0;
    }
    return -1;
}

void Thread::dispatch() {
    thread_dispatch();
}

Thread::Thread() {
    thread_create(&myhandle,&(Thread::wrapper),this);
    myhandle->setStartFlag(false);
}

void Thread::wrapper(void *thread_pointer) {
    ((Thread*)thread_pointer)->run();
}



