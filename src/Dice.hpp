#pragma once
#include "fogpi/fogpi.hpp"
#include <vector>

struct Die
{
    int sides = 0;
};

//int RollDice(int sides)
//{
//    int rolledNumber = random_int(1,sides);
//    return rolledNumber;
//}
//struct RollStats
//{
//    int total = 0;
//    float average = 0.0f;
//    int min = 0;
//    int max = 0;
//};
//
//void PrintRollStats(RollStats &_stats) {
//    printf("#### ROLL STATS ####\n");
//    printf("Total: %i\n", _stats.total);
//    printf("Min: %i\n", _stats.min);
//    printf("Max: %i\n", _stats.max);
//    printf("Average: %f\n", _stats.average);
//}
//
//RollStats RollDice(std::vector<Die> _dice)
//{
//    RollStats stats = {};
//
//    for (Die die : _dice)
//    {
//        stats.min += 1;
//        stats.max += die.sides;
//
//        stats.average += die.sides / 2.0f;
//
//        int roll = random_int(1, die.sides);
//        stats.total += roll;
//    }
//
//    return stats;
//}