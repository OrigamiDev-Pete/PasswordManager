#include "accounts.h"

#include <stdio.h>

#include "util.h"

typedef struct Account {
    String *name;
    String *url;
    String *password;
} Account;


Account *CreateAccount(String *name, String *url, String *password)
{
    Account *acc = malloc(sizeof(Account));
    acc->name = name;
    acc->url = url;
    acc->password = password;
    return acc;
}

Account newAccount(char *name, char *url, char *password)
{
    Account acc;
    acc.name = newString(name);
    acc.url = newString(url);
    acc.password = newString(password);
    return acc;
}

String* getAccountName(Account *acc)
{
    return acc->name;
}

void printAccount(Account *acc)
{
    printf("{name: %s, url: %s, password: %s}\n", acc->name->text, acc->url->text, acc->password->text);
}

void freeAccount(Account *account)
{
    freeString(account->name);
    freeString(account->url);   
    freeString(account->password);
    free(account);
}
