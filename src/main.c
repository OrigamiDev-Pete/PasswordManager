#include <stdio.h>

#include "Compression.h"
#include "util.h"

int main(void)
{
    IntArray *arr = newIntArray();
    intArrayAppend(arr, 1);
    intArrayAppend(arr, 2);
    intArrayAppend(arr, 3);
    intArrayAppend(arr, 4);
    printIntArray(arr);

    String *string = newString(NULL); /* empty String */
    stringAppend(string, "Appending to the string");
    printString(string);

    String *string2 = newString("Setting the string at initialisation");
    printString(string2);

    printf("Enter a string> ");
    String *stdRead = readString(); /* A string can be created directly from stdin */
    printString(stdRead);

    free(string);
    free(string2);
    free(stdRead);

    return 0;
}