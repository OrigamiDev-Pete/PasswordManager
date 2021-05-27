/*******************************************************************************
* Header files 
*******************************************************************************/
#include "compression.h"
#include <stdio.h> /* sprintf, printf */
#include <stdlib.h> /* atoi */

/* #define DEBUG */


/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/
String_t *member_decompress(const String_t *input);


/*******************************************************************************
* Functions
*******************************************************************************/


String_t* compress(const String_t *input)
{
    int i = 0, p, occ;
    char temp_array[256]; 

    String_t* compressed_string = newString(NULL);
    

    /* iterate through each word in an input string */
    while(i < input->length)
    {
        p = i;

        /* skips spaces and append them straight to the compressed string*/
        if(input->text[i] != ' ')
        {
            while(p < input->length && input->text[p] == input->text[i])
            {
                p++;
            }

            #ifdef DEBUG
            printf("%c has p = %d occurences\n", input->text[p], p);
            #endif /* DEBUG */

            stringAppendChar(compressed_string, input->text[i]);

            if(p - i >= 1)
            {
                occ = p - i;

                 /* Convert occ int to string or char depending on length */

                sprintf(temp_array, "%d", occ); /* Automatically null appends */

                String_t* occ_str = newString(temp_array);

                stringAppend(compressed_string, occ_str->text);

                #ifdef DEBUG
                printf("occ_str = ");
                printString(occ_str);
                #endif /* DEBUG */

                /* Signifies that a char in a member has a double digit 
                   occurence */
                if(occ > 9)
                {
                    stringAppendChar(compressed_string, ';');
                }

                /* free contents of occ_str for next loop */
                freeString(occ_str);
            }

            i = p;

            #ifdef DEBUG
            printf("The next loop uses i = %d\n", i);
            #endif /* DEBUG */
        }
        else
        {
           stringAppendChar(compressed_string, ' ');
           i++;
        }
    }

    #ifdef DEBUG
    printf("Before Compression: ");
    printString(input);
    printf("After Compression: ");
    printString(compressed_string);
    #endif /* DEBUG */

    return(compressed_string);
}


String_t* decompress(const String_t *input)
{
	
    String_t* decompressed_string = newString(NULL);

    int i = 0, p;

    /* Grab the first member/word of the string */
    while(i < input->length)
    {
        String_t* member_str = newString(NULL);

        for(p = i; p < input->length && input->text[p] != ' '; ++p)
        {
            stringAppendChar(member_str, input->text[p]);
        }

        #ifdef DEBUG
        printf("member_str = ");
        printString(member_str);
        #endif /* DEBUG */
       
        stringAppend(decompressed_string, member_decompress(member_str)->text);
        if(p < input->length)
        {
            stringAppendChar(decompressed_string, ' ');
        }

        /* Free member string for next loop*/
        freeString(member_str);

        /* Update i to begin at the next member (Skip space) */
        i = p + 1;

        #ifdef DEBUG
        printf("The next loop uses i = %d\n", i);
        #endif /* DEBUG */
    }

    #ifdef DEBUG
    printString(input);
    printString(decompressed_string);
    #endif /* DEBUG */

    return(decompressed_string);

}

/*******************************************************************************
* Author: Joshua Gonzalez
* Function: decompresses single word string and passes the decompressed word
            back to the decompress function
* Inputs: 
* - compressed string object pointer 
* Outputs: 
* - decompressed string object pointer
*******************************************************************************/
String_t *member_decompress(const String_t *input)
{
    int i = 0, p;
    int count;
    char temp_array[256];

    String_t* decompressed_member = newString(NULL);

    /* convert pairs of letter and occurence */
    while(i < input->length - 1)
    {
        char current_char = input->text[i];

        /* ; signifies a more than 9 occurence */
        if(input->text[i + 3] == ';')
        {
            count = atoi(&input->text[i + 1]);
            i = (i + 2);

            #ifdef DEBUG
            printf("count = %d\n", count);
            #endif /* DEBUG */
        }
        else
        {
            char current_count = input->text[i + 1];
            
            /* Automatically null appends */
            sprintf(temp_array, "%c", current_count); 
            count = atoi(temp_array);

            #ifdef DEBUG
            printf("count = %d\n", count);
            #endif /* DEBUG */
        }

        /* print as many letters as needed */
        for(p = 0; p < count; p++)
        {
            stringAppendChar(decompressed_member, current_char);
        }

        /* Skip to next pair of character and occurence */
        i = (i + 2);

        #ifdef DEBUG
        printf("The next loop uses i = %d\n", i);
        #endif /* DEBUG */
    }

    #ifdef DEBUG
    printf("Before member decompression: ");
    printString(input);
    printf("After member decompression: ");
    printString(decompressed_member);
    #endif /* DEBUG */

    return(decompressed_member);
}


