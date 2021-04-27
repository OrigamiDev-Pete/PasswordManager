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
typedef struct Account {
    String *name;
    String *url;
    String *password;
} Account;

Account* CreateAccount();

void printAccount();

#endif /* ACCOUNTS_H */