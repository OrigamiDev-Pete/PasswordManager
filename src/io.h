/*******************************************************************************
* Author: Peter de Vroom
* 
* The header file for the In/Out functionality of the program.
*******************************************************************************/

#ifndef IO_H
#define IO_H

#include "util.h" /* boolean, LinkedList, linkedListGet, linkedListClear, linkedListAppend,
                   * String, stringAppendChar, stringAppend, freeString */


/* Enumerator for compression types */
typedef enum compressionType { NONE, HUFFMAN, RUN_LENGTH } compressionType;

/*******************************************************************************
* Author: Peter de Vroom
* Function: Saves accounts data to the filesystem.
* Input: accounts - A list of the accounts to be saved.
*         encrypt - encrypt or not.
*         cmpType - Type of compression to employ. Options are stored as enumerated
*                   values, HUFFMAN, RUN_LENGTH and NONE. HUFFMAN is more space 
*                   effecient. RUN_LENGTH is faster. NONE does not apply compression.
* Output: Returns true if successful, false if an error occurs
*******************************************************************************/
boolean saveData(const LinkedList_t *accounts, boolean encrypt, compressionType cmpType);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Loads accounts data from the filesystem.
* Input: accounts - A list to load the saved accounts into.
* Output: Returns true if successful, false if an error occurs
*******************************************************************************/
boolean loadData(LinkedList_t *accounts);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Safely read an integer from the stdin. Ignores bad input and flushes
*           the buffer.
* Output: Returns the integer found.
*******************************************************************************/
int readInt(void);


#endif /* IO_H */