#ifdef _WIN32
#include <windows.h>

#endif

#include <iostream>
#include <vector>
#include "fogpi/Math.hpp"
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "Dice.hpp"
#include "Entity.hpp"
#include "Room.hpp"
#include "Player.hpp"

int Add(int &_a, int &_b)
{
    _a = _a * 2;
    return _a + _b;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));

    Room room;
    room.Load("assets/level_1.map");

    while(true)
    {
        room.Update();
    }
  
    return 0;
}