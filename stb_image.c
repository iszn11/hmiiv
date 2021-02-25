#include <Windows.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_ONLY_BMP
#define STBI_ONLY_GIF
#define STBI_NO_STDIO
#define STBI_NO_THREAD_LOCALS
#define STBI_NO_HDR
#define STBI_NO_LINEAR
#define STBI_ASSERT(x) do { if (!(x)) __debugbreak(); } while(0)

#define STBI_MALLOC Alloc
#define STBI_FREE Dealloc
#define STBI_REALLOC Realloc

#pragma function(_lrotl)
unsigned long _lrotl(unsigned long value, int shift)
{
	return (value << shift) | ((value) >> (32 - shift));
}

#pragma function(abs)
int abs(int n)
{
	return n >= 0 ? n : -n;
}

void* Alloc(size_t bytes);
void Dealloc(void* ptr);
void* Realloc(void* ptr, size_t bytes);

#include "stb_image.h"
