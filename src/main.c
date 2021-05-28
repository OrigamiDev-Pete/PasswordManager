/*******************************************************************************
 * Fundamentals of C - Autumn 2021 - Group Assessment
 * Password Manager Tool "Ccret Keeper" 
 * 
 * Students: Luke Phillips - 13591476, Sam Zammit - 99201838
 *           Peter de Vroom - 13294196, Giovanni Tjandra - 13752454
 *           Joshua Gonzalez - 13915158
 * 
 * How to Operate: 
 *  - Linux or ED - type 'make' to build the program, then ./bin/main.out to
 *    execute. Use 'make build debug' - for the debug mode.
 *  - MinGW compiler - type 'mingw32-make win' to build the program.
 *       Note for Windows: the makefile is expecting a ‘bin’ directory,  
 *       a ‘src’ directory, and a ‘src/obj’ directory
 * Follow the on screen menu prompts to navigate and use the program.
 * Use ./bin/main.out -p to enter administrator mode and reset data.
*******************************************************************************/

#include <stdio.h> /* printf, puts, remove */

#include "accounts.h"
#include "io.h"
#include "util.h"

#define internal static /* static is a vague keyword, internal is more clear */

/* Function Prototypes */
internal void printMenu(void);
internal void printSearch(void);
internal void printSettings(void);
internal String_t* readAndValidateString(const char *prompt);
internal void parseCommandLineArgs(int argc, char *argv[]);
internal void printHelp();
internal void printAdmin();
internal int searchAccounts(LinkedList_t *list, String_t *searchWord);

/*  Global Variables */
internal boolean encryption = true;
internal compressionType compression = HUFFMAN;

