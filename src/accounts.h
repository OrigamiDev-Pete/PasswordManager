/*******************************************************************************
* Author: 
* 
* The header file exposes functionality for Account structs
* Types: Account, AccountList
*******************************************************************************/

#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include "util.h"

/*******************************************************************************
* Author: Peter de Vroom
* Struct: Account
* Container struct for Account values.
*******************************************************************************/
typedef struct Account Account;

Account newAccount(char *name, char *url, char *password);

Account* CreateAccount(String *name, String *url, String *password);

String* getAccountName(Account *acc);

void printAccount();

void freeAccount(Account *account);

#endif /* ACCOUNTS_H */
