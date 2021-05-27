/*******************************************************************************
* Header files 
*******************************************************************************/
#include "huffman.h"
#include <stdio.h> /* malloc, free */

/* #define DEBUG */

/* Huffman tree node */
struct node{
    char character;
    unsigned int frequency;
    struct node *left, *right;
    boolean isleaf;
};
typedef struct node node_t;

/* Stores unique character and corresponding frequency  */
typedef struct{
    char ch;
    unsigned int freq;
}character_t;

/* Node of huffman code dictionary */
typedef struct{
    char character;
    int code[16];
    int arr_size;
}dnode_t;


/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/
void printHuffmanCodes(node_t* root_node, int code_array[], int top);
node_t* newLeafNode(char character, unsigned int frequency);
node_t* newInternalNode(node_t* node1, node_t* node2);
int BuildHuffmanTree(character_t character_array[], int size, 
                     node_t* priorityqueue[]);
int SaveHuffmanCodes(node_t* root_node, int code_array[], dnode_t huffman_dict[],
                       int top, int d_index);
String* BitConversion(const String *input, dnode_t huffman_dict[], int dict_size);
String* exportTree(node_t* root_node, String* huff_str, int top);
node_t *readNode(const String *tree, int *pos);


/*******************************************************************************
* Functions
*******************************************************************************/


/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Prints huffman codes to stdout from huffman tree
* Inputs: 
* - root node pointer of huffman tree
* - code array
* - top (keeps track of what node the function is up to)
* Outputs: 
* - void
*******************************************************************************/
void printHuffmanCodes(node_t* root_node, int code_array[], int top)
{
    if(root_node->left) 
    {
        code_array[top] = 0;
        printHuffmanCodes(root_node->left, code_array, top + 1);
    }
 
    if (root_node->right) 
    {
        code_array[top] = 1;
        printHuffmanCodes(root_node->right, code_array, top + 1);
    }
 
    if (root_node->isleaf == true) 
    {
        printf("%c: ", root_node->character);
        int i;
        for(i = 0; i < top; i++)
        {
            printf("%d", code_array[i]);
        }
        printf("\n");
    }
}


/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Allocates memory for a new huffman leaf node for a character and its 
*           frequency
* Input: 
* - character
* - frequnecy of character
* Output:
* - new leaf node pointer
*******************************************************************************/
node_t* newLeafNode(char character, unsigned int frequency)
{
    node_t* new_leaf_node = (node_t*) malloc(sizeof(node_t));

    /* Set leaf node characteristics */
    new_leaf_node->character = character;
    new_leaf_node->frequency = frequency;
    new_leaf_node->left = NULL;
    new_leaf_node->right = NULL;
    new_leaf_node->isleaf = true;

    return(new_leaf_node);
}


/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Allocates memory for a new huffman internal node, that points to 
*           two other nodes
* Input: 
* - node 1 pointer
* - node 2 pointer
* Output: 
* - new internal node pointer
*******************************************************************************/
node_t* newInternalNode(node_t* node1, node_t* node2)
{
    node_t* new_internal_node = (node_t*) malloc(sizeof(node_t));

    /* Set internal node characteristics */
    new_internal_node->frequency = (node1->frequency + node2->frequency);
    /* right (bigger frequency node) */
    new_internal_node->left = node1;
    /* left (smaller frequency node) */
    new_internal_node->right = node2;
    new_internal_node->isleaf = false;

    return(new_internal_node);
}


