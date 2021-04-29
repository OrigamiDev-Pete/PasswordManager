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

Account* newAccount(String *name, String *url, String *password);

String* getAccountName(Account *acc);

void printAccount(void *account);

void freeAccount(void *account);

#endif /* ACCOUNTS_H */
