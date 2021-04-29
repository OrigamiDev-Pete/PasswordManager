/* Library Inclusion */
#include "encryption.h"
/* #define DEBUG */

boolean isPrime(int input);

int e, d;

String encryptAccounts(String* input) {
    /* 'e' and 'd' are the public and private keys respectively */
    int* e_p = &e;
    int* d_p = &d;
    
    /*Generate two random prime numbers*/
    int x, y;
    int* x_p = &x;
    int* y_p = &y;
    randomPrimes(x_p, y_p);
    
    /*Create the modulus and totient values for key generation*/
    int n = x * y;
    int t = (x-1)*(y-1);
    createKey(e_p, d_p, n, t);

    /*TODO: Use the keys generated to encrypt the input string.*/
    String *encrypted = newString(NULL);

    return *encrypted;
}

String decryptAccounts(String* input) {
    /*TODO: decrypt the input string*/
    String *decrypted = newString(NULL);
    return *decrypted;
}

void createKey(int* e, int* d, int n, int t) {
    /*TODO: create public (e) and private (d) keys from the inputs*/
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
        if(input%i!=0) {
            return true;
        }
    }
    return false;
}
