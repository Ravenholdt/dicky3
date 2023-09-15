#include <stdio.h>

enum class Resources {
    hydrogen, oxygen, iron, water, power, size
};

const char* resString = "hydrogen, oxygen, iron, water, power, size";

enum class Factories {
    powerplant, electrolysis, size
};

struct Factory
{
    // Input
    int input[(int)Resources::size] = {0};
    // Output
    int output[(int)Resources::size] = {0};
};

Factory factories[(int)Factories::size] = {0};
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
            stockpile[res] -= factories[fac].input[res];
            stockpile[res] += factories[fac].output[res];
        }

        printRes("In: \t", factories[fac].input);
        printRes("Out: \t",factories[fac].output);
    }

    printRes("Stock: \t", stockpile);
}

void createFactories()
{
    factories[(int)Factories::powerplant].input[(int)Resources::hydrogen] = 2;
    factories[(int)Factories::powerplant].output[(int)Resources::power] = 10;

    factories[(int)Factories::electrolysis].input[(int)Resources::water] = 1;
    factories[(int)Factories::electrolysis].input[(int)Resources::power] = 1;
    factories[(int)Factories::electrolysis].output[(int)Resources::hydrogen] = 2;
    factories[(int)Factories::electrolysis].output[(int)Resources::oxygen] = 1;
}

int main()
{
    createFactories();

    tick();
    return 0;
}