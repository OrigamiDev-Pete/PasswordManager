#include <stdio.h>

#include "accounts.h"
#include "compression.h"
#include "huffman.h"
#include "io.h"
#include "util.h"
#include "encryption.h"



int main(void)
{
  boolean running = true;
  while(running=true)
  {
    printLogin();
    int option, login_size= 0;
    printf("Option>");
    scanf("%d",&option);
    while(option!=4)
    {
      switch(option)
    {
      case 1:

        printMenu();
        int task, menu_size=0;
        printf("Option>");
        scanf("%d",&task);
        while(task!=8)
        {
          switch(task)
          {
            case 1:

              printSearch();
              int choice, search_size=0;
              printf("Option>");
              scanf("%d",&choice);
              while(choice!=5)
              {
                switch(choice)
                {
                  case 1:
                  break;
                  case 2:
                  break;
                  case 3:
                  break;
                  case 4: /* Enter master password*/
                    String* password = readString("Enter password> ");
                    
                    printSettings();
                    int del, setting_size=0;
                  break;
                }
              } 

            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 7: running = false;
            break;
            default: printf("Invalid option.\n");
          }
        }

      break;
      case 2:;
      break;
      case 3:;
      break;
      default: printf("Invalid option.\n");
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
  "3. Display stored websites\n"
  "4. Import database (DC&DE)\n"
  "5. Export database (E&C)\n"
  "6. Settings\n"
  "7. Log out\n");
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

void printSettings(void)
{
  printg("\n\n"
  "*************************************\n"
  "*              Settings             *\n"
  "*************************************\n"
  "1. DELETE MASTER ACCOUNT\n");
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