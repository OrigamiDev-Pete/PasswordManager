#include "accounts.h"

#include <stdio.h>

#include "util.h"

typedef struct Account {
    String *name;
    String *url;
    String *password;
} Account;


Account *newAccount(String *name, String *url, String *password)
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

void freeAccount(void *account)
{
    freeString(((Account *)account)->name);
    freeString(((Account *)account)->url);   
    freeString(((Account *)account)->password);
    free(account);
}
