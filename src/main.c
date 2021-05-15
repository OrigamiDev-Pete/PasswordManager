#include <stdio.h>

#include "accounts.h"
#include "compression.h"
#include "huffman.h"
#include "io.h"
#include "util.h"
#include "encryption.h"



int main(void)
{
	/* setBit Demo */
	char A = 0;
	setBit(A, 7);
	setBit(A, 3);
	setBit(A, 5);
	printf("%d\n", A);
	printf("%c\n", A);

	/* stringCompare Demo */
	String *str1 = newString("oak ridge");
	String *str2 = newString("oakley park");
	printf("%d\n", stringCompare(str1, str2));


    /* Run Length Encoding Test */
    String* input = newString("aaaaaaaabbbbbbbbddddddddhhhhhhhhhhhhjj");
    printString(input);
    String stringcmp = compress(*input);
    printString(&stringcmp);
    String stringdcmp = decompress(stringcmp);
    printString(&stringdcmp);


    /* Huffman code printing test */
    printf("\nHuffman compression test:\nInput: ");
    String* test = newString("This is a test");
    printString(test);
    HuffmanCompression(*test);

    /* Encryption Test Run */
    String* tester = newString("Encryption tester string");
    printf("The original string: ");
    printString(tester);
    String encrypted = encryptAccounts(tester);
    printf("The encrypted string: ");
    printString(&encrypted);

    printf("Now Decrypted: ");
    String decrypted = decryptAccounts(&encrypted);
    printString(&decrypted);

	return 0;
}

/* Rough Main Menu idea */

/*

Login Menu:

*************************************
*         Password Mananger         *
*************************************
  1. Login (Exisiting User)
  2. Create New Master Account
  3. Exit Program


Main Menu (Succesfull Login):

*************************************
*            Main Menu              *
*************************************
   1. Search and Sort menu
   2. Add New account
   3. Display stored websites
   4. Import database (DC&DE)
   5. Export database (E&C)
   6. Settings
   7. Log out


Search Menu:

*************************************
*       Search and Sort Menu        *
*************************************
  1. Search database
  2. Sort database alphabetically
  3. Edit account entry
  4. Delete account


Settings Menu: !(Need to type in master password to delete master account)!

*************************************
*           Settings Menu           *
*************************************
   1. DELETE MASTER ACCOUNT
   2. OPTION 2
   2. OPTION 3

*/