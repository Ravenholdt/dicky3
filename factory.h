#pragma once

#include "resourses.h"

enum class Factories {
    automaticMiner, powerplant, electrolysis, size
};

struct Factory
{
    int amount = 0;
    float efficiency = 0;
    // Input
    int input[(int)Resources::size] = {0};
    // Output
    int output[(int)Resources::size] = {0};
};