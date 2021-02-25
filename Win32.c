#include <Windows.h>

#include "Common.h"

i32 _fltused;

#pragma function(memset)
void* memset(void* const dest, const i32 c, u64 count)
{
	c8* bytes = (c8*)dest;
	while (count--)
	{
		*bytes++ = (c8)c;
	}
	return dest;
}

#pragma function(memcpy)
void *memcpy(void* dest, const void* src, u64 count)
{
	c8* dest8 = (c8*)dest;
	const c8* src8 = (const c8*)src;
	while (count--)
	{
		*dest8++ = *src8++;
	}
	return dest;
}

i32 main(HINSTANCE hInstance, i32 nCmdShow);

void WinMainCRTStartup()
{
	const HINSTANCE hInstance = GetModuleHandleW(NULL);

	STARTUPINFO si;
	GetStartupInfoW(&si);

	const i32 nCmdShow = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT;

	const i32 exitCode = main(hInstance, nCmdShow);

	ExitProcess(exitCode);
}
