#include <stdio.h> /* printf, puts */

#include "accounts.h"
#include "io.h"
#include "util.h"

#define PRINT_COLUMN_DEFAULT_WIDTH 8
#define PRINT_PASSWORD_DEFAULT_WIDTH 20

/* Function Prototypes */
void printLogin(void);
void printMenu(void);
void printSearch(void);
static void printAccountList(LinkedList *accounts);
static LinkedList *fuzzyAccountSearch(LinkedList accounts, String keyword, int numberToFind);
static void parseCommandLineArgs(int argc, char *argv[]);
static void printHelp();

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    parseCommandLineArgs(argc, argv);
    return 0;
  }

  LinkedList* accounts = newLinkedList(NULL);
  boolean running = true;

  while(running == true)
  {
    printLogin();
    int option;
    printf("Option>");
    option = readInt();

    while(option != 4)
    {
      switch (option) 
      {
        case 1: /* Login (Existing User) */
        {
          int task;

          while(task != 7) /* NOTE(pete): Moved while statement */
          {
            printMenu();
            printf("Option>");
            task = readInt();

            switch (task)
            {
              case 1: /* Search and Sort menu */
              {
                printSearch();
                int choice;
                printf("Option>");
                choice = readInt();

                while(choice!=5)
                {
                  switch(choice)
                  {
                    case 1: /* Search database */
                    { 
                      break;
                    }
                    case 2: /* Sort database alphabetically */
                    {
                      break;
                    }
                    case 3: /* Edit account entry */
                    {
                      break;
                    }
                    case 4: /*  Delete account */
                    {
                      /* Enter master password*/
                      /*String* password = readString("Enter password> ");*/
                      break;
                    }
                  }
                }
                break;
              }
              case 2: /* Add New account */
              {
                String* name = readString("Please enter website's name> ");
                String* url = readString("Please enter website's url> ");
                String* password = readString("Please enter password> ");
                
                Account* inputAccount = newAccount(name, url, password);
                linkedListAppend(accounts, inputAccount); 
                linkedListSort(accounts, accountSort);
                break;
              }
              case 3: /* Display stored websites */
              {
                printAccountList(accounts);
                #ifdef DEBUG
                printLinkedList(accounts, printAccount);
                #endif
                break;
              }
              case 4: /* Import database (DC&DE) */
              {
                saveData(accounts, true, HUFFMAN);
                break;
              }
              case 5: /* Export database (E&C) */
              {
                break;
              }
              case 6: /* Log out */
              {
                running = false;
                break;
              }
              default:
              {
                printf("Invalid option.\n");
                break;
              }
            }
          }
          break;
        }
        case 2:
        { /*  Create New Master Account */
          break;
        }
        case 3: 
        { /* Exit Program */
          running = false;
          break;
        }
        default:
        {
          printf("Invalid option.\n");
          break;
        }
      }
    }
  }
  return 0;
}

/* Rough Main Menu idea */
void printLogin(void)
{
  printf("\n\n"
  "*************************************\n"
  "*              Welcome!             *\n"
  "*************************************\n"
  "1. Login (Exisiting User)\n"
  "2. Create New Master Account\n"
  "3. Exit Program\n");
}

void printMenu(void)
{
  printf("\n\n"
  "*************************************\n"
  "*             Main Menu             *\n"
  "*************************************\n"
  "1. Search and Sort menu\n"
  "2. Add New account\n"
  "3. Display stored websites\n" /* NOTE(pete): Maybe 'Display stored accounts' would be more consistent */
  "4. Import database (DC&DE)\n" /* NOTE(pete): Maybe Save/Load makes more sense than Import Export. Thoughts on Auto-Saving? */ 
                                 /* NOTE(luke): We need to make clear that it is the encryption and compression
                                                as they are they main parts of the project. So maybe we should
                                                include that in the name. */
  "5. Export database (E&C)\n"   /* NOTE(luke): Maybe "Save Database (Encrypted and Compressed)"??? */
  "6. Log out\n");
}

