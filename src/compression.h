/*******************************************************************************
* Author: Joshua Gonzalez
* Date Updated: 26/04/2021
* 
* The header file for the run-length encoding compression alogorithm
*******************************************************************************/

#include "util.h"
#include "huffman.h"

#ifndef COMPRESSION_H

#define COMPRESSION_H

/*******************************************************************************
* Define: Function compresses a string object input using run-length encoding
* Input:
* - Uncompressed string object pointer
* Output:
* - A compressed string object pointer
*******************************************************************************/
String_t* compress(const String_t *input);


/*******************************************************************************
* Define: Function decompresses a string object input using run-length encoding
* Input:
* - Compressed string object pointer
* Output:
* - A decompressed string object pointer
*******************************************************************************/
String_t* decompress(const String_t *input);


#endif /*COMPRESSION_H*/
