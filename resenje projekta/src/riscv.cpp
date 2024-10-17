//
// Created by os on 8/28/22.
//

#include "../h/riscv.hpp"
#include "../lib/console.h"
#include "../h/tcb.hpp"
#include "../h/mySemaphore.hpp"
#include "../h/memoryAllocator.hpp"

typedef TCB* thread_t;


void Riscv::lock() {
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
}

void Riscv::unlock() {
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
}

//fja koja obradjuje prekidnu rutinu
void Riscv::interruptRoutineHandler() {

    //sacuvamo vrednosti registra to jest argumenata koje je postavio sistemski poziv u registre
    uint64 volatile fcode, arg1, arg2, arg3 , arg4;
    asm volatile("mv %0, a0" : "=r" (fcode));   //fcode <- a0
    asm volatile("mv %0, a1" : "=r" (arg1));    // thread_t* handle
    asm volatile("mv %0, a2" : "=r" (arg2));    //void (*function)(void*)
    asm volatile("mv %0, a3" : "=r" (arg3));    //void* arg
    asm volatile("mv %0, a4" : "=r" (arg4));    //void* stack

    uint64 scause = r_scause();     //uzrok prekida koji nam govori zasto je prekid generisan

    if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL){
        // softverski prekid metodom ecall:  u zavisnosti od rezima  U-mode(8) or S-mode(9)

        uint64 volatile sepc = r_sepc() + 4;    //prelazak na sledecu instrukciju; jer procesor ponavlja instr koja je izazvala prekid
        uint64 volatile sstatus = r_sstatus();

        if(fcode == 0x55){
            //prelazi iz sistemskog u korisnicki rezim
            mc_sstatus(SSTATUS_SPP);    //bit spp postavimo na 0; sto znaci da je prekid bio iz korisnickog rezima
                                            // i onda cemo se nakon obrade prekida vratiti u korisnicki rezim

            w_sepc(sepc);   //upise se izracunati sepc(sacuvana vrednost registra pc) za to radimo return
            return;
        }
        /*else if(fcode == 0x01){
            uint64 addres = MemoryAllocator::memAlloc((uint64)arg1);
            asm volatile("mv a0, %0" : : "r" (addres)); //a0 <- addres
        }*/
        else if(fcode == 0x11){
            //sistemski poziv => THREAD_CREATE
            fcode = TCB::createThread( (thread_t*) arg1 ,(TCB::Body)arg2, (void*)arg3, (void*)arg4);
            asm volatile("mv a0, %0" : : "r" (fcode));
        }
        else if(fcode == 0x12){
            //sistemski poziv => THREAD_EXIT
            TCB::thread_exit();
        }
        else if(fcode == 0x13){
            //sistemski poziv => THREAD_DISPATCH
            TCB::dispatch();
        }
        else if(fcode == 0x21){
            //sistemski poziv sem_open
            fcode = MySemaphore::createSem((sem_t*)arg1, (unsigned)arg2);
            asm volatile("mv a0, %0" : : "r" (fcode));
        }
        else if(fcode == 0x22){
            //sistemski poziv sem_close
           auto semPointer = (sem_t)arg1;
           semPointer->freeSem();
        }
        else if(fcode == 0x23){
            //sistemski poziv sem_wait
            auto semPointer = (sem_t)arg1;

            semPointer->wait();
        }
        else if(fcode == 0x24){
            //sistemski poziv sem_signal
            auto semPointer = (sem_t)arg1;
            semPointer->signal();
        }
        else if(fcode == 0x41){
            //sistemski poziv char getc()
            char c = __getc();  //__getc iz lib/conslole.h
            asm volatile("mv a0, %0" : : "r" (c));  //a0 <- c
        }
        else{
            printString("nema taj fcode\n");
            printInt(fcode);
            printString("\n");
        }
        w_sepc(sepc);
        w_sstatus(sstatus);
    }

    else if (scause == 0x8000000000000001UL){
        mc_sip(SIP_SSIP);
    }
    else if (scause == 0x8000000000000009UL){
        console_handler();
    }
    else{
        printString("\nScause: ");
        printInt(scause);
        if(scause == 2){
            printString("   nelegalna instrukcija");
        }
        else if(scause == 5){
            printString("   nedozvoljena adresa citanja");
        }
        else if(scause == 7){
            printString("   nedozvoljena adresa upisa");
        }
    }
}

void Riscv::popSppSpie() {
    asm volatile("csrw sepc, ra");  //registar pc dobija vrednost registar sepc pri povratku iz prekidne rutine
    asm volatile("sret");
}