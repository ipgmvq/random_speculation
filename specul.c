#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_NUMBER	40000
#define CYCLES		100000
#define LEVERAGE	2.0
#define PATH		"data.txt"

int main()
{
    srand(time(NULL));
    int i = 0, belowZero = 0;
    double tempStep, cumul = 0.0, cumulStep = 0.0;
    double closePrices[MAX_NUMBER];
    double logClosePrices[MAX_NUMBER];
    FILE * handle = fopen(PATH, "r");
    if (handle == NULL) exit(1);
    while(fscanf(handle, "%lf\n", &closePrices[i])!=EOF)
    {
        logClosePrices[i] = log(closePrices[i]);
        if(++i >= MAX_NUMBER) break;
    }
    fclose(handle);
    printf("Investor's wealth grew by %.2f times\n", closePrices[i-1]/closePrices[0]);
    for(int cycle = 0; cycle < CYCLES; ++cycle) 
    {
        cumulStep = 0.0;
        for(int j = 1; j < i; ++j)
        {
            tempStep = (logClosePrices[j] - logClosePrices[j-1]) * ((double) (rand() % 2) );
            tempStep = log((exp(tempStep) - 1.0) * LEVERAGE + 1.0);
            cumulStep += tempStep;
        }
        if(cumulStep < 0.0) ++belowZero;
        cumul += cumulStep;
    }
    printf("Speculator's wealth grew by %.2f times with %.2f:1 leverage\nThe probability of speculator's being non-profitable is %.2f%%\n", exp(cumul/CYCLES), LEVERAGE, 100.0 * ((double) belowZero)/((double) CYCLES));
    return 0;
}

