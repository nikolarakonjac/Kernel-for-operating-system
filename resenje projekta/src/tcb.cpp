//
// Created by os on 8/30/22.
//

#include "../h/tcb.hpp"
#include "../h/scheduler.hpp"
#include "../h/riscv.hpp"

TCB *TCB::running = nullptr;
uint64 TCB::id_counter = 0;

void TCB::dispatch() {
    TCB *old = running; //nit koja se trenutrno izvrsava; koja ce prepustiti procesor

    if (!old->isFinished()) { Scheduler::put(old); }    //ako nit nije zavrsila dodaj je u scheduler
    // biranje nove niti;
    bool flag = false;
    while(!flag){
        //izvadi prvu nit iz reda
        TCB* newThread = Scheduler::get();
        //provera da li je nit startovana; moze da se izabere za novu nit samo ona nit koja je startovana
        if(newThread->getStartFlag()){
            flag = true;
            running = newThread;
        }
        else{
            //ako nit nije startovana vrati je na kraj reda
            Scheduler::put(newThread);
        }
    }

    // promena konteksta: u procesorski registar ra i sp se upisu vrednosti iz memorije na koja pokazuju
    // promenljive nove niti ra i sp a u promenljive ra i sp niti koja je izgubila procesor se upisu vrednosti
    // iz registara procesora ra i sp tako da bi proces sledeci put kada dobije procesor
    // nastavio tamo gde je stao sa svojim podacim na koje pokazuje sp
    TCB::contextSwitch(&old->context, &running->context);
    //nakon promene konteksta, tok kontrole se ne vraca ovde nego tamo gde registar ra pokazuje(threadWrapper)
}

void TCB::threadWrapper() {
    Riscv::popSppSpie();    //vraca se iz prekidne rutine

    running->body(running->getBodyArgument());  //poziva se fja koja treba da se izvrsava(nad kojom je pokrenuta nit)
    running->setFinished(true); //nakon sto se fja zavrsi, nit je zavrsila svoj posao
    TCB::yield();   //hocemo da se ode ponovo u prekidnu rutinu i da se izabere nova nit
}

void TCB::yield() {
    //namerno promeni kontekst
    uint64 fcode = 0x13;
    asm volatile("mv a0, %0" : : "r" (fcode));  //a0 <- 13
    asm volatile("ecall");
}

/*TCB *TCB::createThread(Body body, void* arg, void *stack_space) {
    return new TCB(body,arg, stack_space);
}*/
int TCB::createThread(thread_t* handle, Body body, void* arg, void *stack_space) {

    *handle =  new TCB(body,arg, stack_space);

    if (*handle != nullptr) return 0;
    return -1;
}

