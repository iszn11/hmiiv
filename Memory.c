#include <Windows.h>

#include "Common.h"
#include "Memory.h"

void* Alloc(const u64 bytes)
{
	void* ret = HeapAlloc(GetProcessHeap(), 0, bytes);
	return ret;
}

void* Realloc(void* const ptr, const u64 bytes)
{
	if (!ptr) return Alloc(bytes);
	void* ret = HeapReAlloc(GetProcessHeap(), 0, ptr, bytes);
	return ret;
}

void Dealloc(void* const ptr)
{
	HeapFree(GetProcessHeap(), 0, ptr);
}