/*******************************************************************************
* Author: Giovanni Tjandra
* Function: The main function handles all of the program's user interace.
*           When command-line args are passed the main function will exit early.
*******************************************************************************/
int main(int argc, char *argv[])
{
  #ifdef DEBUG
  puts("\n<< Debug mode is active >>");
  #endif /* DEBUG */

  if (argc > 1)
  {
    parseCommandLineArgs(argc, argv);
    return 0;
  }

  LinkedList_t* accounts = newLinkedList(NULL);
  boolean running = true;

  while(running == true)
  {
    int task=0;

    while(task != 7)
    {
      printMenu();
      printf("Option> ");
      task = readInt();
      switch (task)
      {
        case 1: /* Search and Sort menu */
        {
          int choice=0;
          while(choice!=4)
          {
            printSearch();
            printf("Option> ");
            choice = readInt();
            switch(choice)
            {
              case 1: /* Search database */
              {
                /* NOTE(pete): correct searching requires that the list is sorted.
                  *             This should be fine under normal operation. */
                String_t *keyword = readString("Please enter the account name> ");
                int index = searchAccounts(accounts, keyword);

                /* Create a stack-allocated LinkedList in this case to house the one account.
                *  Heap allocation is avoided here so as to not double free the contents of
                *  the new LinkedList. Rather acc will merely contain a copy 
                *  to a reference of one of the accounts in the list */
                LinkedList_t acc;
                acc.head = linkedListGet(accounts, index);
                acc.length = 1;

                /* If the search and result do not exactly match, tell the user. */
                if (stringCompare(keyword, ((Account_t *)acc.head->data)->name) != 0)
                {
                  printf("Could not find \"%s\". Nearest match found: \"%s\"\n", 
                  keyword->text,
                  ((Account_t *)acc.head->data)->name->text);
                }

                printAccountList(&acc);
                freeString(keyword);
                break;
              }
              case 2: /* Edit account entry */
              {
                printAccountList(accounts);
                int entry=0;
                printf("Please select an account>");
                entry = readInt();
                entry--; /* LinkedList is 0 based but table format is 1 based so we need to decrement. */
                if (entry < accounts->length)
                {
                  /* Run Length compression won't allow ';' characters so must be checked*/
                  String_t *name = readAndValidateString("Please enter a website's name> ");
                  String_t *url = readAndValidateString("Please enter a website's url> ");
                  String_t *username = readAndValidateString("Please enter a website's username> ");
                  String_t *password = readAndValidateString("Please enter a website's password> ");
                  
                  Account_t* inputAccount = newAccount(name, url, username, password);
                  linkedListSet(accounts, entry, inputAccount, freeAccount); /* Set an account for selection */
                  linkedListSortAlphabetically(accounts, compareAccounts); /* sort everytime an account is added */
                }
                else
                {
                  puts("Invalid selection");
                }
                break;
              }
              case 3: /*  Delete account */
              {
                if (accounts->length != 0)
                {
                  printAccountList(accounts);
                  int entry = 0;
                  printf("Please select an account> ");
                  entry = readInt();
                  entry--; /* LinkedList is 0 based but table format is 1 based so we need to decrement. */
                  if (entry < accounts->length)
                  {
                    Account_t acc = *(Account_t *)linkedListGet(accounts, entry)->data;
                    printf("Account: %s has been deleted.\n", acc.name->text);
                    linkedListRemove(accounts, entry, freeAccount);
                  }
                  else
                  {
                    puts("Invalid selection");
                  }
                }
                else
                  puts("No Accounts. Select \"Add New Account\" in the main \
                        menu to create a new account.\n");

                break;
              }
              case 4:
                break;
              default:
              {
                puts("Invalid option");
                break;
              }
            }
          }
          break;
        }
        case 2: /* Add New account */
        {
          /* Run Length compression won't allow ';' characters so must be checked*/
          String_t *name = readAndValidateString("Please enter a website's name> ");
          String_t *url = readAndValidateString("Please enter a website's url> ");
          String_t *username = readAndValidateString("Please enter a website's username> ");
          String_t *password = readAndValidateString("Please enter a website's password> ");
          
          Account_t* inputAccount = newAccount(name, url, username, password);
          linkedListAppend(accounts, inputAccount);
          linkedListSortAlphabetically(accounts, compareAccounts); /*sort everytime an account is added*/ 
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
        case 4: /* Load database */
        {
          if (loadData(accounts))
          {
            puts("Loaded Successfully! Decrypted and Decompressed");
          }
          else
          {
            puts("Error reading 'accounts.pwm'. Make sure accounts data has \
                  been created before reading.");
          }
          break;
        }
        case 5: /* Save database */
        {
          if (accounts->length != 0)
          {
            if (saveData(accounts, encryption, compression))
            {
              printf("Saved Successfully!");
              if(encryption)
                printf(" Encrypted,");
              if(compression == HUFFMAN || compression == RUN_LENGTH) 
                printf(" Compressed,");
              printf(" Saved to 'accounts.pwm'");
            }
            else
              puts("There was an problem with saving the file. Accounts \
                    were not saved.");
          }
          else
            puts("No Accounts. Select \"Add New Account\" in the main menu \
                  to create a new account.\n");

          break;
        }
        case 6: /* Settings */
        {
          int option=0;

          while (option !=3)
          {
            printSettings();
            printf("Option> ");
            option = readInt();

            switch (option)
            {
              case 1: /* config encryption */
              {
                if (encryption)
                {
                  encryption=false;
                }
                else
                {
                  encryption=true;
                }
                break;
              }
              case 2: /* config compression */
              {
                int type=0;

                printf("\n1. Huffman\n"
                "2. Run length\n"
                "3. None\n");
                printf("Option> ");
                type = readInt();

                switch (type)
                {
                  case 1:
                    compression = HUFFMAN;
                    break;
                  
                  case 2:
                    compression = RUN_LENGTH;
                    break;
                  
                  case 3:
                    compression = NONE;
                    break;
                  
                  default:
                    break;
                }
                break;
              }
              case 3:
                break;
              default:
                puts("Invalid option");
                break;
            }
          }
          break;
        }
        case 7: /* Exit Program */
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
return 0;
}

/*******************************************************************************
* Author: Giovanni Tjandra
* Function: Main Menu
*******************************************************************************/
internal void printMenu(void)
{
  printf("\n\n"
  "*************************************\n"
  "*             Main Menu             *\n"
  "*************************************\n"
  "1. Edit menu\n"
  "2. Add New account\n"
  "3. Display stored accounts\n" 
  "4. Load database\n" 
  "5. Save database\n"                       
  "6. Settings\n"                       
  "7. Exit\n");
}

/*******************************************************************************
* Author: Giovanni Tjandra
* Function: Edit Menu
*******************************************************************************/
internal void printSearch(void)
{
  printf("\n\n"
  "*************************************\n"
  "*             Edit Menu             *\n"
  "*************************************\n"
  "1. Search database\n"
  "2. Edit account entry\n"
  "3. Delete account\n"
  "4. Return to main menu\n");
}

/*******************************************************************************
* Author: Giovanni Tjandra
* Function: Settings menu
*******************************************************************************/
internal void printSettings(void)
{
  printf("\n\n"
  "*************************************\n"
  "*             Settings              *\n"
  "*************************************\n");
  if(encryption)
  {
    printf("1. Encryption: Enabled\n");
  }
  else 
  {
    printf("1. Encryption: Disabled\n");
  }

  if(compression==HUFFMAN)
  {
    printf("2. Compression: Huffman\n");
  }
  else if(compression==RUN_LENGTH)
  {
    printf("2. Compression: Run Length\n");
  }
  else
  {
    printf("2. Compression: None\n");
  }

  printf("3. Return to main menu\n");
}

/*******************************************************************************
* Author: Peter de Vroom
* Function: This acts as a wrapper around readString, adding a layer of 
*           abitrary validation. In this case Strings are invalid if they are
*           empty or if they contain ';' characters.
* Input: prompt - takes a c-string that is printed before input is taken.
* Output: Returns a pointer to heap-allocated String struct.
*******************************************************************************/
internal String_t *readAndValidateString(const char *prompt)
{
  String_t *string;
  while ((string = readString(prompt))->length == 1 ||
        stringContains(string, ';'))
  {
    if (stringContains(string, ';'))
      puts("String cannot contain ';' characters");
    else
      puts("String cannot be empty");
    freeString(string);
  }
  return string;
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
internal void parseCommandLineArgs(int argc, char *argv[])
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
            LinkedList_t *list = newLinkedList(NULL);
            if (loadData(list))
            {
              printAccountList(list);
            }
            else
            {
              puts("Error reading 'accounts.pwm'. Make sure accounts data has \
                    been created before reading.");
            }
            freeLinkedList(list, freeAccount);
          }
          else if (argc == 3)
          {
            /* Search and display account */
            LinkedList_t *list = newLinkedList(NULL);
            if (loadData(list))
            {
              String_t *keyword = newString(argv[2]);
              int index = searchAccounts(list, keyword);

              /* Create a stack-allocated LinkedList in this case to house the one account.
              *  Heap allocation is avoided here so as to not double free the contents of
              *  the new LinkedList. Rather acc will merely contain a copy of one of the accounts
              *  in list */
              LinkedList_t acc;
              /* Take a dereferenced copy of the Node */
              acc.head = linkedListGet(list, index);
              acc.length = 1;

              /* If the search and result do not exactly match, tell the user. */
              if (stringCompare(keyword, ((Account_t *)acc.head->data)->name) != 0)
              {
                printf("Could not find \"%s\". Nearest match found: \"%s\"\n", 
                  keyword->text,
                  ((Account_t *)acc.head->data)->name->text);
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
            LinkedList_t *list = newLinkedList(NULL);
            Account_t *acc = newAccount(newString(argv[2]), newString(argv[3]), newString(argv[4]), newString(argv[5]));
            loadData(list);
            linkedListAppend(list, acc);
            linkedListSortAlphabetically(list, compareAccounts);
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
          /*if(!stringCompare(newString(argv[1]), newString("admin"))) {*/
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

/*******************************************************************************
* Author: Sam Zammit
* Function: A function that returns the location of a word that the user is 
            searching for. 
* Input: Takes in the linked list of accounts aswell as the string of the word
        that the user wishes to search.
* Output: Returns the integer index of the most accurate account that the user
          is trying to look for. 
*******************************************************************************/
int searchAccounts(LinkedList_t *list, String_t *searchWord){
    int i, j, accurate, mostAccurate, MAindex;
    int size = list->length;
    String_t *accName;
    mostAccurate = 0;
    accurate = 0;
    MAindex = 0;


  for(i = 0; i < size; i++){

      accName = ((Account_t*)linkedListGet(list, i)->data)->name;

      for(j = 0; j < searchWord->length && j < accName->length; j++){
          if(stringGetChar(searchWord, j) == stringGetChar(accName, j)){
            accurate++;
          }
      }
      if(accurate > mostAccurate){
        MAindex = i;
        mostAccurate = accurate;
      }
  }
  return MAindex;
}


/*******************************************************************************
* Author: Peter de Vroom
* Function: Prints help text for command-line arguments.
*******************************************************************************/
internal void printHelp(void)
{
  puts("Password Manager\n");
  puts("Usage: main [COMMAND] <arguments>\n");
  puts("Commands:");
  puts("-l                                      Prints accounts");
  puts("-l <Name>                               Searches for <Name> and prints the account");
  puts("-a <Name> <URL> <Username> <Password>   Adds a new account");
  puts("-h                                      Prints help menu\n");
  puts("-p <Pass>                               Enter Administrator mode if <Pass> is correct\n");
}

/*******************************************************************************
* Author: Luke Phillips
* Function: Prints options for administrator menu.
*******************************************************************************/
internal void printAdmin(void) 
{
  puts("*************************************");
  puts("*        Administrator Menu         *");
  puts("*************************************");
  puts("  1. Reset All Data");
  puts("  2. Exit Program");
}