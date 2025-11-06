#pragma once
#include <iostream>
#include <vector>
#include <iomanip>

#include "Util.h"

/// <summary>
/// Linear Allocator: <para/>
/// Has a fixed capacity, determined on initialization.
/// Memory must all be freed at once. <para/>
/// 
/// Known Issues: <para/> 
///		The address and the value of an allocated std::string gives unexpected results. <para/>
///		I am unsure how to free the memory reserved on allocation
///			delete[] in dtor?
/// </summary>
class LinearAllocator
{
public:
	unsigned char* buffer;
	size_t capacity;
	uintptr_t topPointer;

	~LinearAllocator() { delete[] buffer; }

	inline size_t GetSize() { return topPointer - (uintptr_t)buffer; }

	void Init(size_t aCapacity)
	{
		capacity = aCapacity;
		buffer = new unsigned char[aCapacity] { 0 };
		topPointer = (uintptr_t)buffer;
		std::cout << "Created Linear Allocator with Capacity: " << capacity << "\n\n";
	}

	template<typename T>
	T* Allocate()
	{
		size_t allocSize = sizeof(T);
		size_t remainingSize = capacity - GetSize();
		size_t allocAlignment = alignof(T);
		std::cout << "Trying to allocate on Linear Allocator... \n";
		std::cout << "Size: " << allocSize << "\n";
		std::cout << "Alignment: " << allocAlignment << "\n";
		std::cout << "Remaining Size On Allocator: " << remainingSize << "\n";

		checkf((allocSize <= remainingSize), "Allocation failed. Size of allocation is bigger than remaining Allocator Size.");

		std::cout << "Remaining Size After Allocation: " << remainingSize - allocSize << "\n";
		size_t alignOffset = topPointer & (allocAlignment - 1);
		if (alignOffset != 0)
		{
			//move top pointer to alignment
			std::cout << "Address " << topPointer << " does not match alignment of " << allocAlignment << ". Moving address up by " << allocAlignment - alignOffset << " bytes." << "\n";
			topPointer += allocAlignment - alignOffset;
		}

		uintptr_t ptr = topPointer;
		topPointer += allocSize;
		memset((void*)ptr, 0, allocSize);
		std::cout << "Return address: " << ptr << "\n";
		std::cout << "New Value of Top Pointer: " << topPointer << "\n\n";
		return (T*)ptr;
	}

	void Free(void* ptr)
	{
	}

	void FreeAll()
	{
		topPointer = (uintptr_t)buffer;
	}
};
