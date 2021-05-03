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
* Function: to generate public and priavte keys for the RSA algorithm used for 
  encryption.
* Input: e & d - pointers to the public and private keys to be created
        n - the modulus of the two keys
        t - the totient function
*******************************************************************************/
void createKey(int* e, int* d, int n, int t);

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
* Function: determines if two integers are coprime
* Input: the integers for comparison
* Output: a boolean true if coprime or false if not
          - note: boolean is defined in util.h
*******************************************************************************/
boolean isCoPrime(int i1, int i2);

#endif /* ENCRYPT_H */