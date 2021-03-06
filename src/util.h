/*******************************************************************************
* Authors: Peter de Vroom, Joshua Gonzalez, Sam Zammit
* 
* The header file supports the functionality of various systems in the program.
* Types: boolean, String, LinkedList, Bit Manipulation
*******************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h> /* size_t, malloc, realloc, free */

/**********************************************************
* * *                      BOOLEAN                    * * *
***********************************************************/

typedef unsigned char boolean;
#define true 1
#define false 0

/**********************************************************
* * *                      STRING                     * * *
***********************************************************/

/*******************************************************************************
* Author: Peter de Vroom
* Struct: String
* Abstracts some of the complexity of working with C-style strings into a 
* higher-level wrapper struct with helper functions. Strings are automatically
* resized as needed and are automatically null-terminated.
*******************************************************************************/
typedef struct String {
    char *text;
    size_t length;
    size_t capacity;
} String_t;

/*******************************************************************************
* Author: Peter de Vroom
* Function: Allocate and initialise a new String object. Any call to newString
*           must be paired with freeString to avoid memory leaks.
* Input: val - A C-style string can be provided which sets the new String's initial
*              value to val and sized appropriately. If NULL, the new String is 
*              initalised empty.
* Output: Returns a pointer to heap-allocated String struct.
*******************************************************************************/
String_t* newString(const char *val);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Append a C-string to the String object. Resized if needed.
* Input: string - A String.
*           val - A C-style string which is appended to the String. val should
*                 be null-terminated.
*******************************************************************************/
void stringAppend(String_t *string, const char *val);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Append a char to the String object. Resized if needed.
* Input: string - A String.
*           val - A char which is appended to the String.
*******************************************************************************/
void stringAppendChar(String_t *string, char val);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Gets a characater at a given position. Bounds-checked.
* Input: string - A String.
*           val - index of a character.
* Output: Returns a char at the given position. Returns '\0' if out of bounds.
*******************************************************************************/
char stringGetChar(const String_t *string, int index);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Changes a character at a given position. Bounds-checked.
* Input: string - A String.
*         index - Index of a character in String.
*           val - Character to set.
*******************************************************************************/
void stringSetChar(String_t *string, int index, char val);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Checks if a String contains character c.
* Input: string - A String.
*             c - a character.
* Output: Returns true if string contains c, otherwise returns false.
*******************************************************************************/
boolean stringContains(const String_t *string, char c);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Compares string1 to string2 based on ASCII values. Shorter strings
*           take lexicographic precedence. Capital letters are considered
*           lesser than lower case letters.
*           This function works similarly to strcmp from <string.h>
* Input: string1 - A String.
*        string2 - A String.
* Output: Returns 0 if both Strings are identical. 
*         Returns 1 if string1 is greater than string2.
*         Returns -1 if string1 is less than string2.
*******************************************************************************/
int stringCompare(const String_t *string1, const String_t *string2);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Reads the stdin and creates a new String object.
* Input: prompt - takes a c-string that is printed before input is taken.
* Output: Returns a pointer to heap-allocated String struct.
*******************************************************************************/
String_t* readString(const char *prompt);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Prints a String
* Input: string - A String
*******************************************************************************/
void printString(const String_t *string);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Frees a String and the data it contains
* Input: string - A String (void pointer allows for compatability with LinkedLists)
*******************************************************************************/
void freeString(void *string);


/**********************************************************
* * *                   LINKED LIST                   * * *
***********************************************************/

/*******************************************************************************
* Author: Peter de Vroom
* Struct: LinkedList, Node
* Provides a linked list data structure which can contain any data. All
* data must be the same type for all functions to work properly. Using different
* types in one LinkedList will result in undefined behaviour.
*******************************************************************************/
typedef struct Node {
    void *data;
    struct Node *next;
} Node_t;

typedef struct LinkedList {
    Node_t *head;
    size_t length;
} LinkedList_t;

