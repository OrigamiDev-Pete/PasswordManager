/*******************************************************************************
* Author: Peter de Vroom
* 
* The header file for the In/Out functionality of the program.
*******************************************************************************/

#ifndef IO_H
#define IO_H

#include "util.h"


/* Enumerator for compression types */
typedef enum compression { HUFFMAN, RUN_LENGTH } compression;

/*******************************************************************************
* Author: Peter de Vroom
* Function: Saves accounts data to the filesystem.
* Input: accounts - A list of the accounts to be saved.
*         encrypt - encrypt or not.
*        compress - compress or not.
*         cmpType - Type of compression to employ. Options are stored as enumated
*                   values, HUFFMAN and RUN_LENGTH. HUFFMAN is more space effecient.
*                   RUN_LENGTH is faster.
* Output: Returns true if successful, false if an error occurs
*******************************************************************************/
boolean saveData(const LinkedList *accounts, boolean encrypt, boolean compress, compression cmpType);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Saves accounts data to the filesystem.
* Input: accounts - A list to load the  saved accounts into.
* Output: Returns true if successful, false if an error occurs
*******************************************************************************/
boolean loadData(LinkedList *accounts);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Safely read an integer from the stdin. Ignores bad input and flushes
*           the buffer.
* Output: Returns the integer found.
*******************************************************************************/
int readInt(void);


#endif /* IO_H */