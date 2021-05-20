/* Library Inclusion and Defines*/
#include "encryption.h"
#include <stdlib.h> /* srand, rand */
#include <stdio.h>  /* fwrite, fread, fopen, fclose */
#include <time.h> /* time */

/* #define DEBUG */
#define KEYFILE "keys.bin" /* A file in which the keys will be stored */

void encryptString(String* input) {
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
        char tmp = stringGetChar(input, counter);
        tmp = tmp + key;
        stringSetChar(input, counter, tmp);
    }

    #ifdef DEBUG
    printf("The key is: %d\n", key);
    printf("The original text is: ");
    printString(input);
    printf("\nThe encrypted text is: ");
    printString(input);             /* NOTE(pete): encrypted doesn't exist anymore */
    #endif /* DEBUG */

}

void decryptString(String* input) {
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
        char tmp = stringGetChar(input, counter);
        tmp = tmp - key;
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
    /* int n = x * y; */ 
    int t = (x-1)*(y-1);

    #ifdef DEBUG
    printf("x = %d; y = %d; t = %d\n", *x_p, *y_p, t);
    #endif /* DEBUG */

    /* Shortens the key while retaining randomness. Makes more efficient. */
    int shortened = shortKey(t);
    /* If the shortened key is zero, encryption will not change the string. */
    if(shortened == 0) createKey(key); /* Generate key again. */
    else *key = shortened;
}

void randomPrimes(int* x, int* y) {
    /* Seeding the rand function - using time will cause the first roll to always 
    be different. This is required to reduce predicatbility of key generated */
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

int shortKey(int key) {
    return key % 100;
}

void readKeys(int* key) {
    FILE* file = fopen(KEYFILE, "rb");
    fread(key, sizeof(int), 1, file);
    fclose(file);    
}

void writeKeys(int* key) {
    FILE* file = fopen(KEYFILE, "wb");
    fwrite(key, sizeof(int), 1, file);
    fclose(file);
}