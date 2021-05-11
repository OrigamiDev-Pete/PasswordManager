#include "io.h"

#include <stdio.h>


int readInt(void)
{
    int temp;
    while (scanf("%d", &temp) != 1)
        getchar(); /* consumes non-int characters */
        
    while (getchar() != '\n'); /* flush the input */
    return temp;
}
