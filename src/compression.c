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
String* double_digit_occ(String input);

String* single_digit_occ (String input);

/*******************************************************************************
* Functions
*******************************************************************************/
String* compress(String input)
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

            stringAppendChar(compressed_string, input.text[i]);

            if(p - i >= 1)
            {
                occ = p - i;

                 /* Convert occ int to string or char depending on length */

                sprintf(temp_array, "%d", occ); /* Automatically null appends */

                String* occ_str = newString(temp_array);

                stringAppend(compressed_string, occ_str->text);

                /* Signifies that a char in a member has a double digit occurence */
                if(occ > 9)
                {
                    stringAppendChar(compressed_string, ';');
                }

                /* free contents of occ_str for next loop */
                freeString(occ_str);
            }

            i = p;
        }
        else
        {
           stringAppendChar(compressed_string, ' ');
           i++;
        }
    }

    return(compressed_string); /*Output Examples a3b6c1e1 or a12;91c2*/
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

String* decompress(String input)
{
	
    String* decompressed_string = newString(NULL);

    int i = 0, p;

    String* member_str = newString(NULL);


    /* Grab the first member of the string */
    while(i < input.length)
    {
        for(p = i; p < input.length && input.text[p] != ' '; ++p)
        {
            stringAppendChar(member_str, input.text[p]);
        }

        /* Determines if the member has a ';', 1 for true, 0 for false*/
        int c, semicolon_flag;
        for(c = 0; c < member_str->length; c++)
        {
            if(member_str->text[c] == ';')
            {
                semicolon_flag = 1;
                break;
            }
            else
            {
                semicolon_flag = 0;
            }
        }

        /* Pass member to double_digit_occ */
        if(semicolon_flag == 1)
        {
            /*
            stringAppend(decompressed_string, double_digit_occ(*member_str)->text);
            if(p < input.length)
            {
               stringAppendChar(decompressed_string, ' ');
            }
            */
        }
        /* Pass member to single_digit_occ */
        if(semicolon_flag == 0)
        {
            stringAppend(decompressed_string, single_digit_occ(*member_str)->text);
            if(p < input.length)
            {
               stringAppendChar(decompressed_string, ' ');
            }
        }

        /* Free member string for next loop*/
        freeString(member_str);

        /* Update i to begin at the next member */
        i = p + 1;
    }

    return(decompressed_string);

}

/*
String* double_digit_occ(String input)
{
    return(input)
}
*/

String* single_digit_occ(String input)
{
    int i = 0, p;
    int count;

    String* decompressed_member = newString(NULL);

    while(i < input.length - 1)
    {
        char current_char = input.text[i];

        count = atoi(&input.text[i + 1]);

        for(p = 0; p < count; p++)
        {
            stringAppendChar(decompressed_member, current_char);
        }

        /* Skip to next pair of character and occurence */
        i += 2;
    }

    return(decompressed_member);
}
