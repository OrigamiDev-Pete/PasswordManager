/*******************************************************************************
* Author: Peter de Vroom
* 
* The header file supports the functionality of various systems in the program.
* Types: boolean, String, IntArray
*******************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

typedef unsigned int boolean;
#define true 1
#define false 0

/*******************************************************************************
* Author: Peter de Vroom
* Struct: String
* Abstracts some of the complexity of working with C-style strings into a 
* higher-level wrapper struct with helper functions. Strings are automatically
* null-terminated.
*******************************************************************************/
typedef struct String {
    char *text;
    size_t length;
    size_t capacity;
} String;
#define STRING_START_SIZE 64
#define STRING_MAX_SIZE 200000000

/*******************************************************************************
* Author: Peter de Vroom
* Function: Initialises a preallocated String object
* Input: A unitiliased String.
*        val - A C-style string can be provided which sets the new String's initial
*              value to val and sized appropriately. If NULL the new String is 
*              initalised empty.
*******************************************************************************/
/* void initString(String *string, const char *val); */ /* NOTE(pete): This allows for stack allocation
*                                                                      however the implemenatation doesn't support this fully */

/*******************************************************************************
* Author: Peter de Vroom
* Function: Allocate and initialise a new String object.
* Input: val - A C-style string can be provided which sets the new String's initial
*              value to val and sized appropriately. If NULL the new String is 
*              initalised empty.
* Output: Returns a pointer to heap-allocated String struct.
*******************************************************************************/
String* newString(const char *val);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Append a C-string to the String object. Resized if needed.
* Input: string - A String.
*           val - A C-style string which is appended to the String.
* Output: Returns a pointer to the String.
*******************************************************************************/
String* stringAppend(String *string, const char *val);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Append a char to the String object. Resized if needed.
* Input: string - A String.
*           val - A char which is appended to the String.
* Output: Returns a pointer to the String.
*******************************************************************************/
String* stringAppendChar(String *string, char val);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Returns char at a given position.
* Input: string - A String.
*           val - index of character.
* Output: Returns a char at the given position. Returns '\0' if out of bounds.
*******************************************************************************/
char stringGetChar(String *string, int index);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Reads the stdin and creates a new String object.
* Output: Returns a pointer to heap-allocated String struct.
*******************************************************************************/
String* readString(void);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Prints a String
* Input: string - A String
*******************************************************************************/
void printString(String *string);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Frees a String and the data it contains
* Input: string - A String
*******************************************************************************/
void freeString(String *string);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Frees the data in a string
* Input: string - A String
*******************************************************************************/
void freeStackString(String *string);


typedef struct IntArray IntArray;
#define MIN_ARRAY_SIZE 8

void initIntArray(IntArray *arr);

IntArray* newIntArray();

void intArrayAppend(IntArray *arr, int val);

void intArrayInsert(IntArray *arr, int index, int val);

void intArrayGet(IntArray *arr, int index);

void intArraySet(IntArray *arr, int index, int val);

void intArrayRemove(IntArray *arr, int index);

void intArrayEmpty(IntArray *arr);

void printIntArray(IntArray *arr);

void freeIntArray(IntArray *arr);


#endif /* UTIL_H */