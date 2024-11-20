//
// Created by samuel on 11/17/24.
//
#include "Memory.h"

int memory_allocated = 0;
void* hmalloc(size_t size)
{
	//TODO: keep reference to memory allocated
	memory_allocated += size;
	return malloc(size);
}

void hfree(size_t size, void* ptr)
{
	//TODO: keep reference to memory allocated
	memory_allocated -= size;
	free(ptr);
}

int getAllocatedMemory()
{
	return memory_allocated;
}
