#pragma once

#include <hvpch.h>
namespace hive
{
    enum class EventType
    {
        MouseMove, MouseButtonDown, MouseButtonUp, MouseScroll, MouseScrollWheel,
        KeyPressed, KeyReleased, KeyTyped,
    };

    //Using this type of struct is powerfull since we don't have to use polymorphism in order to handle events. But it can be more error prone since you have to know exactly the data layout for each type of event
    struct Event
    {
        union {
            i64 i_64[2];
            u64 u_64[2];

            f64 f_64[2];

            i32 i_32[4];
            u32 u_32[4];
            f32 f_32[4];

            i16 i_16[8];

            u16 u_16[8];

            i8 i_8[16];
            u8 u_8[16];

            char c[16];
        } data;

        EventType type;
    };

    //TODO: create some documentation for the different event data layout
    //Key -> i_32[0] key
    //Mouse button -> i_32[0] button
    //Mouse motion -> i32[0](x), i_32[1](y)
}