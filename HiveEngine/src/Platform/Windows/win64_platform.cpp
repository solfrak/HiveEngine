#include <hvpch.h>


#ifdef HIVE_PLATFORM_WINDOWS
#include <Core/Platform.h>

#include <windows.h>
namespace hive
{
    u64 timer_frequency = -1.0f;

    void platform_sleep(const f64 time_seconds)
    {
        Sleep(static_cast<u64>(time_seconds * 1000));
    }

    void platform_init_timer()
    {
        if(timer_frequency == -1)
        {
            QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(&timer_frequency));
        }
    }

    u64 platform_get_timer_value()
    {
        u64 value;
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&value));
        return value;
    }

    u64 platform_get_timer_frequency()
    {
        return timer_frequency;
    }

}

#endif