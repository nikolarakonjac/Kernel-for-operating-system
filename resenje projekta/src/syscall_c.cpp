

#include "../h/syscall_c.h"

/*void* mem_alloc(size_t size){
    //size je broj bajtova
    uint64 rest = size % MEM_BLOCK_SIZE;
    uint64 number_of_needed_blocks = (rest == 0)? size/MEM_BLOCK_SIZE : size/MEM_BLOCK_SIZE + 1;

    //printInteger(number_of_needed_blocks);
    //printString("\n");

    uint64  fcode = 0x01;
    asm volatile("mv a0, %0" : : "r" (fcode));
    asm volatile("mv a1, %0" : : "r" (number_of_needed_blocks));

    asm volatile("ecall");

    uint64 address;
    asm volatile("mv %0, a0" : "=r" (address));

//    printString(reinterpret_cast<const char *>("" + address == 0));
    if(address == 0) return nullptr;
    return reinterpret_cast<void *>(address);
}*/

void* mem_alloc(size_t size){
    return __mem_alloc(size);
}

int mem_free(void* ptr){
    return __mem_free(ptr);
}


int thread_create (thread_t* handle, void(*start_routine)(void*), void* arg){
    uint64 volatile arg1;
    uint64 volatile arg2;
    uint64 volatile arg3;
    uint64 const fcode = 0x11;
    //procita vrednost iz a0 registra u kojem su parametri fje i u upise u lokalne promenljive

    asm volatile("mv %0, a2" : "=r" (arg3));
    asm volatile("mv %0, a1" : "=r" (arg2));
    asm volatile("mv %0, a0" : "=r" (arg1));

    //alocira se prostor za stek
    uint64* stack = reinterpret_cast<uint64 *> (new uint64[DEFAULT_STACK_SIZE]);

    //printString("stek: ");
    //printInteger((uint64)stack);
    //printString("\n");

    //spreme se argumenti sistemskog poziva za u registre a0..a4
    // u registar a4 prebaci vrednost iz promenljive stack
    asm volatile("mv a4, %0" : : "r" (stack));
    asm volatile("mv a3, %0" : : "r" (arg3));
    asm volatile("mv a2, %0" : : "r" (arg2));
    asm volatile("mv a1, %0" : : "r" (arg1));
    asm volatile("mv a0, %0" : : "r" (fcode));

    //printString("pre ecalla");
    asm volatile("ecall");
    //printString("posle ecalla");

    return 0;
}

void thread_dispatch(){
    uint64 fcode = 0x13;
    asm volatile("mv a0, %0" : : "r" (fcode));  //a0 <- 13
    asm volatile("ecall");
}

int thread_exit(){
    uint64 fcode = 0x12;
    asm volatile("mv a0, %0" : : "r" (fcode));  //a0 <- 13
    asm volatile("ecall");

    return 0;
}


int sem_open(sem_t* handle, unsigned init){
    uint64 volatile arg1;
    uint64 volatile arg2;
    uint64  fcode = 0x21;

    //upise u vrednost registra u promenljivu
    asm volatile("mv %0, a1" : "=r" (arg2));
    asm volatile("mv %0, a0" : "=r" (arg1));
    //upise vrednost promenljive u registar

    asm volatile("mv a2, %0" : : "r" (arg2));
    asm volatile("mv a1, %0" : : "r" (arg1));
    asm volatile("mv a0, %0" : : "r" (fcode));

    asm volatile("ecall");
    return 0;
}

int sem_close(sem_t handle){
    uint64 volatile arg1;

    uint64 fcode = 0x22;

    asm volatile("mv %0, a0" : "=r" (arg1));


    asm volatile("mv a1, %0" : : "r" (arg1));
    asm volatile("mv a0, %0" : : "r" (fcode));

    asm volatile("ecall");
    return 0;
}

int sem_wait(sem_t id){
    uint64 volatile arg1;

    uint64  fcode = 0x23;
    asm volatile("mv %0, a0" : "=r" (arg1));

    asm volatile("mv a1, %0" : : "r" (arg1));
    asm volatile("mv a0, %0" : : "r" (fcode));

    asm volatile("ecall");
    return 0;
}

int sem_signal(sem_t id){
    uint64 volatile arg1;

    uint64 fcode = 0x24;

    asm volatile("mv %0, a0" : "=r" (arg1));

    asm volatile("mv a1, %0" : : "r" (arg1));
    asm volatile("mv a0, %0" : : "r" (fcode));

    asm volatile("ecall");
    return 0;
}

void putc(char c){
    __putc(c);
}

char getc(){
    uint64 const fcode = 0x41;
    asm volatile("mv a0, %0" : : "r" (fcode));

    asm volatile("ecall");

    char c;
    asm volatile("mv %0, a0" : "=r" (c)); // c <- a0
    //char c = __getc();
    return c;
}

void changeMode(){
    uint64 fcode = 0x55;
    asm volatile("mv a0, %0" : : "r" (fcode));
    asm volatile("ecall");
}

int getThreadId(){
    uint64 fcode = 0x100;
    asm volatile("mv a0, %0" : : "r" (fcode));
    asm volatile("ecall");
    return 0;
}










