//
// Created by os on 9/9/22.
//

#include "../h/memoryAllocator.hpp"
//#include "../h/print.h"

//List<MemoryAllocator::Frame> MemoryAllocator::freeFrameList;
//List<MemoryAllocator::Frame> MemoryAllocator::allocatedFramesList;

/*void* MemoryAllocator::head = const_cast<void *> (HEAP_START_ADDR);
uint64 MemoryAllocator::numOfUsedBlocks = 0;


uint64 MemoryAllocator::memAlloc(uint64 numOfBlocks) {

    uint64 endOfUsedMemory = (uint64)HEAP_START_ADDR + numOfUsedBlocks*MEM_BLOCK_SIZE;

    if(endOfUsedMemory + numOfBlocks* MEM_BLOCK_SIZE > (uint64)HEAP_END_ADDR) {
        printString("Out of memory exception!");
        return 0;
    }

    numOfUsedBlocks += numOfBlocks;
    return endOfUsedMemory;
}*/


