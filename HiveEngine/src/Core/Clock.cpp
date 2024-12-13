

#include "Clock.h"
#include "Platform.h"

hive::Clock::Clock()
{
    platform_init_timer();
    offset = platform_get_timer_value();
}


void hive::Clock::sleep(const f64 seconds) const
{
    //We sleep for only a % of the time because there is a chance that sleep will go a little bit beyond the time.
    f64 sleep_time = seconds * 0.95f;
    f64 target_time = getTime() + seconds;
    platform_sleep(sleep_time);

    //We just busy wait the rest of the time
    while(getTime() < target_time)
    {

    }
}

f64 hive::Clock::getTime() const
{
    return static_cast<f64>(platform_get_timer_value() - offset) / platform_get_timer_frequency();
}
