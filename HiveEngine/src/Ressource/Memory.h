//
// Created by samuel on 11/17/24.
//
#pragma once
#include "hvpch.h"

HAPI void* hmalloc(size_t size);
HAPI void hfree(size_t size, void* ptr);
HAPI int getAllocatedMemory();