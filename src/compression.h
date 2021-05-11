/*******************************************************************************
* Author: Joshua Gonzalez
* Date Updated: 26/04/2021
* 
* The header file for the run-length encoding compression alogorithm
*******************************************************************************/

#include "util.h"

#ifndef COMPRESSION_H

#define COMPRESSION_H

/*******************************************************************************
* Define: Function takes a string object input, compresses it and outputs the
* compressed version of the input
* Input:
* - Uncompressed String
* Output:
* - A compressed string
*******************************************************************************/
String compress(String);


/*******************************************************************************
* Define: Function takes a compressed string object input, decompresses it and 
* outputs the decompressed version of the input
* Input:
* - Compressed String
* Output:
* - A decompressed string
*******************************************************************************/
String decompress(String);


#endif /*COMPRESSION_H*/
