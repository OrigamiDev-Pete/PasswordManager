#include "util.h"

#include <stdio.h>
#include <stdlib.h>

/* #define DEBUG */

#define internal static

internal void checkAndResizeString(String *string, int newLength);
internal int stringLength(const char *str);
internal void nullTerminate(String *string);

void initString(String *string, const char *val)
{
    if (val == NULL)
    {
        string->length = 0;
        string->capacity = STRING_START_SIZE;
        string->text = malloc(string->capacity);
    }
    else
    {
        string->length = stringLength(val);
        int cap = STRING_START_SIZE;
        while (cap < string->length)
            cap *= 2;
        string->capacity = cap;
        string->text = malloc(string->capacity);

        int i;
        for (i = 0; i < string->length; i++)
        {
            string->text[i] = val[i];
        }
        nullTerminate(string);
    }
}

String* newString(const char *val)
{
    String *string = malloc(sizeof(String));
    initString(string, val);
    return string;
}

String* stringAppend(String *string, const char *val)
{
    if (val == NULL)
    {
        return string;
    }
    checkAndResizeString(string, string->length + stringLength(val));
    int i = 0;
    while (val[i] != '\0' && val[i] != EOF && i < STRING_MAX_SIZE)
    {
        string->text[string->length++] = val[i++];
    }
    nullTerminate(string);
    #ifdef DEBUG
    if (i == STRING_MAX_SIZE)
    {
        puts("stringAppend: Maximum Capacity");
    }
    #endif /* DEBUG */
    
    return string;
}

String* stringAppendChar(String *string, char val)
{

    nullTerminate(string);
    return string;
}

char stringGetChar(String *string, int index)
{
    if (index < string->length)
    {
        return string->text[index];
    }

    #ifdef DEBUG
    puts("stringGetChar: Out of Bounds");
    #endif /* DEBUG */

    return '\0';
}

String* readString(void)
{
    String *string = newString(NULL);
    char c;
    while ((c = getchar()) != '\n' && c != '\0' && c != EOF)
    {
        checkAndResizeString(string, string->length+1);
        string->text[string->length++] = c;
    }
    nullTerminate(string);
    return string;
}

void printString(String *string)
{
    #ifndef DEBUG
    puts(string->text);
    #endif /* DEBUG */

    #ifdef DEBUG
    int i;
    for (i = 0; i < string->length; i++)
    {
        putchar(string->text[i]);
    }
    if (string->text[string->length] == '\0')
        puts("\\0");
    else
        putchar('\n');
    #endif /* DEBUG */
}

void freeString(String *string)
{
    free(string->text);
    free(string);
}

void freeStackString(String *string)
{
    free(string->text);
}

internal void checkAndResizeString(String *string, int newLength)
{
    if (newLength >= string->capacity-1)
    {
        int cap = string->capacity;
        while (cap < newLength)
        {
            cap *= 2;
        }
        String *tmp = string;
        tmp->capacity = cap;
        tmp = realloc(tmp, tmp->capacity);
        if (tmp)
        {
            string->text = tmp->text;
            string->capacity = tmp->capacity;
            string->length = tmp->length;
        }
        else
        {
            puts("checkAndResizeString: Error reallocating memory.");
        }
    }
}

internal int stringLength(const char *str)
{
    int i = 0;
    while (str[i] != '\0' && str[i] != EOF && i < STRING_MAX_SIZE)
    {
        i++;
    }
    #ifdef DEBUG
    if (i == STRING_MAX_SIZE)
        puts("stringLength: String trunctated because input was \
              greater than STRING_MAX_SIZE");
    #endif /* DEBUG */

    return i;
}

internal void nullTerminate(String *string)
{
    if (string->text[string->length] != '\0')
    {
        string->text[string->length++] = '\0'; 
    }
}


struct IntArray {
    size_t length;
    size_t capacity;
    int *data;
};

void initIntArray(IntArray *arr)
{
    arr->length = 0;
    arr->capacity = MIN_ARRAY_SIZE;
    arr->data = malloc(sizeof(int) * arr->capacity);
}

IntArray* newIntArray()
{
    IntArray *arr = malloc(sizeof(IntArray));
    initIntArray(arr);
    return arr;
}

void intArrayAppend(IntArray *arr, int val)
{
    /* TODO(pete): implement resize */

    arr->data[arr->length++] = val;
}

void printIntArray(IntArray *arr)
{
    putchar('[');

    int i;
    for (i = 0; i < arr->length; i++)
    {
        if (i == arr->length - 1)
            printf("%d]\n", arr->data[i]);
        else
            printf("%d, ", arr->data[i]);
    }
}