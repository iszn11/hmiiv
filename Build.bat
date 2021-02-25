@ECHO OFF

REM "build" to make a release build
REM "build debug" to make a debug build
REM "build run" to make a release build and immediately run with APP_CMD_ARGS

SET APP_EXE_NAME=Hmiiv.exe
SET APP_CMD_ARGS=test.png
SET SOURCES=App.c Gl.c Main.c Memory.c System.c Win32.c stb_image.c

IF NOT DEFINED INCLUDE CALL "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"

REM /O2                      Maximize Speed
SET CL_FLAGS_RELEASE=/O2
REM /arch:AVX                Minimum CPU architecture
REM /EHa-                    Disable exceptions
REM /fp:fast                 Optimize floating-point code for speed and space
REM /DUNICODE                Define "UNICODE"
REM /D_UNICODE               Define "_UNICODE"
REM /GA                      Optimize for Windows Application (faster TLS)
REM /GR-                     Disable RTTI
REM /Fe                      Name EXE File
REM /Fd                      PDB file location
REM /Fo                      Object files location
REM /Zi                      Produce seperate PDB file
REM /nologo                  Suppress Startup Banner
REM /TC                      Treat all files as C source files
REM /W4                      Display all level 4 warnings
REM /WX                      Treat all compiler warnings as errors
REM /wd4100                  Disable warning C4100 'identifier' : unreferenced formal parameter
REM /wd4459                  Disable warning C4459 declaration of 'identifier' hides global declaration
REM /utf-8                   Set Source and Executable character sets to UTF-8
REM /GS-                     Disable Buffer Security Check
REM /Gs9999999               Control Stack Checking Calls
SET CL_FLAGS=/arch:AVX /EHa- /fp:fast /DUNICODE /D_UNICODE /GA /GR- /Fe"bin\%APP_EXE_NAME%" /Fd"bin\\" /Fo"obj\\" /Zi /nologo /TC /W4 /WX /wd4100 /wd4459 /utf-8 /GS- /Gs9999999
REM /DEBUG:FASTLINK          Create debug info with faster method
REM /INCREMENTAL:NO          Disable incremental linking (on by default)
REM /NODEFAULTLIB            Don't link to any libraries by default
REM /SUBSYSTEM:WINDOWS       Application does not require a console
REM /STACK:0x100000,0x100000 Reserve and commit 1MiB of stack
SET LINK_FLAGS=/DEBUG:FASTLINK /INCREMENTAL:NO /NODEFAULTLIB /SUBSYSTEM:WINDOWS /STACK:0x100000,0x100000 kernel32.lib user32.lib gdi32.lib shell32.lib opengl32.lib

IF NOT "%~1"=="debug" SET CL_FLAGS=%CL_FLAGS_RELEASE% %CL_FLAGS%

MKDIR bin 2> NUL
MKDIR obj 2> NUL
DEL "bin\\%APP_EXE_NAME%" 2> NUL
cl %CL_FLAGS% %SOURCES% /link %LINK_FLAGS%
IF "%~1"=="run" START "" "bin\%APP_EXE_NAME%" "%APP_CMD_ARGS%"
