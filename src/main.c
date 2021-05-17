#include <stdio.h>

#include "accounts.h"
#include "compression.h"
#include "huffman.h"
#include "io.h"
#include "util.h"
#include "encryption.h"

/* Function Prototypes */
void printLogin();
void printMenu();
void printSearch();


int main(void)
{
  LinkedList* accounts = newLinkedList(NULL);
  boolean running = true;
  while(running==true)
  {
    printLogin();
    int option;
    printf("Option>");
    option = readInt();
    while(option!=4)
    {
      switch(option)
    {
      case 1: /* Login (Existing User) */

        printMenu();
        int task;
        printf("Option>");
        task = readInt();
        while(task!=7)
        {
          switch(task)
          {
            case 1: /* Search and Sort menu */

              printSearch();
              int choice;
              printf("Option>");
              choice = readInt();
              while(choice!=5)
              {
                switch(choice)
                {
                  case 1: /* Search database */
                  break;
                  case 2: /* Sort database alphabetically */
                  break;
                  case 3: /* Edit account entry */
                  break;
                  case 4: /*  Delete account */
                    /* Enter master password*/
                    /*String* password = readString("Enter password> ");*/
                  break;
                }
              } 

            break;
            case 2: /* Add New account */
              ; /* fix later */
              String* name = readString("Please enter website's name> ");
              String* url = readString("Please enter website's url> ");
              String* password = readString("Please enter password> ");
              
              Account* inputAccount = newAccount(name, url, password);
              linkedListAppend(accounts, inputAccount); 
            break;
            case 3: /* Display stored websites */

              printLinkedList(accounts, printAccount);
            break;
            case 4: /* Import database (DC&DE) */
            break;
            case 5: /* Export database (E&C) */
            break;
            case 6: /* Log out */
              running = false;
            break;
            default: printf("Invalid option.\n");
          }
        }

      break;
      case 2: /*  Create New Master Account */
      break;
      case 3:  /* Exit Program */
        running =false;
      break;
      default: printf("Invalid option.\n");
    }

  }

  }

  return 0;
}

/* Rough Main Menu idea */
void printLogin()
{
  printf("\n\n"
  "*************************************\n"
  "*              Welcome!             *\n"
  "*************************************\n"
  "1. Login (Exisiting User)\n"
  "2. Create New Master Account\n"
  "3. Exit Program\n");
}

void printMenu()
{
  printf("\n\n"
  "*************************************\n"
  "*             Main Menu             *\n"
  "*************************************\n"
  "1. Search and Sort menu\n"
  "2. Add New account\n"
  "3. Display stored websites\n"
  "4. Import database (DC&DE)\n"
  "5. Export database (E&C)\n"
  "6. Log out\n");
}

void printSearch()
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