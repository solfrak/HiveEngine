//
// Created by samuel on 11/17/24.
//
#include "Memory.h"

void* hmalloc(size_t size)
{
	//TODO: keep reference to memory allocated
	return malloc(size);
}

void hfree(size_t size, void* ptr)
{
	//TODO: keep reference to memory allocated
	free(ptr);
}
