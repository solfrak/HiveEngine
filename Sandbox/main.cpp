#include <Core/WIndow/Window.h>
int main()
{
    hive::Window window(900, 600, "Hive", hive::FLAG_WINDOW_RESIZABLE | hive::FLAG_WINDOW_DECORATED);
    while(!window.shouldClose())
    {
        window.pollEvents();
    }
}

