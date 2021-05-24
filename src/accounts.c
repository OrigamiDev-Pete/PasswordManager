#include "accounts.h"

#include <stdio.h> /* malloc, free */

#include "util.h" /* String, freeString, LinkedList */

#define internal static /* static is a vague keyword, internal is more clear */

Account* newAccount(String *name, String *url, String *password)
{
    Account *acc = malloc(sizeof(Account));
    acc->name = name;
    acc->url = url;
    acc->password = password;
    return acc;
}

void printAccount(void *acc)
{
    printf("{name: %s, url: %s, password: %s}", ((Account *)acc)->name->text, 
                                                 ((Account *)acc)->url->text,
                                                 ((Account *)acc)->password->text);
}

boolean accountSort(void *accountA, void *accountB)
{
    Account accA = *(Account *)accountA;
    Account accB = *(Account *)accountB;
    if (stringCompare(accA.name, accB.name) == 1)
        return true;
    else
        return false;
}

void freeAccount(void *account)
{
    freeString(((Account *)account)->name);
    freeString(((Account *)account)->url);   
    freeString(((Account *)account)->password);
    free(account);
}
