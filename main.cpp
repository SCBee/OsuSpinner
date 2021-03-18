#include <input.h>
#include <windows.h>
#include <random>

void driver(std::mt19937 &gen)
{
    input::pressKey(0x53, true);
    std::uniform_int_distribution<> distribMove(8, 12); // Range of movement: [lower, upper]
    std::uniform_int_distribution<> distribDel(5, 15); // Range of delay: [lower, upper]

    while (GetAsyncKeyState(VK_SHIFT) & 0x8000)
    {
        int val = distribMove(gen);
        int delay = distribDel(gen);

        for (int i = 0; i < 10; ++i)
        {
            input::moveMouse(val, -val);
        }
        Sleep(delay);

        for (int i = 0; i < 10; ++i)
        {
            input::moveMouse(-val, -val);
        }
        Sleep(delay);

        for (int i = 0; i < 10; ++i)
        {
            input::moveMouse(-val, val);
        }
        Sleep(delay);

        for (int i = 0; i < 10; ++i)
        {
            input::moveMouse(val, val);
        }
        Sleep(delay);
    }

    input::pressKey(0x53, false);
}

#include <shape.h>
void driver_fancy()
{

}

#include <iostream>
int main(int, char**)
{
    bool start = true;
    bool toggle = false;
    std::random_device rd;
    std::mt19937 gen(rd());

    driver_fancy();

    while (start)
    {
        // spin 2 win
        if (toggle && (GetAsyncKeyState(VK_SHIFT) & 0x8000))
        {
            driver(gen);
        }

        // Kill switch
        if (GetKeyState(VK_END) & 0x8000)
        {
            return 0;
        }

        // Toggle
        if (GetKeyState(VK_HOME) & 0x80)
        {
            system("cls");
            if (toggle)
            {
                toggle = !toggle;
                std::cout << "Off\n";
            }
            else
            {
                toggle = !toggle;
                std::cout << "On\n";
            }
            Sleep(250);
        }
    }

    return 0;
}