/*******************************************************************************
* Author: Joshua Gonzalez
* Date Updated: 20/05/2021
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
* Define: Function compresses a string object input using huffman encoding
* Input:
* - Uncompressed string pointer
* Output:
* - Result_t data type
*   - compressed string
*   - compressed huffman tree
*   - length of full huffman code
*******************************************************************************/
result_t HuffmanCompression(const String *input);


/*******************************************************************************
* Define: Function decompresses a string object input using huffman encoding 
* Input:
*  - compressed string pointer
*  - compressed huffman tree
*  - length of full huffman code
* Output:
* - A decompressed string object pointer
*******************************************************************************/
String* HuffmanDecompression(String *huff_tree, String *huff_code, int code_len);


#endif /*HUFFMAN_H*/
