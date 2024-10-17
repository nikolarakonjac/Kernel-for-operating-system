//
// Created by os on 8/28/22.
//

#ifndef PROJECT_BASE_V1_0_SYSCALL_C_H
#define PROJECT_BASE_V1_0_SYSCALL_C_H

#include "../lib/hw.h"
#include "../lib/console.h"
#include "../lib/mem.h"

void* mem_alloc(size_t size);

int mem_free(void*);

int getThreadId();


class TCB;
typedef TCB* thread_t;
int thread_create (thread_t* handle, void(*start_routine)(void*), void* arg);

void thread_dispatch();

int thread_exit();



class MySemaphore;
typedef MySemaphore* sem_t;
int sem_open(sem_t* handle, unsigned init);

int sem_close(sem_t handle);

int sem_wait(sem_t id);

int sem_signal(sem_t id);

void putc(char c);

const int EOF=-1;
char getc();

void changeMode();


#endif //PROJECT_BASE_V1_0_SYSCALL_C_H