void printSearch(void)
{
  printf("\n\n"
  "*************************************\n"
  "*        Search and Sort Menu       *\n"
  "*************************************\n"
  "1. Search database\n"
  "2. Sort database alphabetically\n"
  "3. Edit account entry\n"
  "4. Delete account\n");
}

static void printAccountList(LinkedList *list)
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
        putchar('\n');
    }
}

static LinkedList *fuzzyAccountSearch(LinkedList accounts, String keyword, int numberToFind)
{
  LinkedList *list = newLinkedList(NULL);
  

}

/*******************************************************************************
* Author: Peter de Vroom
* Function: Parses command line arguments. If a valid command is parsed the
*           program executes the command and terminates in place without running
*           the main program. If the command is invalid help text is printed
*           to the standard output.
* Input: argc - number of command line arguments
*        argv - command line arguments
*******************************************************************************/
static void parseCommandLineArgs(int argc, char *argv[])
{
  switch (argv[1][0])
  {
    case '-':
    {
      switch (argv[1][1])
      {
        case 'l':
        {
          if (argc < 3)
          {
            LinkedList *list = newLinkedList(NULL);
            if (loadData(list))
            {
              printAccountList(list);
            }
            else
            {
              puts("Error reading 'accounts.pwm'. Make sure accounts data has been created before reading.");
            }
            freeLinkedList(list, freeAccount);
          }
          else if (argc == 3)
          {
            /* Search and display account */
          }
          else
          {
            puts("Too many parameters. Expected -l <Name>");
          }
          break;
        }
        case 'a':
        {
          if (argc == 5)
          {
            LinkedList *list = newLinkedList(NULL);
            Account *acc = newAccount(newString(argv[2]), newString(argv[3]), newString(argv[4]));
            loadData(list);
            linkedListAppend(list, acc);
            linkedListSort(list, accountSort);
            saveData(list, true, HUFFMAN);
            freeLinkedList(list, freeAccount);
          }
          else if (argc < 5)
          {
            puts("Too few parameters. Expected -a <Name> <URL> <Password>");
          }
          else
          {
            puts("Too many parameters. Expected -a <Name> <URL> <Password>");
          }
          break;
        }
        case 'h':
        {
          printHelp();
          break;
        }
        default:
        {
          puts("--- Unknown Command ---");
          printf("Could not find command \"-%c\".\n\n", argv[1][1]);
          printHelp();
          break;
        }
      }
      break;
    }
    default:
    {
      printHelp();
    }
  }
}

/*******************************************************************************
* Author: Peter de Vroom
* Function: Prints help text for proper operation.
*******************************************************************************/
static void printHelp(void)
{
  puts("Password Manager\n");
  puts("Usage: main [COMMAND] <arguments>\n");
  puts("Commands:");
  puts("-l                           Prints accounts");
  puts("-l <Name>                    Searches for <Name> and prints the account");
  puts("-a <Name> <URL> <Password>   Adds a new account");
  puts("-h                           Prints help menu\n");
}

/*


Login Menu:

*************************************
*         Password Mananger         *
*************************************
  1. Login (Exisiting User)
  2. Create New Master Account
  3. Exit Program


Main Menu (Succesfull Login):

*************************************
*            Main Menu              *
*************************************
   1. Search and Sort menu
   2. Add New account
   3. Display stored websites
   4. Import database (DC&DE)
   5. Export database (E&C)
   6. Settings
   7. Log out


Search Menu:

*************************************
*       Search and Sort Menu        *
*************************************
  1. Search database
  2. Sort database alphabetically
  3. Edit account entry
  4. Delete account


Settings Menu: !(Need to type in master password to delete master account)!

*************************************
*           Settings Menu           *
*************************************
   1. DELETE MASTER ACCOUNT
   2. OPTION 2
   2. OPTION 3

*/