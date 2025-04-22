#ifndef MEMORY_H
#define MEMORY_H

void* AllocateMemory(size_t size);
char* AllocateMemoryToStr(char* text);
void ResizeAllocatedMemory(void*& ptr, size_t size);

#endif