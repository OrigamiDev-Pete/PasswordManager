/*******************************************************************************
* Author: Luke Phillips
* Date Updated: 26/04/2021
* 
* The header file for the ecryption functionality of the program.
*
*******************************************************************************/

#ifndef ENCRYPT_H
#define ENCRYPT_H

#include "util.h"   /*String, boolean*/
#include <stdlib.h> /*rand*/
#include <stdio.h>  /* fwrite, fread, fopen, fclose */

/*******************************************************************************
* Author: Luke Phillips
* Function: to encrypt a database file containing a collection of user accounts
* the whole file will be encrypted with each run of this function.
* The algorithm used is a RSA encryption method.
* Input: the name of the file to be encrypted.
* Output: an string containing the encrypted version of the input.
            - note: String defined in util.h
*******************************************************************************/
String encryptAccounts(String* input);

/*******************************************************************************
* Author: Luke Phillips
* Function: to decrypt a database file containing a collection of user accounts
* Input: the name of the file to be encrypted.
* Output: an string containing the decrypted version of the input.
            - note: String defined in util.h
*******************************************************************************/
String decryptAccounts(String* input);

/*******************************************************************************
* Author: Luke Phillips
* Function: to generate a key by performing mathematical operations on random
*           prime numbers. The key is used to encrypt data.
* Input: a pointer to the varible storing the encryption key.
*******************************************************************************/
void createKey(int* key);

/*******************************************************************************
* Author: Luke Phillips
* Function: generate two random prime numbers to be used in key generation
* Input: pointer to two integers to fill with the prime numbers.
*******************************************************************************/
void randomPrimes(int* x, int* y);

/*******************************************************************************
* Author: Luke Phillips
* Function: determines if an integer is prime
* Input: the integer
* Output: a boolean true if prime, false if not prime
          - note: boolean is defined in util.h
*******************************************************************************/
boolean isPrime(int input);

/*******************************************************************************
* Author: Luke Phillips
* Function: take the totient value and use it to generate the 2 digit shift key.
* Input: integer of the long key value.
*******************************************************************************/
int shortKey(int key);

/*******************************************************************************
* Author: Luke Phillips
* Function: read the two encoded keys from the file to be used.
* Input: two integer pointers of the location to load the keys into.
*******************************************************************************/
void readKeys(int* key);

/*******************************************************************************
* Author: Luke Phillips
* Function: encode the two keys and store securely in a file for future use.
    - future uses are further encryption, or decryption, for which the keys
      are needed.
* Input: two integer pointers of the keys to be stored.
*******************************************************************************/
void writeKeys(int* key);

#endif /* ENCRYPT_H */