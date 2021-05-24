/*******************************************************************************
* Author: 
* 
* The header file exposes functionality for Account structs
* Types: Account
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

/*******************************************************************************
* Author: Peter de Vroom
* Function: Creates a new heap-allocated Account Struct.
* Input: name - Website/Service name String
*         url - URL String
*    password - Password String
* Output: Returns an newly allocated and initialised Account
*******************************************************************************/
Account* newAccount(String *name, String *url, String *password);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Compares the names between two accounts.
* Input: accountA - An Account. accountA is a void pointer to allow for flexibility
*                  with LinkedLists.
*        accountB - An Account. accountB is a void pointer to allow for flexibility
*                  with LinkedLists
* Output: Returns true if accountA is greater than accountB, otherwise returns false
*******************************************************************************/
boolean accountSort(void *accountA, void *accountB);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Prints an account to stdout.
* Input: account - An Account. account is a void pointer to allow for flexibility
*                  with LinkedLists.
*******************************************************************************/
void printAccount(void *account);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Prints accounts in a table format.
*        -----------------------------------------------
*         Name       URL                Password
*        -----------------------------------------------
*         Google     www.google.com     password123
*
* Input: list - A LinkedList
*******************************************************************************/
void printAccountList(LinkedList *list);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Frees an account and all Strings within.
* Input: account - An Account. account is a void pointer to allow for flexibility
*                  with LinkedLists.
*******************************************************************************/
void freeAccount(void *account);

#endif /* ACCOUNTS_H */
