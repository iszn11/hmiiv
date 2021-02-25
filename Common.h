#pragma once

typedef signed char        i8;
typedef signed short       i16;
typedef signed int         i32;
typedef signed long long   i64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef char               c8;

#define bool _Bool
#define false 0
#define true 1

#ifndef COMMON_NO_ERROR_TYPES
#define char __error_char
#define wchar_t __error_wchar_t
#define short __error_short
#define int __error_int
#define long __error_long
#define signed __error_signed
#define unsigned __error_unsigned
#define size_t __error_size_t
#endif

#define TRY(x) do { error = (x); if (error) return error; } while (0)

#ifndef NULL
#define NULL ((void*)0)
#endif
