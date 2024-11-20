//
// Created by samuel on 11/20/24.
//

#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H
#include <cstddef>
#include <hvpch.h>
namespace hive
{
	class HAPI StackAllocator
	{
	public:

		StackAllocator(size_t size);
		~StackAllocator();

		void* push(size_t size);
		void pop(size_t size);
		size_t getAvailableSpace() const;

	private:
		int m_max_size;
		int m_current_size;
		void* m_current;
		void* m_ptr;
	};


}
#endif //STACKALLOCATOR_H
