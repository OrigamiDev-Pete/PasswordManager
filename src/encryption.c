/* Library Inclusion */
#include "encryption.h"

/* #define DEBUG */
#define K 2 /* K is a constant of any value used in key generation */ /* NOTE(pete): removed semi-colon from #define */
int e, d;

String encryptAccounts(String* input) {
    /* 'e' and 'd' are the public and private keys respectively */
    int* e_p = &e;
    int* d_p = &d;
    
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

    #ifdef DEBUG
    printf("e = %d; d = %d\n", *e_p, *d_p);
    #endif /* DEBUG */

    /* TODO: Use the keys generated to encrypt the input string. */
    String encrypted;
    encrypted.text = "placeholder";

    #ifdef DEBUG
    printf("The original text is: ");
    printString(input.text);
    printf("\nThe encrypted text is: ");
    printString(encrypted.text);
    #endif /* DEBUG */

    return encrypted;
}

String decryptAccounts(String* input) {
    /*TODO: decrypt the input string*/
    String decrypted;
    decrypted.text = "hello";
    return decrypted;
}

void createKey(int* e, int* d, int n, int t) {
    /* GENERATE PUBLIC KEY (e) - e must be coprime to t*/
    while(*e < t) {
        if(isCoPrime(*e, t)) {
            break;
        }
        else {
            (*e)++; /* NOTE(pete): added parentheses for order of operations */
        }
    }

    /* GENERATE PRIVATE KEY (d) - standard RSA encryption formula */
    *d = (1 + (K * t))/ *e; /* NOTE(pete): added dereference to e */
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