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
    double cumul = 0.0, cumulStep = 0.0;
    double closePrices[MAX_NUMBER];
    double percentClosePrices[MAX_NUMBER];
    FILE * handle = fopen(PATH, "r");
    if (handle == NULL) exit(1);
    while(fscanf(handle, "%lf\n", &closePrices[i])!=EOF && ++i < MAX_NUMBER);
    fclose(handle);
    for(int n = i-1; n; --n)
        percentClosePrices[n] = log((closePrices[n] / closePrices[n-1] - 1.0) * LEVERAGE + 1.0);
    printf("Investor's wealth grew by %.2f times\n", closePrices[i-1]/closePrices[0]);
    for(int cycle = 0; cycle < CYCLES; ++cycle) 
    {
        cumulStep = 0.0;
        for(int j = 1; j < i; ++j)
            if(rand() % 2)
                cumulStep += percentClosePrices[j];
        if(cumulStep < 0.0) ++belowZero;
        cumul += cumulStep;
    }
    printf("Speculator's wealth grew by %.2f times with %.2f:1 leverage\nThe probability of speculator's being non-profitable is %.2f%%\n", exp(cumul/CYCLES), LEVERAGE - 1.0, 100.0 * ((double) belowZero)/((double) CYCLES));
    return 0;
}

