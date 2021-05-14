/* Library Inclusion and Defines*/
#include "encryption.h"

/* #define DEBUG */
#define K 2 /* K is a constant of any value used in key generation */
#define KEYFILE "keys.bin" /* A file in which the keys will be stored */

String encryptAccounts(String* input) {
    /* 'e' and 'd' are the public and private keys respectively */
    int e, d;
    int* e_p = &e;
    int* d_p = &d;
    /* Open the file of stored keys if it exists */
    FILE* keys_file = fopen(KEYFILE, "rb");
    if(keys_file == NULL) {
        /* If the file does not exist, proceed with new key generation */
        /* Generate two random prime numbers */
        int x, y;
        int* x_p = &x;
        int* y_p = &y;
        randomPrimes(x_p, y_p);

        /* Create the modulus and totient values for key generation */
        int n = x * y;
        int t = (x-1)*(y-1);

        #ifdef DEBUG
        printf("x = %d; y = %d; t = %d\n", *x_p, *y_p, t);
        #endif /* DEBUG */

        createKey(e_p, d_p, n, t);

        /* Close the keyfile to avoid conflicts when writing new keys
        in writeKeys() function. */
        fclose(keys_file);
        writeKeys(e_p, d_p);
    }
    else {
        /* The keys exist, so read them from the file to continue encryption. */
        /* Close the keyfile to avoid conflicts when reading keys
        in readKeys() function. */
        fclose(keys_file);
        readKeys(e_p, d_p);
    }

    #ifdef DEBUG
    printf("e = %d; d = %d\n", *e_p, *d_p);
    #endif /* DEBUG */

    /* TODO: Use the keys generated to encrypt the input string. */
    String* encrypted = newString("placeholder");

    #ifdef DEBUG
    printf("The original text is: ");
    printString(input);
    printf("\nThe encrypted text is: ");
    printString(encrypted);
    #endif /* DEBUG */

    return *encrypted;
}

String decryptAccounts(String* input) {
    /* 'e' and 'd' are the public and private keys respectively */
    int e, d;
    int* e_p = &e; 
    int* d_p = &d;

    FILE* keys_file = fopen(KEYFILE, "rb");
    if(keys_file == NULL) {
        /* When a valid file for stored keys is not present, there has been no 
        previous encryption */
        /* Decryption is not necessary when the string has not been encrypted. */
        printf("Data has not been previously encrypted. Aborting decryption.\n");
        fclose(keys_file);
        return *input;
    }
    else {
        /* Close the keyfile to avoid conflicts when reading keys
        in readKeys() function. */
        fclose(keys_file);
        readKeys(e_p, d_p);
    }

    /*TODO: decrypt the input string*/
    String decrypted;
    decrypted.text = "placeholder";
    return decrypted;
}

void createKey(int* e, int* d, int n, int t) {
    /* GENERATE PUBLIC KEY (e) - e must be coprime to t*/
    while(*e < t) {
        if(isCoPrime(*e, t)) {
            break;
        }
        else {
            (*e)++;
        }
    }

    /* GENERATE PRIVATE KEY (d) - standard RSA encryption formula */
    *d = (1 + (K * t))/ *e;
}

void randomPrimes(int* x, int* y) {
    int i = rand();
    int j = rand();

    while(!isPrime(i)) {
        i++;
    }
    while(!isPrime(j)) {
        j++;
    }
    *x = i;
    *y = j;
}

boolean isPrime(int input) {
    int i;
    for(i = 2; i < input/2; i++) {
        if(input%i==0) {
            return false;
        }
    }
    return true;
}

boolean isCoPrime(int i1, int i2) {
    /* The method used to determine coprime is found by Euclid's algorithm. 
     * The greatest common divisor will be 1 when both are coprime. */
    while (i1 != 0 && i2 != 0) {
        if(i1 < i2) {
            i1 = i1 % i2;
        }
        else {
            i2 = i2 % i1;
        }
    }
    /* Max will store the greatest common divisor (GCD) */
    int max;
    if(i1 > i2) {
        max = i1;
    }
    else {
        max = i2; 
    }
    /* The integers are coprime if the GCD is 1 */
    return max == 1;
}

void readKeys(int* e, int* d) {
    FILE* file = fopen(KEYFILE, "rb");
    /* Holder for the values taken from the file. */
    int values[2];
    fread(values, sizeof(int), 2, file);
    *e = values[0];
    *d = values[1];
    fclose(file);    
}

void writeKeys(int* e, int* d) {
    FILE* file = fopen(KEYFILE, "wb");
    /* The key values to be written to the file. */
    int values[2] = {*e, *d};
    fwrite(values, sizeof(int), 2, file);
    fclose(file);
}