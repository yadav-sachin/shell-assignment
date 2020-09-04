#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    for (int i = 0; i < 100000000; ++i)
    {
        for (int j = 0; j < 1000; ++j)
            ;
        if (i % 50000 == 0)
            printf("THis is it");
    }
    return 0;
}