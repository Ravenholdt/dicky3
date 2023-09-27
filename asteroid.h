#pragma once

#include "resourses.h"

enum class AteroidType {
    s, c, m, size
};

struct Asteroid
{
    int mass;
    int resourses[(int)Resources::size] = {0};
};