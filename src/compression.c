/*******************************************************************************
* Header files 
*******************************************************************************/
#include "compression.h"

/* #define DEBUG */

String compress(String input)
{
    int i = 0;

    compressed_string = newString();

    while( i < input.length)
    {
        int p = i;
        if(input.text[i] != " ")
        {
            while(p < input.length && input.text[p] == input.text[i])
            {
                p++;
            }

            stringAppendChar(compressed_string.text, input.text[i]);

            if(p - i > 1)
            {
                int occ = p - i;
                stringAppendChar(compressed_string.text, (char) occ);
            }

            i = p;
        }
        else
        {
           stringAppendChar(compressed_string.text, " ");
           i++;
        }
    }

    return(compressed_string);
}


















String decompress(String input)
{
	
}
