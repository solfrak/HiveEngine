#pragma once

#include <hvpch.h>
#include <bitset>

namespace hive {

    enum class WindowConfigurationOptions 
    {
        FULLSCREEN,
        CURSOR_DISABLED,
        RESIZABLE
    };

    class HAPI WindowConfiguration 
	{
	public:
        void set(WindowConfigurationOptions flag, bool value);

        bool has(WindowConfigurationOptions flag);

        void toggle(WindowConfigurationOptions flag);

        void clear();

        WindowConfiguration operator^(const WindowConfiguration &other) const;

        constexpr static int MAX_BIT = 24;
    private:
        std::bitset<MAX_BIT> m_windowFlags;
    };
}
