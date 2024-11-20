//
// Created by samuel on 11/20/24.
//
#include <Ressource/StackAllocator.h>

#include "Ressource/Memory.h"

struct MyStruct
{
	int x;
};

struct MyOtherStruct
{
	float x, y, z;
	float r, g, b;
};

int main()
{
	std::cout << getAllocatedMemory() << std::endl;
	{
		hive::StackAllocator stack(1024);

		std::cout << getAllocatedMemory() << std::endl;

		int i = 0;
		while (stack.getAvailableSpace() > sizeof(MyOtherStruct))
		{
			i++;
			stack.push(sizeof(MyOtherStruct));
		}

		//As you can see here the allocated memory stay the same (We only ask the kernel once for memory and than we manage it internaly)
		std::cout << getAllocatedMemory() << std::endl;
	}
	std::cout << getAllocatedMemory() << std::endl;
}