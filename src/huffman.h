/*******************************************************************************
* Author: Joshua Gonzalez
* Date Updated: 10/05/2021
* 
* The header file for the compression functionality of the program.
*
*******************************************************************************/
#include "util.h"

#ifndef HUFFMAN_H

#define HUFFMAN_H

/*******************************************************************************
* Define: Function takes a string object input, compresses it and outputs the
* compressed version of the input
* Input:
* - Uncompressed String
* Output:
* - A compressed string
* - Huffman dictonary
*******************************************************************************/
String HuffmanCompression(String);


/*******************************************************************************
* Define: Function takes a compressed string object input, decompresses it and 
* outputs the decompressed version of the input
* Input:
* - Compressed String
* - Huffman dictionary
* Output:
* - A decompressed string
*******************************************************************************/
String HuffmanDecompression(String);


#endif /*HUFFMAN_H*/
