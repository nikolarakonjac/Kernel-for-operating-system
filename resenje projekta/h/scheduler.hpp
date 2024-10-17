//
// Created by os on 8/27/22.
//

#ifndef PROJECT_BASE_V1_0_SCHEDULER_HPP
#define PROJECT_BASE_V1_0_SCHEDULER_HPP

#include "list.hpp"


class TCB;
//utility klasa Scheluder ne mora da se inicijalizuje(ima sve staticke atribute i staticke operacije)
//za atribut ima sablonsku listu; lista ciji su elemneti pokazivaci na moju TCB klasu
class Scheduler {
private:
    static List<TCB> readyThreadQueue;

public:
    static TCB *get();

    static void put(TCB *thread);

    static TCB* peekFirst();
};


#endif //PROJECT_BASE_V1_0_SCHEDULER_HPP
