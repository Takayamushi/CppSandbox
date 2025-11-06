#include "StackAllocator.h"

#include "Util.h"

StackAllocator::~StackAllocator()
{
	delete[] buffer;
}

void StackAllocator::Init(size_t aCapacity)
{
	capacity = aCapacity;
	buffer = new unsigned char[aCapacity] { 0 };
	topPointer = (uintptr_t)buffer;
	lastAllocPtr = topPointer;
	std::cout << "Created Stack Allocator with Capacity: " << capacity << "\n\n";
}

void StackAllocator::Free(void* ptr)
{
	uintptr_t ptrToFree = (uintptr_t)ptr;

	checkf((ptrToFree >= lastAllocPtr), "Out of order de-allocation.")

	std::cout << "Freeing pointer: " << ptrToFree << "\n";

	uintptr_t start = (uintptr_t)buffer;
	uintptr_t end = (uintptr_t)(buffer + capacity);

	checkf((start <= ptrToFree && ptrToFree <= end), "Pointer is not located in this allocator.");

	StackAllocator_Header* header = (StackAllocator_Header*)(ptrToFree - sizeof(StackAllocator_Header));
	std::cout << "Header padding: " << (size_t)header->headerPadding << "\n";
	topPointer = ptrToFree - (size_t)header->headerPadding;
	lastAllocPtr = topPointer - header->previousAllocOffset;
	std::cout << "Top Pointer new location: " << topPointer << "\n";
	std::cout << "Last Allocation Pointer: " << lastAllocPtr << "\n\n";
}

void StackAllocator::FreeAll()
{
	topPointer = (uintptr_t)buffer;
	lastAllocPtr = topPointer;
}