/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Takes array of unique characters and frequncies and builds 
*           a binary huffman tree using a priority queue array of node pointers
* Input: 
* - character structure array
* - size of character array
* - priority queue array
* Output: 
* - tracked length of the priority queue (to free malloced nodes)
*******************************************************************************/
int BuildHuffmanTree(character_t character_array[], int size, 
                      node_t* priorityqueue[])
{
    
    /* Total length of the priorirty queue, for easy reference to free all 
       nodes */
    int priorityQ_len = 0;

    /* Updated length of the priority queue after nodes are added and deleted */
    int priorityQ_index = 0;

    /* Create all leaf nodes and add them to priority queue in descending 
       order */
    int i;
    for(i = 0; i < size; ++i)
    {   
        priorityqueue[priorityQ_index] = newLeafNode(character_array[i].ch,
                                                     character_array[i].freq);
        ++priorityQ_index;
        ++priorityQ_len;
    }

    /* repeatebly take two lowest nodes, add them, and reorder the queue
       until there is only one node left */
    while(priorityQ_index != 1)
    {
        priorityqueue[priorityQ_len] = newInternalNode(
                                        priorityqueue[priorityQ_index - 1],
                                        priorityqueue[priorityQ_index - 2]);
        
        ++priorityQ_index;
        ++priorityQ_len;

        /* Bubble sort priority queue from largest to smallest frequency */
        int k;
        for(k = 0; k < priorityQ_len - 1; k++)
        {
            int j;
            for(j = 0; j < priorityQ_len - k - 1; ++j)
            {
                if(priorityqueue[j]->frequency < priorityqueue[j + 1]->frequency)
                {
                    /* Swap elements in the array */
                    node_t* temp = priorityqueue[j];
                    priorityqueue[j] = priorityqueue[j + 1];
                    priorityqueue[j + 1] = temp;
                }
            }
        }

        /* ignore the 2 nodes that were added to create the new internal 
           node*/
        priorityQ_index -= 2;
    }


    /* return full size of priority queue to free all malloced nodes*/
    return(priorityQ_len);
}


/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Recurssively traverse the huffman tree and assign codes to each 
*           element in character_array
* Inputs: 
* - code array 
* - pointer to top node of huffman tree
* - int to track current level of binary tree
* Outputs: 
*******************************************************************************/
int SaveHuffmanCodes(node_t* root_node, int code_array[], 
                     dnode_t huffman_dict[], int top, int d_index)
{
    if(root_node->left) 
    {
        code_array[top] = 0;
        /* return new d_index to keep track of length of dictionary */
        d_index = SaveHuffmanCodes(root_node->left, code_array, huffman_dict,
                                   top + 1, d_index);
    }
 
    if (root_node->right) 
    {
        code_array[top] = 1;
        /* return new d_index to keep track of length of dictionary */
        d_index = SaveHuffmanCodes(root_node->right, code_array, huffman_dict,
                                   top + 1, d_index);
    }
 
    if (root_node->isleaf == true) 
    {
        huffman_dict[d_index].character = root_node->character;

        /* Print code to dictionary */
        int i;
        for(i = 0; i < top; i++)
        {
            huffman_dict[d_index].code[i] = code_array[i];
        }
        /* Length of code array equals how far down the tree the function is */
        huffman_dict[d_index].arr_size = top;
        ++d_index;
    }

    return(d_index);
}


/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Use bitwise operations to convert characters in original strings 
*           to coded huffman bits
* Inputs: 
* - original string pointer (const)
* - huffman dictionary
* - size of dictionary
* Outputs: 
* - a string of changed bits (in the order of the full huffman compression code)
*******************************************************************************/
String* BitConversion(const String *input, dnode_t huffman_dict[],
                      int dict_size)
{
    String* bit_str = newString(NULL);

    /* store the current position of the bit and code */
    int pos_bit = 8;
    int index_code = 0;

    byte b = 0;

    /* Traverse entire string up until end of string */
    int i = 0;
    while(i < input->length - 1)
    {
        /* store i'th character in string */
        char ch = input->text[i];
        /* store the dictionary position of ch */
        int dict_index = 0;
        
        /* Search for ch in huffman dictionary */
        int j;
        for(j = 0; j < dict_size; ++j)
        {
            if(ch == huffman_dict[j].character)
            {
                dict_index = j;
                break;
            }
        }

        /* change each bit of b depending on the code in the dict,
           stops if the end of the byte is reached or the code is finished */
        int k, l;
        for(k = pos_bit, l = index_code; k > 0 
            && l < huffman_dict[dict_index].arr_size; --k, ++l)
        {
            if(huffman_dict[dict_index].code[l] == 1)
                setBit(b, k);
        }

        /* Check for pos_bit and index_ code conditions */

        /* Condition 1: finished code but not byte */
        if(l == huffman_dict[dict_index].arr_size && k > 0)
        {
            index_code = 0;
            pos_bit = k;
        }
        /* Condition 2: finished the byte but not the code */
        else if(k == 0 && l < huffman_dict[dict_index].arr_size)
        {
            stringAppendChar(bit_str, b);
            b = 0;
            index_code = l;
            pos_bit = 8;
            --i;
        }
        /* Condition 3: finished the byte and the code */
        else if(k == 0 && l == huffman_dict[dict_index].arr_size)
        {
            stringAppendChar(bit_str, b);
            b = 0;
            index_code = 0;
            pos_bit = 8;
        }

        ++i;
    }

    /* add last byte that may have padded 0's*/
    if(pos_bit != 8)
    {
         stringAppendChar(bit_str, b);
    }

    /* DEBUG: Prints each converted bit as an int and char */
    #ifdef DEBUG
    puts("Test output string as integers:");
    for(i = 0; i < bit_str->length - 1; ++i)
    {
        printf("%d=%c ", bit_str->text[i], bit_str->text[i]);
    }
    printf("\n");
    #endif /* DEBUG */

    return(bit_str);
}


