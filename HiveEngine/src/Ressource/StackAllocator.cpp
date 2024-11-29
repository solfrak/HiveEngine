//
// Created by samuel on 11/20/24.
//
#include "StackAllocator.h"
#include "Memory.h"
#include <Debug/Asserts.h>
#include <Debug/Profiler.h>

#include "Engine/Logger.h"

hive::StackAllocator::StackAllocator(size_t size)
{
	m_max_size = size;
	m_current_size = 0;

	m_ptr = hmalloc(size);
	m_current = m_ptr;
}

hive::StackAllocator::~StackAllocator()
{
	TRACE_EVENT("memory", "StackAllocator::~StackAllocator");
	//If it's not 0 this means that someone still hold a reference to a pointer and might cause an undefined behaviour by accessing freed memory
	// HASSERTS(m_current_size == 0);
	hfree(m_max_size, m_ptr);
}

void* hive::StackAllocator::push(size_t size)
{
	TRACE_EVENT("memory", "StackAllocator::push");
	//Make sure that we don't overflow our allocated memory
	HASSERTS(m_current_size + size <= m_max_size);

	void* ptr = m_current;
	m_current = reinterpret_cast<char*>(m_current) + size;
	m_current_size += size;
	return ptr;
}

void hive::StackAllocator::pop(size_t size)
{
	TRACE_EVENT("memory", "StackAllocator::pop");
	//If this failed, this mean you deallocated something with the wrong size (Maybe a child object of a abstract class?)
	HASSERTS(m_current_size - size >= 0);

	m_current = reinterpret_cast<char*>(m_current) - size;
	m_current_size -= size;
}

size_t hive::StackAllocator::getAvailableSpace() const
{
	TRACE_EVENT("memory", "StackAllocator::getAvailableSpace");
	return m_max_size - m_current_size;
}
