#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum class Resources {
    // Atoms
    hydrogen, helium, carbon, oxygen, magnesium, aluminium, silicon, iron, cobolt, nickel, 
    // Molecules
    water, raw, 
    // Other
    power, people, size
};

enum class AteroidType {
    s, c, m, size
};

const char* resString = "hydrogen, oxygen, iron, water, power, size";

enum class Factories {
    automaticMiner, powerplant, electrolysis, size
};

struct Factory
{
    int amount = 0;
    // Input
    int input[(int)Resources::size] = {0};
    // Output
    int output[(int)Resources::size] = {0};
};

struct Asteroid
{
    int resrourses[(int)Resources::size] = {0};
};

Factory factories[(int)Factories::size] = {0};
Asteroid asteroids[1] = {0};
int stockpile[(int)Resources::size] = {0};

void printRes(const char* text, int res[(int)Resources::size])
{
    printf(text);

    for (int i = 0; i < (int)Resources::size ; i++)
    {
        printf("%i, \t", res[i]);
    }

    printf("\n");
}

void tick()
{
    printf ("\t%s \n", resString);
    for (int fac = 0; fac < (int)Factories::size ; fac++ )
    {
        for (int res = 0; res < (int)Resources::size ; res++)
        {
            stockpile[res] -= (factories[fac].input[res] * factories[fac].amount);
            stockpile[res] += (factories[fac].output[res] * factories[fac].amount);
        }

        printRes("In: \t", factories[fac].input);
        printRes("Out: \t",factories[fac].output);
    }

    printRes("Stock: \t", stockpile);
}

void createFactories()
{
    factories[(int)Factories::automaticMiner].amount = 1;
    factories[(int)Factories::automaticMiner].input[(int)Resources::power] = 2;
    factories[(int)Factories::automaticMiner].output[(int)Resources::raw] = 10;

    factories[(int)Factories::powerplant].amount = 1;
    factories[(int)Factories::powerplant].input[(int)Resources::hydrogen] = 2;
    factories[(int)Factories::powerplant].output[(int)Resources::power] = 10;

    factories[(int)Factories::electrolysis].amount = 1;
    factories[(int)Factories::electrolysis].input[(int)Resources::water] = 1;
    factories[(int)Factories::electrolysis].input[(int)Resources::power] = 1;
    factories[(int)Factories::electrolysis].output[(int)Resources::hydrogen] = 2;
    factories[(int)Factories::electrolysis].output[(int)Resources::oxygen] = 1;
}

void generateAsteroid()
{
    int size = rand() %(int)1e+6 + 1e+5;
    int type = (int)AteroidType::s;
    switch (type)
    {
    case (int)AteroidType::s: // 17%
        asteroids[0].resrourses[(int)Resources::silicon] = (rand() %2+2) * size; // 2-4
        asteroids[0].resrourses[(int)Resources::iron] = (rand() %1) * size; // 0-1
        asteroids[0].resrourses[(int)Resources::nickel] = (rand() %1) * size; // 0-1
        asteroids[0].resrourses[(int)Resources::magnesium] = (rand() %1 / 10) * size; // 0-0.1
        break;
    case (int)AteroidType::c:
        break;
    case (int)AteroidType::m:
        break;
    
    default:
        break;
    }

    int mass = 0;
    for (int i = 0 ; i < (int)Resources::raw ; i++)
    {
        mass += asteroids[0].resrourses[i];
    }

    printf("Mass: %i.\n", mass);
}

int main()
{
    srand (time(NULL));

    createFactories();
    generateAsteroid();

    for (int i = 0; i < 1 ; i++)
    {
        printf("Tick: %i", i);
        tick();
    }
    return 0;
}