#include "io.h"

#include <stdio.h> /* fopen, fclose, scanf, getchar */

#include "accounts.h" /* Account */
#include "compression.h"
#include "encryption.h"
#include "huffman.h"

#define internal static /* static is a vague keyword, internal is more clear */

internal String *accountsToString(const LinkedList *accounts);
internal String *fileToString(FILE *f);
internal void stringToAccounts(const String *string, LinkedList *accounts);

boolean saveData(const LinkedList *accounts, boolean encrypt, compressionType cmpType)
{
    /* Saving an empty list will effectively clear the data file. */
    if (accounts->length == 0)
    {
        FILE *f = fopen("accounts.pwm", "w");
        if (f)
        {
            fclose(f);
            return true;
        }
        else
            return false;
    }

    /* Turn accounts into a String to be passed to encryption/compression, then saved */
    String *str = accountsToString(accounts);
    result_t cmpResult;

    switch (cmpType)
    {
        case NONE:
        {            
            if (encrypt)
            {
                encryptString(str);
            }
            break;
        }
        case RUN_LENGTH:
        {
            String *compStr = compress(str);
            freeString(str);
            str = compStr;
            compStr = NULL;
            if (encrypt)
                encryptString(str);
            break;
        }
        case HUFFMAN:
        default:
        {
            cmpResult = HuffmanCompression(str);
            freeString(str);
            str = cmpResult.comp_string;
            cmpResult.comp_string = NULL;
            if (encrypt)
                encryptString(str);
            break;
        }
    }


    FILE *f = fopen("accounts.pwm", "w");
    if (f)
    {
        /* FILE FORMAT:
        * Byte 1 = encryption flag
        * Byte 2 = compressionType flag 
        * (if Byte 2 is 1) Bytes 3-6 = Huffman Tree length bits
        * (if Byte 2 is 1) Byte 8-11 = Huffman Tree length bytes
        * (if Byte 2 is 1) Bytes 13-? = Huffman Tree 
        * Remainder Bytes = String data */
    
        fprintf(f, "%c%c", encrypt, cmpType);
        if (cmpType == HUFFMAN)
        {
            fprintf(f, "%d %d %s", cmpResult.code_len, (int)cmpResult.huff_tree->length, cmpResult.huff_tree->text);
            freeString(cmpResult.huff_tree);
        }
        fprintf(f, "%s", str->text);
        fclose(f);
        return true;
    }
    else
        return false;




    puts("Original:");
    puts("---------------------------");
    printString(str);
    result_t result = HuffmanCompression(str);
    freeString(str);
    encryptString(result.comp_string);
    puts("Compressed->Encrypted:");
    puts("---------------------------");
    printString(result.comp_string);
    decryptString(result.comp_string);
    String *str2 = HuffmanDecompression(result.huff_tree, result.comp_string, result.code_len);
    puts("Decompressed->Dencrypted:");
    puts("---------------------------");
    printString(str2);
    freeString(str2);

    return true;
}


String *accountsToString(const LinkedList *accounts)
{
    String *str = newString(NULL);
    
    int i;
    for (i = 0; i < accounts->length; i++)
    {
        Account *acc = linkedListGet(accounts, i)->data;
        stringAppend(str, acc->name->text);
        stringAppendChar(str, '\n');
        stringAppend(str, acc->url->text);
        stringAppendChar(str, '\n');
        stringAppend(str, acc->password->text);
        stringAppendChar(str, '\n');
    }

    return str;
}

boolean loadData(LinkedList *accounts)
{
    FILE *f = fopen("accounts.pwm", "r");
    if (f)
    {
        byte encryptedflag;
        compressionType cmpType;
        byte temp;

        fscanf(f, "%c%c", &encryptedflag, &temp);
        cmpType = temp;
        switch (cmpType)
        {
            case NONE:
            {
                String *str = fileToString(f);
                if (encryptedflag)
                    decryptString(str);

                stringToAccounts(str, accounts);
                freeString(str);
                break;
            }
            case RUN_LENGTH:
            {
                String *str = fileToString(f);
                if (encryptedflag)
                    decryptString(str);

                String *decompStr = decompress(str);

                stringToAccounts(decompStr, accounts);
                freeString(decompStr);
                freeString(str);
                break;
            }
            case HUFFMAN:
            {
                int huffmanTreeLengthBits, huffmanTreeLengthBytes;
                fscanf(f, "%d %d ", &huffmanTreeLengthBits, &huffmanTreeLengthBytes);

                String *huffmanTree = newString(NULL);
                int i;
                for (i = 0; i < huffmanTreeLengthBytes-1; i++)
                {
                    stringAppendChar(huffmanTree, getc(f));
                }

                String *str = fileToString(f);

                if (encryptedflag)
                    decryptString(str);

                String *decompStr = HuffmanDecompression(huffmanTree, str, huffmanTreeLengthBits);

                stringToAccounts(decompStr, accounts);
                printString(decompStr);
                freeString(huffmanTree);
                freeString(decompStr);
                freeString(str);
                break;
            }
        }
        fclose(f);
        return true;
    }
    else
        return false;
}

String *fileToString(FILE *f)
{
    String *str = newString(NULL);
    int c;
    while ((c = getc(f)) != EOF)
    {
        stringAppendChar(str, (char) c);
    }
    return str;
}

void stringToAccounts(const String *string, LinkedList *accounts)
{
    linkedListClear(accounts, freeAccount);
    int i = 0;
    char c;
    while ((c = stringGetChar(string, i)) != '\0')
    {
        String *name, *url, *password;
        name = newString(NULL);
        while ((c = stringGetChar(string, i++)) != '\n' && c != '\0')
        {
            stringAppendChar(name, c);
        }

        url = newString(NULL);
        while ((c = stringGetChar(string, i++)) != '\n' && c != '\0')
        {
            stringAppendChar(url, c);
        }

        password = newString(NULL);
        while ((c = stringGetChar(string, i++)) != '\n' && c != '\0')
        {
            stringAppendChar(password, c);
        }
        Account *acc = newAccount(name, url, password);
        linkedListAppend(accounts, acc);
    }
}

int readInt(void)
{
    int temp;
    while (scanf("%d", &temp) != 1)
        getchar(); /* consumes non-int characters */
        
    while (getchar() != '\n'); /* flush the input */
    return temp;
}
