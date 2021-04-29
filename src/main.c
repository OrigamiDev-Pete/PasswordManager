#include <stdio.h>

#include "accounts.h"
#include "compression.h"
#include "util.h"

/* void LLprintAccount(void *acc)
{
    Account *tmp = (Account *)acc;
    printf("{name: %s, url: %s, password: %s}", tmp->name->text, tmp->url->text, tmp->password->text);
}
 */
int main(void)
{
    int i = 150;
    LinkedList *list = newLinkedList(&i, sizeof(int));
    int j = 200;
    linkedListAppend(list, &j);
    int k = 250;
    linkedListAppend(list, &k);
    int l = 300;
    linkedListAppend(list, &l);

    printLinkedList(list, printInt);
    freeLinkedList(list);

    Account *acc = CreateAccount(readString(), readString(), readString());
    printAccount(acc);

    Account *acc2 = CreateAccount(newString("Amazon"), newString("www.google.com"), newString("password"));
    printAccount(acc2);

    freeAccount(acc);
    freeAccount(acc2);

/*     Account acc;
    acc.name = newString("Google");
    acc.url = newString("www.google.com");
    acc.password = newString("Password");
    LinkedList *list2 = newLinkedList(&acc, sizeof(Account)); */

/*     Account acc2;
    acc2.name = newString("Amazon");
    acc2.url = newString("www.amazon.com");
    acc2.password = newString("Password1234");
    linkedListAppend(list2, &acc2); */

    /* printLinkedList(list2, LLprintAccount); */
    /* freeLinkedList(list2); */
   /*  Account acc3 = newAccount("test", "test.com", "test123");
    freeAccount(&acc3);
    printf("%s", acc3.name->text); */


    String *string = newString(NULL); /* empty String */
    stringAppend(string, "Appending to the string");
    printString(string);

    String *string2 = newString("Setting the string at initialisation");
    printString(string2);

    printf("Enter a string> ");
    String *stdRead = readString(); /* A string can be created directly from stdin */
    printString(stdRead);

    freeString(string);
    free(string2);
    free(stdRead);

    return 0;
}