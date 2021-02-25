#pragma once

void* Alloc(u64 bytes);
void* Realloc(void* ptr, u64 bytes);
void Dealloc(void* ptr);
