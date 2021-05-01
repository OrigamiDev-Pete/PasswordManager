#include "util.h"

#include <stdio.h>
#include <stdlib.h>

/* #define DEBUG */

#define internal static /* static is a vague keyword, internal is more clear */

/**********************************************************
* * *                      STRING                     * * *
***********************************************************/

internal void checkAndResizeString(String *string, int newLength);
internal int stringLength(const char *str);
internal void nullTerminate(String *string);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Changes a char at a given position. Bounds-checked.
* Input: string - An unitialised String.
*           val - A C-style string can be provided which sets the new String's initial
*                 value to val and sized appropriately. If NULL, the new String is 
*                 initalised empty.
*******************************************************************************/
internal void initString(String *string, const char *val)
{
    /* Initialise an empty String if val is NULL */
    if (val == NULL)
    {
        string->length = 0;
        string->capacity = STRING_START_SIZE;
        string->text = malloc(string->capacity);
        if (!string->text)
        {
            #ifdef DEBUG
            puts("initString: malloc error.");
            #endif /* DEBUG */
            return;
        }
    }
    else
    {
        string->length = stringLength(val);
        /* Find the nearest power of 2 capacity that can hold the new length */
        int cap = STRING_START_SIZE;
        while (cap < string->length)
            cap *= 2;
        string->capacity = cap;
        string->text = malloc(string->capacity);
        if (!string->text)
        {
            #ifdef DEBUG
            puts("initString: malloc error.");
            #endif /* DEBUG */
            return;
        }

        /* Copy each character in val to String.text */
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
    if (!string)
    {
        #ifdef DEBUG
        puts("newString: malloc error.");
        #endif /* DEBUG */
        return NULL;
    }
    initString(string, val);
    return string;
}

void stringAppend(String *string, const char *val)
{
    if (val == NULL)
    {
        return;
    }
    /* Calculate the expected size of string once appended and
    *  check if it needs resizing */
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
}

void stringAppendChar(String *string, char val)
{
    checkAndResizeString(string, string->length+1);
    string->text[string->length++] = val;
    nullTerminate(string);
}

char stringGetChar(const String *string, int index)
{
    /* Bounds-check */
    if (index < string->length)
    {
        return string->text[index];
    }

    #ifdef DEBUG
    puts("stringGetChar: Out of Bounds");
    #endif /* DEBUG */

    return '\0';
}

void stringSetChar(String *string, int index, char val)
{
    /* Bounds-check */    
    if (index < string->length)
    {
        string->text[index] = val;
    }
    else
    {
        #ifdef DEBUG
        puts("stringSetChar: Out of Bounds");
        #endif /* DEBUG */
    }
}

String* readString(char *prompt)
{
    if (prompt)
    {
        printf("%s", prompt);
    }

    String *string = newString(NULL);
    char c;
    /* Safely read stdin */
    while ((c = getchar()) != '\n' && c != '\0' && c != EOF)
    {
        checkAndResizeString(string, string->length+1);
        string->text[string->length++] = c;
    }
    nullTerminate(string);
    return string;
}

void printString(const String *string)
{
    #ifndef DEBUG
    puts(string->text);
    #endif /* DEBUG */

    #ifdef DEBUG
    /* Manually print each character and preview null-terminators */
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

void freeString(void *string)
{
    free(((String *)string)->text);
    free(string);
}

/*******************************************************************************
* Author: Peter de Vroom
* Function: Checks if a String has reached capacity and needs resizing. Resizes
*           if it's required. Capacity expands by a factor of 2 to minimise 
*           many realloc calls.
* Input: string - A String.
*     newLength - index of character in String.
*******************************************************************************/
internal void checkAndResizeString(String *string, int newLength)
{
    if (newLength >= string->capacity-1)
    {
        #ifdef DEBUG
        puts("checkAndResizeString: Resizing");
        #endif /* DEBUG */
        /* Find the nearest power of 2 capacity that can hold the new length */
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
            #ifdef DEBUG
            puts("checkAndResizeString: Error reallocating memory.");
            #endif /* DEBUG */
        }
    }
}

/*******************************************************************************
* Author: Peter de Vroom
* Function: Returns the length of a c-string. Implementation is similar to strlen()
*           in string.h. A custom implementation allows for implementation specific
*           features (such as debug info) and avoids including the entire string.h file.
* Input: string - A C-string.
*******************************************************************************/
internal int stringLength(const char *str)
{
    int i = 0;
    while (str[i] != '\0' && str[i] != EOF && i < STRING_MAX_SIZE)
        i++;
    
    #ifdef DEBUG
    if (i == STRING_MAX_SIZE)
        puts("stringLength: String truncated because input was \
              greater than STRING_MAX_SIZE");
    #endif /* DEBUG */

    return i;
}

/*******************************************************************************
* Author: Peter de Vroom
* Function: Checks if string is null-terminated and adds one if not.
* Input: string - A String.
*******************************************************************************/
internal void nullTerminate(String *string)
{
    if (string->text[string->length] != '\0')
        string->text[string->length++] = '\0'; 
}

/**********************************************************
* * *                   LINKED LIST                   * * *
***********************************************************/

LinkedList* newLinkedList(void *data)
{
    LinkedList *list = malloc(sizeof(LinkedList));

    Node *head = malloc(sizeof(Node));
    head->data = data;
    head->next = NULL;
    list->head = head;

    if (data)
        list->length = 1;
    else
        list->length = 0;
    return list;
}

void linkedListAppend(LinkedList *list, void *data)
{
    Node *node = list->head;
    while (node->next != NULL)
    {
        node = node->next;
    }

    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;
    node->next = newNode;

    list->length++;
}

void printLinkedList(LinkedList *list, void (*func)(void *))
{
    Node *node = list->head;
    putchar('[');
    while (node != NULL)
    {
        (*func)(node->data);
        node = node->next;
        if (node) {
            putchar(',');
            putchar(' ');
        }
    }
    putchar(']');
    putchar('\n');
}

void printInt(void *num)
{
    printf("%d", *(int *)num);
}

void printDouble(void *dbl)
{
    printf("%lf", *(double *)dbl);
}

void freeLinkedList(LinkedList *list, void (*func)(void *))
{
    if (func)
    {
        Node *node = list->head;
        while (node != NULL)
        {
            Node *prevNode = node;
            node = node->next;
            (*func)(prevNode->data);
            free(prevNode);
            prevNode = NULL;
        }
    }
    else
    {
        Node *node = list->head;
        while (node != NULL)
        {
            /* printf("%p\n", node); */
            Node *prevNode = node;
            node = node->next;
            free(prevNode);
            prevNode = NULL;
        }
    }
    free(list);
}

/**********************************************************
* * *                   INTARRAY                      * * *
***********************************************************/

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