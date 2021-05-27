#include "io.h"

#include <stdio.h> /* fopen, fclose, scanf, getchar, fscanf, fprintf, getc */

#include "accounts.h" /* Account, newAccount, freeAccount */
#include "compression.h" /* encryptString, decryptString */
#include "encryption.h" /* compress, HuffmanCompression,  */

#define internal static /* static is a vague keyword, internal is more clear */

internal String_t* accountsToString(const LinkedList_t *accounts);
internal String_t* fileToString(FILE *f);
internal void stringToAccounts(const String_t *string, LinkedList_t *accounts);

boolean saveData(const LinkedList_t *accounts, boolean encrypt, compressionType cmpType)
{

    /* Turn accounts into a String to be passed to encryption/compression, then saved */
    String_t *str = accountsToString(accounts);
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
            String_t *compStr = compress(str);
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
}


internal String_t *accountsToString(const LinkedList_t *accounts)
{
    String_t *str = newString(NULL);
    
    int i;
    for (i = 0; i < accounts->length; i++)
    {
        Account_t *acc = linkedListGet(accounts, i)->data;
        stringAppend(str, acc->name->text);
        stringAppendChar(str, '\n');
        stringAppend(str, acc->url->text);
        stringAppendChar(str, '\n');
        stringAppend(str, acc->username->text);
        stringAppendChar(str, '\n');
        stringAppend(str, acc->password->text);
        stringAppendChar(str, '\n');
    }

    return str;
}

boolean loadData(LinkedList_t *accounts)
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
                String_t *str = fileToString(f);
                if (encryptedflag)
                    decryptString(str);

                stringToAccounts(str, accounts);
                freeString(str);
                break;
            }
            case RUN_LENGTH:
            {
                String_t *str = fileToString(f);
                if (encryptedflag)
                    decryptString(str);

                String_t *decompStr = decompress(str);

                stringToAccounts(decompStr, accounts);
                freeString(decompStr);
                freeString(str);
                break;
            }
            case HUFFMAN:
            {
                int huffmanTreeLengthBits, huffmanTreeLengthBytes;
                fscanf(f, "%d %d ", &huffmanTreeLengthBits, &huffmanTreeLengthBytes);

                String_t *huffmanTree = newString(NULL);
                int i;
                for (i = 0; i < huffmanTreeLengthBytes-1; i++)
                {
                    stringAppendChar(huffmanTree, getc(f));
                }

                String_t *str = fileToString(f);

                if (encryptedflag)
                    decryptString(str);

                String_t *decompStr = HuffmanDecompression(huffmanTree, str, huffmanTreeLengthBits);

                stringToAccounts(decompStr, accounts);
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

internal String_t *fileToString(FILE *f)
{
    String_t *str = newString(NULL);
    int c;
    while ((c = getc(f)) != EOF)
    {
        stringAppendChar(str, (char) c);
    }
    return str;
}

internal void stringToAccounts(const String_t *string, LinkedList_t *accounts)
{
    linkedListClear(accounts, freeAccount);
    int i = 0;
    char c;
    while ((c = stringGetChar(string, i)) != '\0')
    {
        String_t *name, *url, *username, *password;
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

        username = newString(NULL);
        while ((c = stringGetChar(string, i++)) != '\n' && c != '\0')
        {
            stringAppendChar(username, c);
        }

        password = newString(NULL);
        while ((c = stringGetChar(string, i++)) != '\n' && c != '\0')
        {
            stringAppendChar(password, c);
        }
        Account_t *acc = newAccount(name, url, username, password);
        linkedListAppend(accounts, acc);
    }
}

String_t* platformPath(void)
{
    String_t *path = newString(NULL);
    #ifdef __linux__
    stringAppend(path, getenv("HOME"));
    stringAppendChar(path, '/');
    return path;
    #endif
    #ifdef __MINGW32__
    stringAppend(path, getenv("USERPROFILE"));
    stringAppend(path, "\\Documents\\");
    return path;
    #endif
}

int readInt(void)
{
    int temp;
    while (scanf("%d", &temp) != 1)
        getchar(); /* consumes non-int characters */
        
    while (getchar() != '\n'); /* flush the input */
    return temp;
}
