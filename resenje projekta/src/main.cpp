

#include "../h/riscv.hpp"
#include "../h/tcb.hpp"
#include "../h/syscall_c.h"
#include "../h/syscall_cpp.hpp"


//#include "../test/Threads_C_API_test.hpp" // zadatak 2, niti C API i sinhrona promena konteksta
//#include "../test/Threads_CPP_API_test.hpp" // zadatak 2., niti CPP API i sinhrona promena konteksta

//#include "../test/ConsumerProducer_C_API_test.h" // zadatak 3., kompletan C API sa semaforima, sinhrona promena konteksta
//#include "../test/ConsumerProducer_CPP_Sync_API_test.hpp" // zadatak 3., kompletan CPP API sa semaforima, sinhrona promena konteksta



void userMain(void* arg) {


    //Threads_C_API_test(nullptr); // zadatak 2., niti C API i sinhrona promena konteksta
    //Threads_CPP_API_test(nullptr); // zadatak 2., niti CPP API i sinhrona promena konteksta

    //producerConsumer_C_API(nullptr); // zadatak 3., kompletan C API sa semaforima, sinhrona promena konteksta
    //producerConsumer_CPP_Sync_API(nullptr); // zadatak 3., kompletan CPP API sa semaforima, sinhrona promena konteksta

}

/*
void fa(void*){
    for(int i=0;i<10;i++){
        printString("A  ");
        printInt(TCB::running->getId());
        printString("\n");
    }
}

void fb(void*){
    for(int i=0;i<10;i++){
        printString("B  ");
        printInt(TCB::running->getId());
        printString("\n");
    }
}
void fc(void*){
    for(int i=0;i<10;i++){
        printString("C  ");
        printInt(TCB::running->getId());
        printString("\n");
    }
}

void f(){
    Thread* nit[3];
    nit[0] = new Thread(fa, nullptr);
    nit[1] = new Thread(fb, nullptr);
    nit[2] = new Thread(fc, nullptr);

    for(int i=0; i<3; i++) {
        nit[i]->start();
    }

    while (!(nit[0]->getHandle()->isFinished() && nit[1]->getHandle()->isFinished() &&
    nit[2]->getHandle()->isFinished() )) {
        Thread::dispatch();
    }

    
}
*/
void wrapper(void* arg){
    //changeMode();
    //korisnicki rezim


    //u korisnickom rezimu ne sme da se koristi instrukcija r_sstatus();
    /*uint64 value = Riscv::r_sstatus();
    printInt(value);
    printString("\n");*/

    //f();
    userMain(nullptr);
}

void main(){
    //sistemski rezim
    Riscv::w_stvec((uint64) &Riscv::interruptRoutine);    //upisuje adresu prekidne rutine

    thread_t thread1;
    //idle nit(nit koja nema fju koja treba da izvrsava)
    thread_create(&thread1, nullptr, nullptr);
    TCB::running = thread1;


    thread_t thread2;
    thread_create(&thread2, wrapper, nullptr);

    //promena rezima
    changeMode();

    while (!(thread2->isFinished())) {
        thread_dispatch();
    }


    /*uint64 niz[3];
    niz[0] = 1;

    printInt(niz[0]);*/


    /*List<uint64> *lista = new List<uint64>();

    uint64 a1 = 1;
    uint64 a2 = 2;
    uint64 a3 = 3;


    lista->addFirst(&a1);
    lista->addLast(&a2);
    lista->addLast(&a3);



    for(int i=0;i<lista->listSize();i++){
        printInt(*lista->getData(i));
    }*/

}











































