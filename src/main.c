#include <stdio.h>

#include "accounts.h"
#include "compression.h"
#include "util.h"


int main(void)
{
    /* Run Length Encoding Test */

    String* input = newString("hw kjd kdld ldkd ldld k ldd lkddafsdfdsfsdfa dsaf asdf sadfasdf asdfasdf sadf asdfsdf asdf "); /* empty String */
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