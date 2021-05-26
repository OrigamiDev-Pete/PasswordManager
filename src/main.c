#include <stdio.h> /* printf, puts, remove */

#include "accounts.h"
#include "io.h"
#include "util.h"

#define internal static /* static is a vague keyword, internal is more clear */

/* Function Prototypes */
void printLogin(void);
void printMenu(void);
void printSearch(void);
internal void parseCommandLineArgs(int argc, char *argv[]);
internal void printHelp();
internal void printAdmin();
int searchAccounts(LinkedList *list, String *searchWord);

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
                String* username = readString("Please enter a username> ");
                String* password = readString("Please enter password> ");
                
                Account* inputAccount = newAccount(name, url, username, password);
                linkedListAppend(accounts, inputAccount); 
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


/*******************************************************************************
* Author: Peter de Vroom, Luke Phillips
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
            LinkedList *list = newLinkedList(NULL);
            if (loadData(list))
            {
              String *keyword = newString(argv[2]);
              int index = searchAccounts(list, keyword);

              /* Create a stack-allocated LinkedList in this case to house the one account.
              *  Heap allocation is avoided here so as to not double free the contents of
              *  the new LinkedList. Rather acc will merely contain a copy of one of the accounts
              *  in list */
              LinkedList acc;
              acc.head = linkedListGet(list, index);
              acc.head->next = NULL;
              acc.length = 1;

              /* If the search and result do not exactly match, tell the user. */
              if (stringCompare(keyword, ((Account *)acc.head->data)->name) != 0)
              {
                printf("Could not find \"%s\". Nearest match found: \"%s\"\n", 
                  keyword->text,
                  ((Account *)acc.head->data)->name->text);
              }

              printAccountList(&acc);
              freeString(keyword);
            }
          }
          else
          {
            puts("Too many parameters. Expected -l <Name>");
          }
          break;
        }
        case 'a':
        {
          if (argc == 6)
          {
            LinkedList *list = newLinkedList(NULL);
            Account *acc = newAccount(newString(argv[2]), newString(argv[3]), newString(argv[4]), newString(argv[5]));
            loadData(list);
            linkedListAppend(list, acc);
            sortLinkedListAlphabetically(list, compareAccounts);
            saveData(list, true, HUFFMAN);
            freeLinkedList(list, freeAccount);
          }
          else if (argc < 5)
          {
            puts("Too few parameters. Expected -a <Name> <URL> <Username> <Password>");
          }
          else
          {
            puts("Too many parameters. Expected -a <Name> <URL> <Username> <Password>");
          }
          break;
        }
        case 'h':
        {
          printHelp();
          break;
        }
        /* Author: Luke - Added administrator run time mode */
        case 'p':
        {
          /*if(stringCompare(newString(argv[1]), newString("admin"))) {*/
            boolean running = true;
            while(running) {
              printAdmin();
              int choice;
              printf("Option> ");
              choice = readInt();
              switch(choice) {
                case 1:     /* Reset all program data */
                {
                  int delKeys = remove("keys.bin");
                  int delAcc = remove("accounts.pwm");
                  if(delKeys != 1 && delAcc != 1) {
                    puts("--- All Stored Data Has Been Reset ---\n");
                  }
                  else {
                    puts("Failed, some data was not deleted or did not exist.");
                  }       
                  break;
                }
                case 2:     /* Exit administrator mode */
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
          /*}*/
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

int searchAccounts(LinkedList *list, String *searchWord){
    int i, j, accurate, mostAccurate, MAindex;
    int size = list->length;
    String accName;
    mostAccurate = 0;
    accurate = 0;
    MAindex = 0;


    for(i = 0; i < size; i++){

        accName = *((Account*)linkedListGet(list, i)->data)->name;

        for(j = 0; j < searchWord->length && j < accName.length; j++){
            if(stringGetChar(searchWord, j) == stringGetChar(&accName, j)){
              accurate++;
            }
            if(accurate > mostAccurate){
              MAindex = i;
              mostAccurate = accurate;
            }
        }
    }
  return MAindex;
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
  puts("-p <Pass>                    Enter Administrator mode if <Pass> is correct\n");
}

/*******************************************************************************
* Author: Luke Phillips
* Function: Prints options for administrator menu.
*******************************************************************************/
static void printAdmin(void) 
{
  puts("*************************************");
  puts("*        Administrator Menu         *");
  puts("*************************************");
  puts("  1. Reset All Data");
  puts("  2. Exit Program");
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