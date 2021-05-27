#include "accounts.h"

#include <stdio.h> /* malloc, free */

#define internal static /* static is a vague keyword, internal is more clear */

#define PRINT_COLUMN_DEFAULT_WIDTH 8
#define PRINT_PASSWORD_DEFAULT_WIDTH 20

internal void printDashes(int length);

Account* newAccount(String *name, String *url, String *username, String *password)
{
    Account *acc = malloc(sizeof(Account));
    acc->name = name;
    acc->url = url;
    acc->username = username;
    acc->password = password;
    return acc;
}

void printAccount(void *acc)
{
    printf("{name: %s, url: %s, username: %s, password: %s}", 
          ((Account *)acc)->name->text, 
          ((Account *)acc)->url->text,
          ((Account *)acc)->username->text,
          ((Account *)acc)->password->text);
}

void printAccountList(LinkedList *list)
{
    if (list->length == 0)
    {
        puts("No Accounts. Select \"Add New Account\" to create a new account.\n");
        return;
    }
    else
    {
        int c2Align = PRINT_COLUMN_DEFAULT_WIDTH;
        int c3Align = PRINT_COLUMN_DEFAULT_WIDTH;
        int c4Align = 14;
        int passLength = PRINT_PASSWORD_DEFAULT_WIDTH;
        
        Node *node = list->head;
        /* while (node != NULL) */
        int i;
        for (i = 0; i < list->length; i++)
        {
            if (c2Align < ((Account *)node->data)->name->length)
                c2Align = ((Account *)node->data)->name->length + 1;
            if (c3Align < ((Account *)node->data)->url->length)
                c3Align = ((Account *)node->data)->url->length + 1;
            if (c4Align < ((Account *)node->data)->username->length)
                c4Align = ((Account *)node->data)->username->length + 1;
            if (passLength < ((Account *)node->data)->password->length)
                passLength = ((Account *)node->data)->password->length + PRINT_COLUMN_DEFAULT_WIDTH;
            node = node->next;
        }

        /* Because the width of the Strings could be anything we need to scale
         * the columns to fit the largest entry. */
        char headerBuffer[32];
        sprintf(headerBuffer, "     %%-%ds %%-%ds %%-%ds %%s\n", c2Align, c3Align, c4Align);

        int dashLength = c2Align + c3Align + c4Align + passLength;
        printDashes(dashLength);
        printf(headerBuffer, "Name", "URL", "Username", "Password");
        printDashes(dashLength);

        char buffer[32];
        sprintf(buffer, " %%d. %%-%ds %%-%ds %%-%ds %%s\n", c2Align, c3Align, c4Align);

        node = list->head;
        int index = 1;
        /* while (node != NULL) */
        for (i = 0; i < list->length; i++)
        {
            printf(buffer, index++,
                        ((Account *)node->data)->name->text,
                        ((Account *)node->data)->url->text,
                        ((Account *)node->data)->username->text,
                        ((Account *)node->data)->password->text);
            node = node->next;
        }
        putchar('\n');
    }
}

/*******************************************************************************
* Author: Peter de Vroom
* Function: Helper function for printAccountList to print the correct amount of
*           dashes.
* Input: length - number of dashes to print.
*******************************************************************************/
internal void printDashes(int length)
{
  int i;
  for (i = 0; i < (length); i++)
      putchar('-');
  putchar('\n');

}

void freeAccount(void *account)
{
    freeString(((Account *)account)->name);
    freeString(((Account *)account)->url);   
    freeString(((Account *)account)->password);
    free(account);
}

boolean compareAccounts(void* acc1, void* acc2){
    Account* a1 = (Account*)acc1;
    Account* a2 = (Account*)acc2;

    if(stringCompare(a1->name, a2->name) > 0){
        return true;
    }else{
        return false;
    }
}
