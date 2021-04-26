/*******************************************************************************
* Author: Luke Phillips
* Date Updated: 26/04/2021
* 
* The header file for the ecryption functionality of the program.
*
*******************************************************************************/

/*******************************************************************************
* Author: Luke Phillips
* Function: to encrypt a database file containing a collection of user accounts
* the whole file will be encrypted with each run of this function.
* Input: the name of the file to be encrypted.
* Output: a boolean value indicating sucess (1) or failure (0)
*******************************************************************************/
int encryptAccounts(char filename[]);

/*******************************************************************************
* Author: Luke Phillips
* Function: to decrypt a database file containing a collection of user accounts
* Input: the name of the file to be encrypted.
* Output: a boolean value indicating sucess (1) or failure (0)
*******************************************************************************/
int decryptAccounts(char filename[]);