/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Recursively traverses huffman tree and outputs it as a compressed 
*           code (leaf node = 1 and internal node = 0)
* Inputs: 
* - priority queue (root node of tree)
* - result string
* - top (keeps track of what node the function is up to)
* Outputs: 
* - coded huffman tree as a string pointer object
*******************************************************************************/
String* exportTree(node_t* root_node, String* huff_str, int top)
{
    if(root_node->isleaf == false) 
    {
        stringAppendChar(huff_str, '0');

        if(root_node->left)
            huff_str = exportTree(root_node->left, huff_str, top + 1);

        if(root_node->right)
            huff_str = exportTree(root_node->right, huff_str, top + 1);
    }

    if (root_node->isleaf == true) 
    {
        stringAppendChar(huff_str, '1');
        stringAppendChar(huff_str, root_node->character);
    }

    return(huff_str);
}


result_t HuffmanCompression(const String *input)
{
    /*Convert string to an array of character_t structures with each element
    * representing a unique character and its corresponding frequency*/
    character_t character_array[256];

    int occ;
    char ch;
    int i, size = 0;

    /* checks for null character as string datatype automatically appends to 
       end */
    for(i = 0; i < input->length -1; i++)
    {
        occ = 0;
        ch = input->text[i];
        int unique_ch_flag = 0;

        /* Sets flag to check if new character is unique */
        int k;
        for(k = 0; k < size; k++)
        {
            if(ch == character_array[k].ch)
            {
                unique_ch_flag = 1;
                break;
            }
        }
        
        /* If the character is unique add it to the array */
        if(unique_ch_flag == 0)
        {
            int j;
            for(j = 0; j < input->length; j++)
            {
                if(ch == input->text[j])
                {
                    ++occ;
                }
            }
            
            character_array[size].ch = ch;
            character_array[size].freq = occ;
            ++size;
        }
        
    }

    /* Bubble sort character array from largest to smallest frequency */
    for(i = 0; i < size - 1; i++)
    {
        int j;
        for(j = 0; j < size - i - 1; ++j)
        {
            if(character_array[j].freq < character_array[j + 1].freq)
            {
                /* Swap elements in the array */
                character_t temp = character_array[j];
                character_array[j] = character_array[j + 1];
                character_array[j + 1] = temp;
            }
        }
    }

    /* Create Priority Queue */
    node_t* priorityqueue[256];

    /* Build Huffman Tree */
    int priorityQ_length;

    priorityQ_length = BuildHuffmanTree(character_array, size, 
                                        priorityqueue);
    

    /* Create dictionary from printed codes */
    dnode_t huffman_dict[256];

    /* save codes to the huffman dictionary */
    int top = 0, d_index = 0;
    int code_array[256];
    

    SaveHuffmanCodes(priorityqueue[0], code_array, huffman_dict, top, d_index);

    
    /*DEBUG: Prints Huffman Dictionary */
    #ifdef DEBUG
    printf("\nHuffman Dictionary:\n");
    for(i = 0; i < size; i++)
    {   
        printf("%c: ", huffman_dict[i].character);

        int j;
        for(j = 0; j < huffman_dict[i].arr_size; j++)
        {
            printf("%d", huffman_dict[i].code[j]);
        }

        printf(": %d\n", huffman_dict[i].arr_size);
    }
    #endif /* DEBUG */

    /* result structure */
    result_t huff_comp;

    huff_comp.comp_string = BitConversion(input, huffman_dict, size);
    
    /*DEBUG: Prints bit converted input string: */
    #ifdef DEBUG
    puts("Bit converted input string:");
    printString(huff_comp.comp_string);
    #endif /* DEBUG */

    /* Export huffman tree */
    top = 0;
    String* huff_str = newString(NULL);
    huff_comp.huff_tree = exportTree(priorityqueue[0], huff_str, top);
    
    /*DEBUG: Prints compressed huffman tree */
    #ifdef DEBUG
    puts("Compressed huffman tree code:");
    printString(huff_comp.huff_tree);
    #endif /* DEBUG */
    
    /* Calculate the length of the huffman compressed string */
    huff_comp.code_len = 0;
    for(i = 0; i < input->length - 1; ++i)
    {
        char ch = input->text[i];
        int dict_pos;

        int j;
        for(j = 0; j < size; ++j)
        {
            if(ch == huffman_dict[j].character)
            {
                dict_pos = j;
                break;
            }
        }
        huff_comp.code_len = huff_comp.code_len + 
                             huffman_dict[dict_pos].arr_size; 
    }
    
    /*DEBUG: Prints length of huffman code */
    #ifdef DEBUG
    printf("Length of huffman code: %d\n", huff_comp.code_len);
    #endif /* DEBUG */

    /* free pointer nodes in the priority queue array */
    for(i = 0; i < priorityQ_length; ++i)
    {
        free(priorityqueue[i]);
    }

    return(huff_comp);
}


