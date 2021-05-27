/* Library Inclusion and Defines*/
#include "encryption.h"
#include <stdlib.h> /* srand, rand */
#include <stdio.h>  /* fwrite, fread, fopen, fclose */
#include <time.h> /* time */

/* #define DEBUG */
#define KEYFILE "keys.bin" /* A file in which the keys will be stored */

/* Function Definitions */
void randomPrimes(int* x, int* y);
boolean isPrime(int input);
int shortKey(int key);
void readKeys(int* key);
void writeKeys(int* key);

void encryptString(String_t* input) {
    int key;
    int* key_p = &key;
    /* Open the file of stored keys if it exists */
    FILE* keys_file = fopen(KEYFILE, "rb");
    /* If the file does not exist, proceed with new key generation */
    if(keys_file == NULL) { 
        createKey(key_p);

        /* Write the generated keys to the file */
        writeKeys(key_p);
    }
    else {
        /* The keys exist, so read them from the file to continue encryption.
        * Close the keyfile to avoid conflicts when reading keys
        * in readKeys() function. */
        fclose(keys_file);
        readKeys(key_p);
    }

    /* Use the keys generated to encrypt the input string. */
    int counter;
    for(counter = 0; counter < input->length; counter++) {
        /* Pull then augment each character using a util.h method. */
        char tmp = stringGetChar(input, counter);
        tmp = tmp + key;
        /* Replace the original character with the augmented to encrypt. */
        stringSetChar(input, counter, tmp);
    }

    #ifdef DEBUG
    printf("The key is: %d\n", key);
    printf("The original text is: ");
    printString(input);
    printf("\nThe encrypted text is: ");
    printString(input);
    #endif /* DEBUG */

}

void decryptString(String_t* input) {
    int key;
    int* key_p = &key;
    FILE* keys_file = fopen(KEYFILE, "rb");
    if(keys_file == NULL) {
        /* When a valid file for stored keys is not present, there has been no 
        previous encryption */
        /* Decryption is not necessary when the string has not been encrypted. */
        printf("Data has not been previously encrypted. Aborting decryption.\n");
        fclose(keys_file);
        return;
    }
    else {
        /* Close the keyfile to avoid conflicts when reading keys
        in readKeys() function. */
        fclose(keys_file);
        readKeys(key_p);
    }

    /* Decrypt the input string */
    int counter;
    for(counter = 0; counter < input->length; counter++) {
        /* Reverse the augmentation of each character from encryption. */
        char tmp = stringGetChar(input, counter);
        tmp = tmp - key;
        /* Reassign the original values to the string. */
        stringSetChar(input, counter, tmp);
    }
    
}

void createKey(int* key) {
    /* Generate two random prime numbers */
    int x, y;
    int* x_p = &x;
    int* y_p = &y;
    randomPrimes(x_p, y_p);

    /* Create totient value for key generation */
    int t = (x-1)*(y-1);

    #ifdef DEBUG
    printf("x = %d; y = %d; t = %d\n", *x_p, *y_p, t);
    #endif /* DEBUG */

    /* Shortens the key while retaining randomness. Makes more efficient. */
    int shortened = shortKey(t);
    /* If the shortened key is zero, encryption will not change the string. */
    if(shortened == 0) {
        createKey(key);  /* Generate key again. */
    }
    else { 
        *key = shortened;
    }
}

/*******************************************************************************
* Author: Luke Phillips
* Function: generate two random prime numbers to be used in key generation
* Input: pointer to two integers to fill with the prime numbers.
*******************************************************************************/
void randomPrimes(int* x, int* y) {
    /* Seeding the rand function - using time will cause the first roll to always 
    be different. This is required to reduce predicatbility of key generated. */
    srand(time(NULL));
    int i = rand();
    int j = rand();

    /* Increment each number until it is prime. */
    while(!isPrime(i)) {
        i++;
    }
    while(!isPrime(j)) {
        j++;
    }
    /* Assign to the pointers in argument as two values cannot be returned. */
    *x = i;
    *y = j;
}

/*******************************************************************************
* Author: Luke Phillips
* Function: determines if an integer is prime.
* Input: the integer to be tested.
* Output: a boolean true if prime, false if not prime.
          - note: boolean is defined in util.h
*******************************************************************************/
boolean isPrime(int input) {
    int i;
    /* Check each value from 2 until the midpoint of the number. */
    for(i = 2; i < input/2; i++) {
        /* If any number other than one is evenly divisble, it's not prime */
        if(input%i==0) {
            return false;
        }
    }
    return true;
}

/*******************************************************************************
* Author: Luke Phillips
* Function: take the totient value and use it to generate the 2 digit shift key.
* Input: integer of the long key value.
*******************************************************************************/
int shortKey(int key) {
    /* Returns the last two digits of the randomised key. Retains randomness
    but reduced processing complexity. Also remains within the limits of
    the ASCII table. */
    return key % 100;
}

/*******************************************************************************
* Author: Luke Phillips
* Function: read the key from the file to be used.
* Input: integer pointer of the location to load the key into.
*******************************************************************************/
void readKeys(int* key) {
    /* Keyfile will persist across executions of this code. */
    FILE* file = fopen(KEYFILE, "rb");
    fread(key, sizeof(int), 1, file);
    fclose(file);    
}

/*******************************************************************************
* Author: Luke Phillips
* Function: store key securely in a file for future use, file will be unreadable
*           to the users of the program without this code.
    - future uses are further encryption, or decryption, for which the keys
      are needed.
* Input: integer pointer of the key to be stored.
*******************************************************************************/
void writeKeys(int* key) {
    /* Keyfile will persist across executions of this code. */
    FILE* file = fopen(KEYFILE, "wb");
    fwrite(key, sizeof(int), 1, file);
    fclose(file);
}