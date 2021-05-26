/*******************************************************************************
* Author: 
* 
* The header file exposes functionality for Account structs
* Types: Account
*******************************************************************************/

#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include "util.h" /* String, freeString */

/*******************************************************************************
* Author: Peter de Vroom
* Struct: Account
* Container struct for Account values.
*******************************************************************************/
typedef struct Account {
    String *name;
    String *url;
    String *username;
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
Account* newAccount(String *name, String *url, String *username, String *password);

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
*        -----------------------------------------------------------
*         Name       URL                 Username      Password
*        -----------------------------------------------------------
*         Google     www.google.com      user          password123
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

/*******************************************************************************
* Author: Sam Zammit
* Function: Compares the names of 2 accounts to see which one comes first 
            alphabetically.
* Input: list - A LinkedList
* Output: Returns 1 if the two accounts are already in alphabetical order, 0 if
          not.
*******************************************************************************/

boolean compareAccounts(void* acc1, void* acc2);

#endif /* ACCOUNTS_H */
