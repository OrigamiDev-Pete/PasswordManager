/*******************************************************************************
* Author: Joshua Gonzalez
* Date Updated: 10/05/2021
* 
* The header file for the huffman compression algorithm
*******************************************************************************/

#include "util.h"

#ifndef HUFFMAN_H

#define HUFFMAN_H


/* Result of huffman compression */
typedef struct {
    String* comp_string;
    String* huff_tree;
    int code_len;
} result_t;


/*******************************************************************************
* Define: Function takes a string object input, compresses it and outputs the
* compressed version of the input
* Input:
* - Uncompressed String
* Output:
* - A compressed string
* - Huffman dictonary
*******************************************************************************/
result_t HuffmanCompression(String);


/*******************************************************************************
* Define: Function takes a compressed string object input, decompresses it and 
* outputs the decompressed version of the input
* Input:
* - Compressed String
* - Huffman dictionary
* Output:
* - A decompressed string
*******************************************************************************/
String* HuffmanDecompression(String *huff_tree, String *huff_code, int code_len);


/* Combine all headers to compression.h */


#endif /*HUFFMAN_H*/
