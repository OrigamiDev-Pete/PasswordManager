/*******************************************************************************
* Author: Joshua Gonzalez
* Date Updated: 26/04/2021
* 
* The header file for the compression functionality of the program.
*
*******************************************************************************/

#ifndef COMPRESSION_H;

#define COMPRESSION_H;

/*******************************************************************************
* Define: Function takes information from a database .txt file 
* compresses it creates a new compressed database file
* Inputs:
* - name of database file
* Outputs:
* - a boolean value indicating success of failure
*******************************************************************************/
int compress_file(char filename[]);


/*******************************************************************************
* Define: Function takes information from a file compressed database .txt file
* and uncompresses it into a new database file
* Inputs:
* - name of database file
* Outputs:
* - a boolean value indicating success of failure
*******************************************************************************/
int decompress_file(char filename[]);


#endif      /*COMPRESSION_H*/
