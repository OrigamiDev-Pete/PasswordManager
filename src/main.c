#include <stdio.h>

#include "accounts.h"
#include "compression.h"
#include "util.h"


int main(void)
{
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