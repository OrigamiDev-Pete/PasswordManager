#include <stdio.h>

#include "accounts.h"
#include "compression.h"
#include "huffman.h"
#include "io.h"
#include "util.h"
#include "encryption.h"



int main(void)
{
<<<<<<< Updated upstream
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
    String* test = newString("aaaaaaabbc");
    HuffmanCompression(*test);

    /* Encryption Test Run */
    String* tester = newString("Encryption tester string");
    printf("The original string: ");
    printString(tester);
    String* encrypted = encryptString(tester);
    printf("The encrypted string: ");
    printString(encrypted);

    printf("Now Decrypted: ");
    String* decrypted = decryptString(encrypted);
    printString(decrypted);


    printf("****************************************************************************************************\n");
    String* inputEnc = readString("Input the string to be encrypted> ");
    String* encrypt = encryptString(inputEnc);
    printf("\nThe encrypted string is> ");
    printString(encrypt);
    String* decrypt = decryptString(encrypt);
    printf("The decrypted version is> ");
    printString(decrypt);
    printf("\n****************************************************************************************************\n");

    int one = 1;
    LinkedList *list = newLinkedList(&one);
    int two = 2;
    linkedListAppend(list, &two);
    int three = 3;
    linkedListAppend(list, &three);
    int four = 4;
    linkedListSet(list, 1, &four, NULL);
    printLinkedList(list, printInt);
    Node *node = linkedListGet(list, 1);
    printf("%d", *(int *)node->data);

    


	return 0;
=======
  boolean running = true;
  while(running=true)
  {
    printLogin();
    int option, login_size= 0;
    printf("Option>");
    scanf("%d",&option);
    while(option!=4)
    {
      switch(option)
    {
      case 1:

        printMenu();
        int task, menu_size=0;
        printf("Option>");
        scanf("%d",&task);
        while(task!=8)
        {
          switch(task)
          {
            case 1:

              printSearch();
              int choice, search_size=0;
              printf("Option>");
              scanf("%d",&choice);
              while(choice!=5)
              {
                switch(choice)
                {
                  case 1:
                  break;
                  case 2:
                  break;
                  case 3:
                  break;
                  case 4: /* Enter master password*/
                    String* password = readString("Enter password> ");
                    
                    printSettings();
                    int del, setting_size=0;
                  break;
                }
              } 

            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 7: running = false;
            break;
            default: printf("Invalid option.\n");
          }
        }

      break;
      case 2:;
      break;
      case 3:;
      break;
      default: printf("Invalid option.\n");
    }

  }

  }

}

/* Rough Main Menu idea */
void printLogin(void)
{
  printf("\n\n"
  "*************************************\n"
  "*              Welcome!             *\n"
  "*************************************\n"
  "1. Login (Exisiting User)\n"
  "2. Create New Master Account\n"
  "3. Exit Program\n");
}

void printMenu(void)
{
  printf("\n\n"
  "*************************************\n"
  "*             Main Menu             *\n"
  "*************************************\n"
  "1. Search and Sort menu\n"
  "2. Add New account\n"
  "3. Display stored websites\n"
  "4. Import database (DC&DE)\n"
  "5. Export database (E&C)\n"
  "6. Settings\n"
  "7. Log out\n");
}

void printSearch(void)
{
  printf("\n\n"
  "*************************************\n"
  "*        Search and Sort Menu       *\n"
  "*************************************\n"
  "1. Search database\n"
  "2. Sort database alphabetically\n"
  "3. Edit account entry\n"
  "4. Delete account\n");
>>>>>>> Stashed changes
}

void printSettings(void)
{
  printg("\n\n"
  "*************************************\n"
  "*              Settings             *\n"
  "*************************************\n"
  "1. DELETE MASTER ACCOUNT\n");
}

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


  /* Run Length Encoding Test */
    
    String* input = newString("hw kjd kdld ldkd ldld k ldd lkddafsdfdsfsdfa dsaf asdf sadfasdf asdfasdf sadf asdfsdf asdf "); /*empty String*/
    printString(input);
    String stringcmp = compress(*input);
    printString(&stringcmp);
    String stringdcmp = decompress(stringcmp);
    printString(&stringdcmp);

    /* LinkedList Demo */

    int i = 150;
    LinkedList *list = newLinkedList(&i);
    int j = 200;
    linkedListAppend(list, &j);
    int k = 250;
    linkedListAppend(list, &k);
    int l = 300;
    linkedListAppend(list, &l);

    printLinkedList(list, printInt);
    freeLinkedList(list, NULL);

    /* Account Demo + LinkedList */

    Account *acc = newAccount(readString("Enter a name> "), readString("Enter a URL> "), readString("Enter a password> "));

    Account *acc2 = newAccount(newString("Amazon"), newString("www.amazon.com"), newString("pass123"));

    LinkedList *list2 = newLinkedList(acc);
    linkedListAppend(list2, acc2);

    printLinkedList(list2, printAccount);
    freeLinkedList(list2, freeAccount);


    /* String Demo */

    String *string = newString(NULL); /* empty String */
    stringAppend(string, "Appending to the string");
    printString(string);

    String *string2 = newString("Setting the string at initialisation");
    printString(string2);

    String *stdRead = readString("Enter a string> "); /* A string can be created directly from stdin */
    printString(stdRead);

    freeString(string);
    freeString(string2);
    freeString(stdRead);