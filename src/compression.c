/*******************************************************************************
* Header files 
*******************************************************************************/
#include "compression.h"

/* #define DEBUG */

String compress(String input)
{
    int i = 0;

    String *compressed_string = newString(NULL);

    while( i < input.length)
    {
        int p = i;
        if(input.text[i] != ' ')
        {
            while(p < input.length && input.text[p] == input.text[i])
            {
                p++;
            }

            stringAppendChar(compressed_string, input.text[i]);

            if(p - i > 1)
            {
                int occ = p - i;
                stringAppendChar(compressed_string, (char) occ);
            }

            i = p;
        }
        else
        {
           stringAppendChar(compressed_string, ' ');
           i++;
        }
    }

    return(*compressed_string);
}


















String decompress(String input)
{
	return *newString(NULL);
}
