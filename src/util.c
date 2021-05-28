/*******************************************************************************
* Authors: Peter de Vroom, Joshua Gonzalez, Sam Zammit
*******************************************************************************/
#include "util.h"

#include <stdio.h> /* printf, puts, putchar, getchar, fprintf */

#define internal static /* static is a vague keyword, internal is more clear */

/**********************************************************
* * *                      STRING                     * * *
***********************************************************/

#define STRING_START_SIZE 64        /* Size selected to minimise reallocation */
#define STRING_MAX_SIZE 200000000   /* Size well beyond anything the program need handle */

internal void checkAndResizeString(String_t *string, int newLength);
internal int stringLength(const char *str);
internal void nullTerminate(String_t *string);


/*******************************************************************************
* Author: Peter de Vroom
* Function: Initialises a new String.
* Input: string - An uninitialised String.
*           val - A C-style string can be provided which sets the new String's initial
*                 value to val and sized appropriately. If NULL, the new String is 
*                 initalised empty.
*******************************************************************************/
internal void initString(String_t *string, const char *val)
{
    /* Initialise an empty String if val is NULL */
    if (!val)
    {
        string->length = 0;
        string->capacity = STRING_START_SIZE;
        string->text = malloc(string->capacity * sizeof(char));
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
        /* Find the nearest power of 2 capacity that can hold the length of val */
        int cap = STRING_START_SIZE;
        while (cap <= string->length)
            cap *= 2;
        string->capacity = cap;
        string->text = malloc(string->capacity * sizeof(char));
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

String_t* newString(const char *val)
{
    String_t *string = malloc(sizeof(String_t));
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

void stringAppend(String_t *string, const char *val)
{
    if (val == NULL)
    {
        return;
    }
    /* Calculate the expected size of string once appended and
    *  check if it needs resizing */
    checkAndResizeString(string, string->length + stringLength(val));
    /* Remove null-terminator */
    if (string->length != 0)
    {
        string->length--;
    }
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

void stringAppendChar(String_t *string, char val)
{
    checkAndResizeString(string, string->length+1);
    /* Remove null-terminator */
    if (string->length != 0)
    {
        string->length--;
    }
    string->text[string->length++] = val;
    nullTerminate(string);
}

char stringGetChar(const String_t *string, int index)
{
    /* Bounds-check */
    if (index < string->length)
    {
        return string->text[index];
    }
    else
    {
        #ifdef DEBUG
        puts("stringGetChar: Out of Bounds");
        #endif /* DEBUG */

        return '\0';
    }
}

void stringSetChar(String_t *string, int index, char val)
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

boolean stringContains(const String_t *string, char c)
{
    int i;
    for (i = 0; i < string->length-1; i++)
    {
        if (stringGetChar(string, i) == c)
            return true;
    }
    return false;
}

int stringCompare(const String_t *string1, const String_t *string2)
{
    int i;
    for (i = 0; i < string1->length-1 && i < string2->length-1; i++)
    {
        /* If string1 is less than string2 */
        if (string1->text[i] < string2->text[i])
            return -1;
        /* If string1 is greater than string2 */
        else if (string1->text[i] > string2->text[i])
            return 1;
    }

    /* Shorter, but otherwise equal, strings take lexicographic precedence. */
    if (string1->length < string2->length)
        return -1;
    else if (string1->length > string2->length)
        return 1;

    /* Strings must be equal to reach this point */
    return 0;
}

String_t* readString(const char *prompt)
{
    if (prompt)
        printf("%s", prompt);

    String_t *string = newString(NULL);
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

void printString(const String_t *string)
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
    free(((String_t *)string)->text);
    free(string);
}

/*******************************************************************************
* Author: Peter de Vroom
* Function: Checks if a String has reached capacity and needs resizing. Resizes
*           if it's required. Capacity expands by a factor of 2 to minimise 
*           realloc calls.
* Input: string - A String.
*     newLength - index of character in String.
*******************************************************************************/
internal void checkAndResizeString(String_t *string, int newLength)
{
    if (newLength >= string->capacity)
    {
        #ifdef DEBUG
        puts("checkAndResizeString: Resizing");
        #endif /* DEBUG */
        /* Find the nearest power of 2 capacity that can hold the new length */
        int cap = string->capacity;
        while (cap <= newLength)
        {
            cap *= 2;
        }
        char *tmp;
        size_t tmp_capacity = cap;
        tmp = realloc(string->text, tmp_capacity);
        if (tmp)
        {
            string->text = tmp;
            string->capacity = tmp_capacity;
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
internal void nullTerminate(String_t *string)
{
    string->text[string->length++] = '\0'; 
}


/**********************************************************
* * *                   LINKED LIST                   * * *
***********************************************************/

void swapNodes(Node_t *a, Node_t *b); /*   Prototype for swapNodes     */

LinkedList_t* newLinkedList(void *data)
{
    LinkedList_t *list = malloc(sizeof(LinkedList_t));

    Node_t *head = malloc(sizeof(Node_t));
    head->data = data;
    head->next = NULL;
    list->head = head;

    /* If no data is passed to the new list we can regard the list
     * as having effectively no length. */
    if (data)
        list->length = 1;
    else
        list->length = 0;
    return list;
}

void linkedListAppend(LinkedList_t *list, void *data)
{
    /* Set head node data if length is 0 */
    if (list->length == 0)
    {
        list->head->data = data;
    }
    else
    {
        Node_t *node = list->head;
        while (node->next != NULL)
        {
            node = node->next;
        }

        Node_t *newNode = malloc(sizeof(Node_t));
        newNode->next = NULL;
        newNode->data = data;
        node->next = newNode;
    }
    list->length++;
}

Node_t *linkedListGet(const LinkedList_t *list, int index)
{
    /* Bounds check */
    if (index > list->length)
    {
        fprintf(stderr, "LinkedList: Out of Bounds");
        return NULL;
    }

    /* Get node at index */
    Node_t *node = list->head;
    int i;
    for (i = 0; i < index && node->next != NULL; i++)
    {
        node = node->next;
    }
    return node;
}

void linkedListSet(LinkedList_t *list, int index, void *data, void (*freeFunc)(void *))
{
    /* Bounds check */
    if (index > list->length)
    {
        fprintf(stderr, "LinkedList: Out of Bounds");
        return;
    }

    /* Get node at index */
    Node_t *node = linkedListGet(list, index);

    /* If element needs to be freed call freeFunc */
    if (freeFunc)
    {
        (*freeFunc)(node->data);
    }

    /* Set data */
    node->data = data;
}

void linkedListRemove(LinkedList_t *list, int index, void (*freeFunc)(void *))
{
    /* Bounds check */
    if (index > list->length-1)
    {
        fprintf(stderr, "LinkedList: Out of Bounds");
        return;
    }

    if (list->length != 0)
    {
        /* Get node at index (linkedListGet() is not used to obtain 
        *  node and prevNode in one loop) */
        Node_t *node = list->head;
        Node_t *prevNode = NULL;
        int i;
        for (i = 0; i < index && node->next != NULL; i++)
        {
            prevNode = node;
            node = node->next;
        }

        /* If list only contains one element then we don't need to move pointers */
        if (list->length > 1)
        {
            if (index == 0)
            {
                list->head = node->next;
            }
            else
            {
                prevNode->next = node->next;
            }
        }

        /* If element needs to be freed call freeFunc */
        if (freeFunc && node->data)
        {
            (*freeFunc)(node->data);
        }

        list->length--;
    }
}

void linkedListClear(LinkedList_t *list, void (*freeFunc)(void *))
{
    if (list->length == 0)
        return;
    
    /* If a free function is provided data must be heap-allocated */
    if (freeFunc)
    {
        Node_t *node = list->head;
        while (node != NULL)
        {
            Node_t *prevNode = node;
            node = node->next;
            (*freeFunc)(prevNode->data);
            free(prevNode);
            prevNode = NULL;
        }
    }
    /* free pass for stack-allocated data */
    else
    {
        Node_t *node = list->head;
        while (node != NULL)
        {
            Node_t *prevNode = node;
            node = node->next;
            free(prevNode);
            prevNode = NULL;
        }
    }

    list->length = 0;
    list->head = malloc(sizeof(Node_t));
    list->head->next = NULL;
    list->head->data = NULL;
}

void printLinkedList(LinkedList_t *list, void (*printFunc)(void *))
{   
    #ifndef DEBUG
    /* Outside of debug mode LinkedList does not impose any formatting */
    /* Check if LinkedList is empty */
    if (list->length == 0)
    {
        return;
    }
    else
    {
        Node_t *node = list->head;
        while (node != NULL)
        {
            (*printFunc)(node->data);
            node = node->next;
        }
    }
    #endif /* DEBUG */

    #ifdef DEBUG
    /* Check if LinkedList is empty */
    if (list->length == 0)
    {
        putchar('[');
        putchar(']');
        putchar('\n');
    }
    else
    {
        Node_t *node = list->head;
        putchar('[');
        while (node != NULL)
        {
            (*printFunc)(node->data);
            node = node->next;
            if (node) {
                putchar(',');
                putchar('\n');
            }
        }
        putchar(']');
        putchar('\n');
    }
    #endif /* DEBUG */
}

void printInt(void *num)
{
    printf("%d", *(int *)num);
}

void printDouble(void *dbl)
{
    printf("%lf", *(double *)dbl);
}

void freeLinkedList(LinkedList_t *list, void (*freeFunc)(void *))
{
    if (list->length == 0)
        return;

    /* If a free function is provided data must be heap-allocated */
    if (freeFunc)
    {
        Node_t *node = list->head;
        while (node != NULL)
        {
            Node_t *prevNode = node;
            node = node->next;
            (*freeFunc)(prevNode->data);
            free(prevNode);
            prevNode = NULL;
        }
    }
    /* free pass for stack-allocated data */
    else
    {
        Node_t *node = list->head;
        while (node != NULL)
        {
            Node_t *prevNode = node;
            node = node->next;
            free(prevNode);
            prevNode = NULL;
        }
    }
    free(list);
}

void linkedListSortAlphabetically(LinkedList_t *list, boolean (*compareFunction)(void *, void *)){
    int swapped, i;
    int size = list->length;

    swapped = 1;

    while(swapped){

        swapped = 0;

        for(i = 0; i < size - 1; i++ ){
            
            Node_t* a = linkedListGet(list, i);
            Node_t* b = linkedListGet(list, i+1);

            if ((compareFunction)(a->data, b->data) == 1){
                swapNodes(a, b);
                swapped = 1;
            }

        }
        if (swapped == 0){
            break;
        }
    } 
}

/*******************************************************************************
* Author: Sam Zammit
* Function: A function that operates the swapping inside of the bubble sort.
* Input: Takes two separate nodes to be swapped. 
*******************************************************************************/

void swapNodes(Node_t *a, Node_t *b){
    void *temp = b->data;
    b->data = a->data;
    a->data = temp;
}

int checkBit(byte byte, int pos)
{
    --pos;
    
    if(byte & (1<< pos))
        return(1);
    else
        return(0);
}