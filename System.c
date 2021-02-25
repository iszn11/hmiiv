#include <Windows.h>

#include "Common.h"
#include "Memory.h"
#include "System.h"

static HWND hwnd;

void SystemInit(const HWND _hwnd)
{
	hwnd = _hwnd;
}

void ResizeWindow(const i32 w, const i32 h)
{
	const HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFO monInfo = {
		.cbSize = sizeof(MONITORINFO)
	};
	GetMonitorInfoW(monitor, &monInfo);

	RECT rect = {
		.right = w,
		.bottom = h
	};
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);

	i32 windowW = rect.right - rect.left;
	i32 windowH = rect.bottom - rect.top;

	i32 workW = monInfo.rcWork.right - monInfo.rcWork.left;
	i32 workH = monInfo.rcWork.bottom - monInfo.rcWork.top;

	if (windowW > workW || windowH > workH)
	{
		ShowWindow(hwnd, SW_MAXIMIZE);
	}
	else
	{
		SetWindowPos(hwnd, NULL, 0, 0, windowW, windowH, SWP_NOMOVE | SWP_NOZORDER);
	}
}

bool ReadFileAlloc(const u16* const filename, u8** const ptr, u64* const len)
{
	const HANDLE file = CreateFileW(
		filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (file == INVALID_HANDLE_VALUE) return false;

	// get file size in bytes

	LARGE_INTEGER fileSizeQ;
	if (!GetFileSizeEx(file, &fileSizeQ) || fileSizeQ.HighPart != 0)
	{
		CloseHandle(file);
		return false;
	}
	*len = fileSizeQ.QuadPart;

	// reserve output

	*ptr = Alloc(*len);

	// read file contents

	DWORD bytesRead;
	if (ReadFile(file, *ptr, (DWORD)*len, &bytesRead, NULL) && bytesRead == *len)
	{
		CloseHandle(file);
		return true;
	}
	else
	{
		CloseHandle(file);
		HeapFree(GetProcessHeap(), 0, *ptr);
		return false;
	}
}

void DebugPrint(const c8* const text)
{
	OutputDebugStringA(text);
}
