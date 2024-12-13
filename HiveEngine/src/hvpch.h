#pragma once


using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;

using f32 = float;
using f64 = double;


#ifdef _WIN64
    #define HIVE_PLATFORM_WINDOWS
    #define HIVE_WINDOWING_RAYLIB
#endif

#ifdef __linux__
    #define HIVE_PLATFORM_LINUX
    #define HIVE_WINDOWING_RAYLIB
#endif
