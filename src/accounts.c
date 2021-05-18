#include "accounts.h"

#include <stdio.h> /* malloc, free */

#include "util.h" /* String, freeString */

#define internal static /* static is a vague keyword, internal is more clear */

#define PRINT_COLUMN_DEFAULT_WIDTH 8
#define PRINT_PASSWORD_DEFAULT_WIDTH 20

typedef struct Account {
    String *name;
    String *url;
    String *password;
} Account;

internal void printDashes(int length);


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

void printAccountList(LinkedList *list)
{
    if (list->length == 0)
    {
        puts("No Accounts. Select \"Add New Account\" to create a new account.");
        return;
    }
    else
    {
        int c2Align = PRINT_COLUMN_DEFAULT_WIDTH;
        int c3Align = PRINT_COLUMN_DEFAULT_WIDTH;
        int passLength = PRINT_PASSWORD_DEFAULT_WIDTH;
        
        Node *node = list->head;
        while (node != NULL)
        {
            if (c2Align < ((Account *)(node)->data)->name->length)
                c2Align = ((Account *)(node)->data)->name->length + 1;
            if (c3Align < ((Account *)(node)->data)->url->length)
                c3Align = ((Account *)(node)->data)->url->length + 1;
            if (passLength < ((Account *)(node)->data)->password->length)
                passLength = ((Account *)(node)->data)->password->length + PRINT_COLUMN_DEFAULT_WIDTH;
            node = node->next;
        }

        /* Because the width of the data  */
        char buf[32];
        sprintf(buf, " %%-%ds %%-%ds %%s\n", c2Align, c3Align);

        int dashLength = c2Align + c3Align + passLength;
        printDashes(dashLength);
        printf(buf, "Name", "URL", "Password");
        printDashes(dashLength);

        node = list->head;
        while (node != NULL)
        {
            printf(buf, ((Account *)node->data)->name->text,
                        ((Account *)node->data)->url->text,
                        ((Account *)node->data)->password->text);
            node = node->next;
        }
    }
}

void printDashes(int length)
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
