#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "resourses.h"
#include "asteroid.h"
#include "factory.h"

Factory factories[(int)Factories::size] = {0};
Asteroid asteroids[1] = {0};
bool newAsteroid = false;
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
    printf("Production.\n");
    printf ("\t%s \n", resString);
    int demand[(int)Resources::size] = {0};
    int supply[(int)Resources::size] = {0};
    float quotient[(int)Resources::size] = {0};

    // Calculate supply and demand.
    for (int fac = 0; fac < (int)Factories::size; fac++ )
    {
        factories[fac].efficiency = 1;
        for (int res = 0; res < (int)Resources::size ; res++)
        {
            demand[res] += (factories[fac].input[res] * factories[fac].amount);
            supply[res] += (factories[fac].output[res] * factories[fac].amount);
        }
        printRes("In: \t", factories[fac].input);
        printRes("Out: \t",factories[fac].output);
    }

    // Calculate supply/demand quotient.
    for (int res = 0; res < (int)Resources::size; res ++ )
    {
        //stockpile[res] = 0;
        if (demand[res] == 0){ 
            quotient[res] = 1; 
        } else {
            quotient[res] = (supply[res] + stockpile[res])/demand[res];
        }
        printf("%f, ", quotient[res]);
    }
    printf("\n");

    // Calculate factory efficiency.
    for (int fac = 0; fac < (int)Factories::size; fac++ )
    {
        factories[fac].efficiency = 1;
        for (int res = 0; res < (int)Resources::size ; res++)
        {
            if (factories[fac].input[res])
            {
                if (quotient[res] < factories[fac].efficiency)
                {
                    float eff = quotient[res];
                    if (quotient[res] > 1) { eff = 1; }
                    if (quotient[res] < 0) { eff = 0; }

                    factories[fac].efficiency = eff;
                }
            }
        }
    }
    printf("\n");

    // Calculate production.
    for (int fac = 0; fac < (int)Factories::size; fac++ )
    {
        for (int res = 0; res < (int)Resources::size ; res++)
        {
            stockpile[res] -= (factories[fac].input[res] * factories[fac].amount * factories[fac].efficiency);
            stockpile[res] += (factories[fac].output[res] * factories[fac].amount * factories[fac].efficiency);
        }
    }

    // Calculate mining.
    printf("Mining.\n");
    for (int res = 0; res < (int)Resources::raw ; res++)
    {
        float percentage = (float)asteroids[0].resourses[res] / (float)asteroids[0].mass;
        int mined = (stockpile[(int)Resources::raw] * percentage);
        stockpile[res] += mined;
        asteroids[0].resourses[res] -= mined;
    }
    if (stockpile[(int)Resources::raw] == 0) { newAsteroid = true; }
    stockpile[(int)Resources::raw] = 0;

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

Asteroid generateAsteroid()
{
    Asteroid asteroid = {0};

    int size = rand() %(int)1e+6 + 1e+5;
    int type = (int)AteroidType::s;
    switch (type)
    {
    case (int)AteroidType::s: // 17%
        asteroid.resourses[(int)Resources::silicon] = ((rand() %100)*2 + 200) * size /100; // 2-4
        asteroid.resourses[(int)Resources::iron] = ((rand() %100)) * size / 100; // 0-1
        asteroid.resourses[(int)Resources::nickel] = ((rand() %100)) * size / 100; // 0-1
        asteroid.resourses[(int)Resources::magnesium] = (((rand() %100)) / 10) * size / 100; // 0-0.1
        break;
    case (int)AteroidType::c:
        break;
    case (int)AteroidType::m:
        break;
    
    default:
        break;
    }

    printf("Asteriod;\n");
    for (int i = 0 ; i < (int)Resources::raw ; i++)
    {
        asteroid.mass += asteroid.resourses[i];
        printf("Res: %u, Mass: %u \n", i, asteroid.resourses[i]);
    }

    printf("Mass: %i, size: %i\n", asteroid.mass, size);


    return asteroid;
}

int main()
{
    srand (time(0));

    createFactories();
    asteroids[0] = generateAsteroid();

    for (int i = 0; i < 10 ; i++)
    {
        printf("Tick: %i\n", i);
        if (newAsteroid == true)
        {
            asteroids[0] = generateAsteroid();
            newAsteroid = false;
        }
        tick();
    }
    return 0;
}