/*******************************************************************************
* Author: Peter de Vroom
* Function: Allocates and initialises a new LinkedList. Any call to newLinkedList
*           needs to be paired with freeLinkedList to avoid memory leaks.
* Input: data - A void pointer to some data.
* Output: Returns a pointer to a heap-allocated LinkedList
*******************************************************************************/
LinkedList_t* newLinkedList(void *data);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Appends data to list. data needs to be the same type as other data
*           in the list
* Input: list - A LinkedList
*        data - A void pointer to some data.
*******************************************************************************/
void linkedListAppend(LinkedList_t *list, void *data);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Gets a node at an index. Bounds-checked. NOTE that list still retains
*           ownership of the returned Node. This function needs to be used carefully
*           to prevent unintentional aliasing.
* Input: list - A LinkedList
*       index - Index of a node
* Output: Returns a Node in the LinkedList. Returns NULL of out of bounds.
*******************************************************************************/
Node_t* linkedListGet(const LinkedList_t *list, int index);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Sets the data of a node at an index. Previously held data may need to be freed
*           if it is heap-allocated. Bounds-checked.
* Input: list - A LinkedList
*       index - Index of a node
*        data - Pointer to data that will be replaced at index. Must be the same
*               type as other elements in the list.
*    freeFunc - Function pointer to a free function if LinkedList contents need
*               freed. Can be NULL if data is not heap-allocated.
*******************************************************************************/
void linkedListSet(LinkedList_t *list, int index, void *data, void (*freeFunc)(void *));

/*******************************************************************************
* Author: Peter de Vroom
* Function: Removes an element in the LinkedList. Previously held data may need to be freed
*           if it is heap-allocated.
* Input: list - A LinkedList
*       index - Index of a node (bounds-checked)
*        data - Void pointer to data that will be replaced at index
*    freeFunc - Function pointer to a free function if LinkedList contents need
*               freed. Can be NULL if data is not heap-allocated.
*******************************************************************************/
void linkedListRemove(LinkedList_t *list, int index, void (*freeFunc)(void *));

/*******************************************************************************
* Author: Peter de Vroom
* Function: Removes all elements in the LinkedList. Previously held data may need to be freed
*           if it is heap-allocated. An empty head Node is recreated.
* Input: list - A LinkedList
*    freeFunc - Function pointer to a free function if LinkedList contents need
*               freed. Can be NULL if data is not heap-allocated.
*******************************************************************************/
void linkedListClear(LinkedList_t *list, void (*freeFunc)(void *));

/*******************************************************************************
* Author: Peter de Vroom
* Function: Prints all the data contained in a LinkedList.
* Input: list - A LinkedList
*   printFunc - A pointer to a print function. This should match the type that
*               needs to be printed. func must take a void pointer for flexibility.
*******************************************************************************/
void printLinkedList(LinkedList_t *list, void (*printFunc)(void *));

/** Sample print functions **/
void printInt(void *num);

void printDouble(void *flt);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Frees a linked list and all contained data.
* Input: list - A LinkedList
*    freeFunc - A pointer to a free function. Can be NULL if data is not
*               heap-allocated. freeFunc must take a void pointer for flexibility.
*******************************************************************************/
void freeLinkedList(LinkedList_t *list, void (*freeFunc)(void *));

/*******************************************************************************
* Author: Sam Zammit
* Function: A function that uses a bubble sort to sort the accounts linked list
            in alphabetical order.
* Input: Takes the linked list of accounts, aswell as a compare function that 
         will compare two account names to check which one comes first 
         alphabetically. 
*******************************************************************************/

void linkedListSortAlphabetically(LinkedList_t *list, boolean (*compareFunction)(void *, void *)); 




/**********************************************************
* * *                 BIT MANIPULATION                * * *
***********************************************************/
typedef char byte;

/* Bit Manipulation code was inspired by aniliitb10 and Collin Peterson's 
* stackoverflow post.
* https://stackoverflow.com/questions/2525310/how-to-define-and-work-with-an-array-of-bits-in-c */

/*******************************************************************************
* Author: Peter de Vroom
* Macro: Sets bit to 1 in a byte. 
* Input: byte - byte to have bit changed
*        bitToSet - bit to set in byte
*******************************************************************************/
#define setBit(byte, bitToSet) byte |= 1 << (bitToSet-1)

/*******************************************************************************
* Author: Peter de Vroom
* Macro: Sets bit to 0 in a byte.
* Input: byte - byte to have bit changed
*        bitToSet - bit to set in byte
*******************************************************************************/
#define clearBit(byte, bitToSet) byte &= ~(1 << (bitToSet-1))

/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Checks status of bit (Goes from 8 - 1)
* Input: byte - byte to have bit checked
*        pos - position of bit to check
*******************************************************************************/
int checkBit(byte byte, int pos);

#endif /* UTIL_H */