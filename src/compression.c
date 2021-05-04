/*******************************************************************************
* Header files 
*******************************************************************************/
#include "compression.h"
#include <stdio.h> /* sprintf */
#include <stdlib.h> /* atoi */

/* #define DEBUG */


/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/
String member_decompress(String input);

/*******************************************************************************
* Functions
*******************************************************************************/
String compress(String input)
{
    int i = 0, p, occ;
    char temp_array[256]; 

    String* compressed_string = newString(NULL);
    

    while(i < input.length)
    {
        p = i;
        if(input.text[i] != ' ')
        {
            while(p < input.length && input.text[p] == input.text[i])
            {
                p++;
            }

            #ifdef DEBUG
            printf("%c has p = %d occurences\n", input.text[p], p);
            #endif /* DEBUG */

            stringAppendChar(compressed_string, input.text[i]);

            if(p - i >= 1)
            {
                occ = p - i;

                 /* Convert occ int to string or char depending on length */

                sprintf(temp_array, "%d", occ); /* Automatically null appends */

                String* occ_str = newString(temp_array);

                stringAppend(compressed_string, occ_str->text);

                #ifdef DEBUG
                printString(occ_str);
                #endif /* DEBUG */

                /* Signifies that a char in a member has a double digit occurence */
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
    printString(input)
    printString(compressed_string);
    #endif /* DEBUG */

    return(*compressed_string); /*Output Examples a3b6c1e1 or a12;91c2*/
}

/*******************************************************************************
* Problems to think about:
* If passwords can have spaces how can i differentiate between a space between 
* string members and spaces within a string hmmmmmm, MAYBE PASSWORDS CANNOT 
* CONTAIN SPACES
* If a password has say more than 9 occurences of a number how to differentiate 
* between the number of occureneces and a number in the original string 
* e.g. Input: aaaaaaaaaaaa8, potential output; a12;81 rather than a1281
*******************************************************************************/

/* Seperate decompress into 2 subfunctions one to handle members in a string 
* that contain a ; symbol and one to handle a member with no char having
* more than single digit occurences
*******************************************************************************/

String decompress(String input)
{
	
    String* decompressed_string = newString(NULL);

    int i = 0, p;

    /* Grab the first member of the string */
    while(i < input.length)
    {
        String* member_str = newString(NULL);

        for(p = i; p < input.length && input.text[p] != ' '; ++p)
        {
            stringAppendChar(member_str, input.text[p]);
        }

        #ifdef DEBUG
        printString(member_str);
        #endif /* DEBUG */
       
        stringAppend(decompressed_string, member_decompress(*member_str).text);
        if(p < input.length)
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

    return(*decompressed_string);

}


String member_decompress(String input)
{
    int i = 0, p;
    int count;
    char temp_array[256];

    String* decompressed_member = newString(NULL);

    while(i < input.length - 1)
    {
        char current_char = input.text[i];

        if(input.text[i + 3] == ';')
        {
            count = atoi(&input.text[i + 1]);
            i = (i + 2);

            #ifdef DEBUG
            printf("count = %d", count);
            #endif /* DEBUG */
        }
        else
        {
            char current_count = input.text[i + 1];
            sprintf(temp_array, "%c", current_count); /* Automatically null appends */
            count = atoi(temp_array);

            #ifdef DEBUG
            printf("count = %d", count);
            #endif /* DEBUG */
        }

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
    printString(input);
    printString(decompressed_string);
    #endif /* DEBUG */

    return(*decompressed_member);
}