/*******************************************************************************
* Author: Peter de Vroom
* Function: Recurvisely creates nodes and links them to internal nodes to create
*           a huffman tree from a compressed code
* Inputs: 
* - Compressed huffman tree string pointer (const)
* - index pointer of current position in string
* Outputs: 
* - Huffman binary tree node_t pointer
*******************************************************************************/
node_t *readNode(const String *tree, int *pos)
{   
    /* If there is a 1 in the string create a leaf node from the character 
      beside it */
    if (stringGetChar(tree, *pos) == '1')
    {
        *pos += 1;
        return newLeafNode(stringGetChar(tree, *pos), 0);
    }

    /*If there is a 0 in the string create an internal node and increment to 
    the next char in the string to create its children nodes */
    else
    {
        *pos += 1;
        node_t *left = readNode(tree, pos);
        *pos += 1;
        node_t *right = readNode(tree, pos);
        return newInternalNode(left, right);
    }
}


String* HuffmanDecompression(String *huff_tree, String *huff_code, int code_len)
{
    String* decomp_str = newString(NULL);
    
    /* Generate the huffman tree */
    int pos = 0;
    node_t * hufftree = readNode(huff_tree, &pos);

    /*DEBUG: Prints the huffman tree codes */
    #ifdef DEBUG
    int array[256];
    int top = 0;
    puts("Decompressed huffman tree:");
    printHuffmanCodes(hufftree, array, top);
    #endif /* DEBUG */

    /* Location index parameters */
    int bit_pos = 8, i = 0, code_index = 0;
    byte ch = huff_code->text[code_index];

    /*Temp huffman tree for recursion purposes */
    node_t temp = *hufftree;
    
    /* Traverse the huffman tree from the bits within the huff code characters */
    while(i < code_len)
    {
        if(bit_pos > 0) 
        {  
            /* If 1 make the new positon in the tree the right node */
            if(checkBit(ch, bit_pos) == 1)
            {
                temp = *temp.right;
                
                /* If a leaf node is encountered reset to the top of the tree*/
                if(temp.isleaf == true)
                {
                    stringAppendChar(decomp_str, temp.character);
                    temp = *hufftree;
                }
                --bit_pos;
            }
            /* If 0 make the new positon in the tree the left node */
            else
            {
                temp = *temp.left;
                
                /* If a leaf node is encountered reset to the top of the tree*/
                if(temp.isleaf == true)
                {
                    stringAppendChar(decomp_str, temp.character);
                    temp = *hufftree;
                }
                --bit_pos;
            }

            /* Move to the next bit */
            i++;
        }
        /* if all bits of a char have been checked move on to the next char */
        else
        {
            bit_pos = 8;
            ch = huff_code->text[++code_index];
        }
    }

    return(decomp_str);
}