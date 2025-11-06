#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

#include "Util.h"

/// <summary>
/// Stack Allocator Allocator: <para/>
/// Has a fixed capacity, determined on initialization. <para/>
/// A header pointing to the previous memory location is added to the stack. <para/>
/// Memory can be freed in reverse order in which they were added. (LIFO) <para/>
/// 
/// Known Issues: <para/> 
///		The address and the value of an allocated std::string gives unexpected results. <para/>
///		I am unsure how to free the memory reserved on allocation
///			delete[] in dtor?
/// </summary>
class StackAllocator
{
	struct StackAllocator_Header
	{
		uint16_t headerPadding;
		uint16_t previousAllocOffset;
	};

public:
	unsigned char* buffer;
	size_t capacity;
	uintptr_t topPointer;
	uintptr_t lastAllocPtr;

	~StackAllocator();

	inline size_t GetSize() { return topPointer - (uintptr_t)buffer; }

	void Init(size_t aCapacity);
	void Free(void* ptr);
	void FreeAll();

	template<typename T>
	T* Allocate()
	{
		size_t typeSize = sizeof(T);
		size_t remainingSize = capacity - GetSize();
		size_t allocAlignment = alignof(T);
		size_t headerSize = sizeof(StackAllocator_Header);
		std::cout << "Trying to allocate " << typeid(T).name() << " (Size: " << typeSize << " Alignment: " << allocAlignment << ")\n";
		std::cout << "Remaining Size On Allocator: " << remainingSize << "\n";


		std::cout << "Allocating at address: " << topPointer << ". With header size: " << headerSize << "\n";
		size_t allocationSize = headerSize + typeSize;
		size_t alignOffset = (topPointer + headerSize) & (allocAlignment - 1);
		size_t targetAlignOffset = 0;
		if (alignOffset != 0)
		{
			targetAlignOffset = allocAlignment - alignOffset;
			//move top pointer to alignment
			std::cout << "Address " << topPointer + headerSize << " does not match alignment of " << allocAlignment << ". Moving address up by " << allocAlignment - alignOffset << " bytes." << "\n";
			allocationSize += targetAlignOffset;
		}
		std::cout << "Allocation Size: " << allocationSize << ". Remaining Size After Allocation : " << remainingSize - allocationSize << "\n";

		checkf((allocationSize <= remainingSize), "Allocation failed. Size of allocation is bigger than remaining Allocator Size.");

		size_t headerPadding = targetAlignOffset + headerSize;
		uintptr_t allocPtr = topPointer + headerPadding;

		StackAllocator_Header* header = (StackAllocator_Header*)(allocPtr - headerSize);
		header->headerPadding = headerPadding;
		header->previousAllocOffset = topPointer - lastAllocPtr;

		lastAllocPtr = allocPtr;

		topPointer += allocationSize;

		std::cout << "Header allocated at address: " << (uintptr_t)header << "\n";
		std::cout << "Header Padding: " << (size_t)header->headerPadding << "\n";
		std::cout << "Header Previous Alloc Offset: " << (size_t)header->previousAllocOffset << "\n";

		memset((void*)allocPtr, 0, typeSize);
		std::cout << "Return address: " << allocPtr << "\n";
		std::cout << "New Value of Top Pointer: " << topPointer << "\n\n";
		return (T*)allocPtr;
	}
};