//
// Created by os on 8/30/22.
//

#ifndef PROJECT_BASE_V1_0_TCB_HPP
#define PROJECT_BASE_V1_0_TCB_HPP

#include "../lib/hw.h"
#include "../h/scheduler.hpp"
typedef TCB* thread_t;  //pokazivac na moju klasu TCB zovemo thread_t

class TCB {

public:
    static TCB *running;
    static uint64 id_counter;

    ~TCB() {
        //printString("usao u destruktor");
        //printInteger(getId());
        //printString("\n");
        delete[] stack;
        stack = nullptr;
        this->setFinished(true);
    }

    static void thread_exit(){
        //gasi tekucu nit
        delete running;
    }

    using Body = void (*)(void*);

    bool isFinished()const { return finished;}

    void setFinished(bool value){ finished = value;}

    uint64 getId(){ return id; }

    uint64 getTimeSlice()const {return timeSlice;}

    static void yield();

    //static TCB* createThread(Body body,void* arg, void* stack_space);
    static int createThread(thread_t* handle,Body body,void* arg, void* stack_space);

    void* getBodyArgument(){ return body_argument;}

    void setStartFlag(bool value){ start_flag = value;}

    bool getStartFlag()const { return start_flag;}

    uint64 getId()const{ return id;}

private:

    TCB(Body body,void* arg, void* stack_space):
    body_argument(arg),
    body(body),
    stack( body != nullptr ? (uint64*)stack_space : nullptr),
    // ako je pokrenuta pocetna nit koja ima svoj stek, ne trebamo i mi da joj alociramo stek
    context({
         (uint64)&threadWrapper,    //povratak iz funkcije ili prekida; prvi put se vraca na izvrsavanje fje
         stack != nullptr ? (uint64)&stack[DEFAULT_STACK_SIZE] : 0
    }),
    timeSlice(DEFAULT_TIME_SLICE),
    finished(false)
    {
        id = ++id_counter;
        //pocetna nit ne treba da se dodaje u scheduler vec samo treba da promeni kontekst i da procesor nekoj korisnickoj niti
        if(body != nullptr){ Scheduler::put(this); }
    }

    struct Context
    {
        uint64 ra;  // gde treba da se vrati posle poziva fje
        uint64 sp;  // pokazivac na stek
    };

    uint64 id;
    bool start_flag = true;     //da li je nit startovana
    void* body_argument = nullptr;  //argument fje koja se izvrsava
    Body body;  // fja koja se izvrsava
    uint64 *stack;
    Context context;
    uint64 timeSlice;   //koliko perioda tajmera imamo na raspolaganju pre oduzimaja procesora
    bool finished;

    static uint64 timeSliceCounter; //koliko je perioda tajmera proslo za running nit

    friend class Riscv;

    friend class MySemaphore;

    static void contextSwitch(Context* oldContext, Context* runningContext);

    static void dispatch();

    static void threadWrapper();

};


#endif //PROJECT_BASE_V1_0_TCB_HPP
