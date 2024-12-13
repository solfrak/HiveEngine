#pragma once
#include <hvpch.h>
namespace hive
{
    class Clock
    {
    public:
        Clock();
        void sleep(f64 seconds) const;

        //Getter & Setter
        [[nodiscard]] f64 getTime() const;


    private:
        u64 offset;
    };
}