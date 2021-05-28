/*******************************************************************************
* Author: Peter de Vroom, Sam Zammit
* 
* The header file exposes functionality for Account structs
* Types: Account
*******************************************************************************/

#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include "util.h" /* String, freeString, stringCompare */

/*******************************************************************************
* Author: Peter de Vroom
* Struct: Account
* Container struct for Account values.
*******************************************************************************/
typedef struct Account {
    String_t *name;
    String_t *url;
    String_t *username;
    String_t *password;
} Account_t;

/*******************************************************************************
* Author: Peter de Vroom
* Function: Creates a new heap-allocated Account Struct.
* Input: name - Website/Service name String
*         url - URL String
*    password - Password String
* Output: Returns an newly allocated and initialised Account
*******************************************************************************/
Account_t* newAccount(String_t *name, String_t *url, String_t *username, String_t *password);

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
*        ---------------------------------------------------------------
*             Name       URL                 Username      Password
*        ---------------------------------------------------------------
*         1.  Google     www.google.com      user          password123
*
* Input: list - A LinkedList
*******************************************************************************/
void printAccountList(LinkedList_t *list);

/*******************************************************************************
* Author: Peter de Vroom
* Function: Frees an account and all Strings within.
* Input: account - An Account. account is a void pointer to allow for flexibility
*                  with LinkedLists.
*******************************************************************************/
void freeAccount(void *account);

/*******************************************************************************
* Author: Sam Zammit
* Function: A function that compares the names of two accounts and returns a 
            boolean based on the outcome. 
* Input: Takes in two accounts to be compared.
* Output: Returns either true or false based on the outcome of the comparison.
*******************************************************************************/

boolean compareAccounts(void* acc1, void* acc2);

#endif /* ACCOUNTS_H */
