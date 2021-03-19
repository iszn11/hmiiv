#include <Windows.h>
#include <windowsx.h>
#include <gl/GL.h>

#define COMMON_NO_ERROR_TYPES
#include "Common.h"

__declspec(dllexport) const u32 NvOptimusEnablement = 1;
__declspec(dllexport) const u32 AmdPowerXpressRequestHighPerformance = 1;

typedef HGLRC (WINAPI *wglCreateContextAttribsARB_t)(HDC hdc, HGLRC hglrc, const i32* attribList);
typedef BOOL (WINAPI *wglChoosePixelFormatARB_t)(HDC hdc, const i32* piAttribIList, const float* pfAttribFList, u32 nMaxFormats, i32* piFormats, u32* nNumFormats);

const u16 CLASS_NAME[] = L"Hmiiv";
const u16 WINDOW_NAME[] = L"Hmiiv";

const i32 WINDOW_WIDTH = 1280;
const i32 WINDOW_HEIGHT = 720;

void InitGl();
void SystemInit(HWND hwnd);
bool Init(const u16* filepath);
void Draw();
void Deinit();
void OnResize(i32 width, i32 height);
void OnDrag(i32 dragX, i32 dragY);
void OnScroll(i32 scrollDelta, i32 mouseX, i32 mouseY);

static void InitExtensions();
static void Frame();
static i64 WindowProc(HWND hwnd, u32 msg, u64 wParam, i64 lParam);

static bool isDragging;
static i32 mouseX;
static i32 mouseY;

static bool initialized;
static HDC hdc;
static HINSTANCE hInstance;
static wglCreateContextAttribsARB_t wglCreateContextAttribsARB;
static wglChoosePixelFormatARB_t wglChoosePixelFormatARB;
static LARGE_INTEGER counterFreq;
static LARGE_INTEGER lastCounter;

i32 main(const HINSTANCE _hInstance, const i32 nCmdShow)
{
	QueryPerformanceFrequency(&counterFreq);

	hInstance = _hInstance;

	const WNDCLASSEXW wc = {
		.cbSize = sizeof(WNDCLASSEXW),
		.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		.lpfnWndProc = WindowProc,
		.hInstance = _hInstance,
		.hCursor = LoadCursorW(NULL, IDC_ARROW),
		.lpszClassName = CLASS_NAME
	};

	RECT rect = {
		.right = WINDOW_WIDTH,
		.bottom = WINDOW_HEIGHT
	};
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);

	const ATOM classAtom = RegisterClassExW(&wc);

	const HWND hwnd = CreateWindowExW(
		0,
		MAKEINTATOM(classAtom),
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
		NULL,
		NULL,
		_hInstance,
		NULL
	);

	hdc = GetDC(hwnd);
	InitExtensions();

	const i32 pixelFormatAttribs[] = {
		0x2001, GL_TRUE,
		0x2010, GL_TRUE,
		0x2011, GL_TRUE,
		0x2003, 0x2027,
		0x2013, 0x202B,
		0x2014, 32,
		0x2022, 24,
		0x2023, 8,
		0
	};

	i32 pixelFormat;
	u32 formatCount;
	wglChoosePixelFormatARB(hdc, pixelFormatAttribs, NULL, 1, &pixelFormat, &formatCount);

	PIXELFORMATDESCRIPTOR pfd;
	DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	const i32 glAttribs[] = {
		0x2091, 4,
		0x2092, 6,
		0x9126, 0x00000001,
		0
	};

	const HGLRC hglrc = wglCreateContextAttribsARB(hdc, NULL, glAttribs);
	wglMakeCurrent(hdc, hglrc);

	QueryPerformanceCounter(&lastCounter);

	InitGl();
	SystemInit(hwnd);
	initialized = true;

	const u16* const cmdLine = GetCommandLineW();
	i32 argc;
	u16** const argv = CommandLineToArgvW(cmdLine, &argc);

	Init(argc >= 2 ? argv[1] : NULL);
	LocalFree(argv);
	Draw();
	ShowWindow(hwnd, SW_SHOW);

	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	Deinit();

	return 0;
}

static void InitExtensions()
{
	const WNDCLASSEXW wc = {
		.cbSize = sizeof(WNDCLASSEXW),
		.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		.lpfnWndProc = DefWindowProcW,
		.hInstance = hInstance,
		.lpszClassName = L"DUMMY"
	};

	const ATOM classAtom = RegisterClassExW(&wc);

	const HWND hwnd = CreateWindowExW(
		0,
		MAKEINTATOM(classAtom),
		L"DUMMY",
		0,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	const HDC hdc = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd = {
		.nSize = sizeof(PIXELFORMATDESCRIPTOR),
		.nVersion = 1,
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.iPixelType = PFD_TYPE_RGBA,
		.cColorBits = 32,
		.cAlphaBits = 8,
		.cDepthBits = 24,
		.cStencilBits = 8
	};

	const i32 pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	const HGLRC hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);

	wglCreateContextAttribsARB = (wglCreateContextAttribsARB_t)wglGetProcAddress("wglCreateContextAttribsARB");
	wglChoosePixelFormatARB = (wglChoosePixelFormatARB_t)wglGetProcAddress("wglChoosePixelFormatARB");

	wglMakeCurrent(hdc, NULL);
	wglDeleteContext(hglrc);
	ReleaseDC(hwnd, hdc);
	DestroyWindow(hwnd);
}

static void Frame()
{
	Draw();
	SwapBuffers(hdc);
}

static i64 WindowProc(const HWND hwnd, const u32 uMsg, const u64 wParam, const i64 lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		if (initialized)
		{
			OnResize(LOWORD(lParam), HIWORD(lParam));
			Frame();
			return 0;
		}
		break;
	case WM_LBUTTONDOWN:
		isDragging = true;
		SetCapture(hwnd);
		mouseX = GET_X_LPARAM(lParam);
		mouseY = GET_Y_LPARAM(lParam);
		return 0;
	case WM_MOUSELEAVE:
	case WM_LBUTTONUP:
		isDragging = false;
		ReleaseCapture();
		return 0;
	case WM_MOUSEMOVE:
	{
		if (!isDragging) return 0;
		i32 curMouseX = GET_X_LPARAM(lParam);
		i32 curMouseY = GET_Y_LPARAM(lParam);
		OnDrag(curMouseX - mouseX, curMouseY - mouseY);
		mouseX = curMouseX;
		mouseY = curMouseY;
		Frame();
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		POINT mouse;
		mouse.x = GET_X_LPARAM(lParam);
		mouse.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hwnd, &mouse);
		OnScroll(GET_WHEEL_DELTA_WPARAM(wParam) / 120, mouse.x, mouse.y);
		Frame();
		return 0;
	}
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
