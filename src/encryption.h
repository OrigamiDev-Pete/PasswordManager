/*******************************************************************************
* Author: Luke Phillips
* Date Updated: 26/04/2021
* 
* The header file for the ecryption functionality of the program.
* Only the functions needed outside of the encryption file are declared.
* Other helper functions are declared within encryption.c
*
*******************************************************************************/

#ifndef ENCRYPT_H
#define ENCRYPT_H

#include "util.h"   /* String, boolean, newString, strintgGetChar,
                      StringSetChar */

/*******************************************************************************
* Author: Luke Phillips
* Function: to encrypt a string by generating a key which is stored for 
* decryption. The key generation algorithm used is a simplified version of 
* the RSA method prolific in web based encryption solutions.
* Input: The string to be encrypted, as a pointer.
* Output: none
            - note: String defined in util.h
*******************************************************************************/
void encryptString(String* input);

/*******************************************************************************
* Author: Luke Phillips
* Function: to use a key generated on encryption to decrypt a coded String type.
* Input: the string to be decrypted, as a pointer.
* Output: none
            - note: String defined in util.h
*******************************************************************************/
void decryptString(String* input);

/* NOTE(pete): Should the following functions be public? */
/* Response(Luke): These functions will only be called internally, the only
one with use outside encryption is the isPrime() method. */

/*******************************************************************************
* Author: Luke Phillips
* Function: to generate a key by performing mathematical operations on random
*           prime numbers. The key is used to encrypt data.
* Input: a pointer to the varible storing the encryption key.
*******************************************************************************/
void createKey(int* key);

#endif /* ENCRYPT_H */