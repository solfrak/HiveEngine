#pragma once

#include <hvpch.h>
namespace hive
{
    //Clock
    void platform_sleep(f64 time_seconds);
    void platform_init_timer();
    u64 platform_get_timer_value();
    u64 platform_get_timer_frequency();



}