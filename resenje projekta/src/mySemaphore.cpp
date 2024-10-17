//
// Created by os on 9/7/22.
//

#include "../h/mySemaphore.hpp"


int MySemaphore::wait() {
    //Riscv::lock();  //maskira spoljasnje prekide
    if(--value < 0){ block(); }
    //Riscv::unlock();    //demaskira spoljasnje prekide
    return 0;
}

int MySemaphore::signal() {
    //Riscv::lock();
    if(++value <= 0) { unblock(); }
    //Riscv::unlock();
    return 0;
}

void MySemaphore::block() {
    TCB* old = TCB::running;
    //blokirana nit ne ide u scheduler gde su spremne niti, vec ide u red za cekanje na semaforu
    queue->put(old);
    // biranje nove niti (koja je startovana)
    bool flag = false;
    while(!flag){
        //izvadi prvu nit iz reda
        TCB* newThread = Scheduler::get();
        if(newThread->getStartFlag()){
            flag = true;
            TCB::running = newThread;
        }
        else{
            //ako nit nije startovana vrati je na kraj reda
            Scheduler::put(newThread);
        }
    }
    TCB::contextSwitch(&old->context, &(TCB::running->context));
}

void MySemaphore::unblock() {
    //vadi se nit iz reda cekanja na semafor i prebacuje u red spremnih niti
    //sigurno ima blokiranih niti ako se uslo u ovaj kod, queue nece vratiti nullptr
    TCB* newThread = queue->get();
    Scheduler::put(newThread);
}

int MySemaphore::createSem(sem_t* handle, unsigned init) {
    *handle = new MySemaphore(init);
    if (*handle != nullptr) { return 0; }
    else { return -1; }
}

int MySemaphore::freeSem() {
    int num = queue->queueSize();
    for(int i=0;i<num;i++){
        this->unblock();
    }
    return 0;
}


