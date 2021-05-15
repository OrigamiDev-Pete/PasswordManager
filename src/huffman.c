/*******************************************************************************
* Header files 
*******************************************************************************/
#include "huffman.h"
#include <stdio.h> /* malloc, free */



/* Huffman tree node */
struct node
{
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
typedef struct d_node {
  char character;
  int code[16];
  int arr_size;
} d_node;


/* I will figure out how to change this later, 
   only a temporary fix for now */
/* global variable */
int d_index;


/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/
node_t* newLeafNode(char character, unsigned int frequency);
node_t* newInternalNode(node_t* node1, node_t* node2);
int BuildHuffmanTree(character_t character_array[], int size, 
                     node_t* priorityqueue[]);
void SaveHuffmanCodes(node_t* root_node, int code_array[], d_node huffman_dict[],
                       int top);
String* BitConversion(String input, d_node huffman_dict[], int dict_size);
String* exportTree(node_t* root_node, String* huff_str, int top);
result_t HuffmanCompression(String input);


/*******************************************************************************
* Functions
*******************************************************************************/


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
*           a binary huffman tree using a priority queue array of pointers
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
        priorityqueue[priorityQ_len] = newInternalNode(priorityqueue[priorityQ_index - 1],
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

        /* get rid of the 2 nodes that were added to create the new internal 
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
void SaveHuffmanCodes(node_t* root_node, int code_array[], d_node huffman_dict[],
                       int top)
{
    if(root_node->left) 
    {
        code_array[top] = 0;
        SaveHuffmanCodes(root_node->left, code_array, huffman_dict, top + 1);
    }
 
    if (root_node->right) 
    {
        code_array[top] = 1;
        SaveHuffmanCodes(root_node->right, code_array, huffman_dict, top + 1);
    }
 
    if (root_node->isleaf == true) 
    {
        huffman_dict[d_index].character = root_node->character;

        int i;
        for(i = 0; i < top; i++)
        {
            huffman_dict[d_index].code[i] = code_array[i];
        }
        huffman_dict[d_index].arr_size = top;
        ++d_index;
    }
}


/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Use bitwise operations to convert characters in original strings 
*           to coded huffman bits
* Inputs: 
* - original string
* - huffman dictionary
* - size of dictionary
* Outputs: 
* - a string of changed bits (hopefull huffman compression)
*******************************************************************************/
String* BitConversion(String input, d_node huffman_dict[], int dict_size)
{
    String* bit_str = newString(NULL);

    /* store the current position of the bit and code */
    int pos_bit = 8;
    int index_code = 0;

    byte b = 0;

    /* Traverse entire string up until end of string or NULL character */
    int i = 0;
    while(i < input.length && input.text[i] != '\0')
    {
        /* store i'th character in string */
        char ch = input.text[i];
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
           will stop if the end of the byte is reached or the code is finished */
        int k, l;
        for(k = pos_bit, l = index_code; k > 0 && l < huffman_dict[dict_index].arr_size; --k, ++l)
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

    /* test output string as integers */
    printf("\nTest output string as integers:\n");
    for(i = 0; i < bit_str->length - 1; ++i)
    {
        printf("%d=%c ", bit_str->text[i], bit_str->text[i]);
    }
    printf("\n");

    return(bit_str);
}


/*******************************************************************************
* Author: Joshua Gonzalez
* Function: Recursively traverses huffman tree and outputs it as a compressed 
*           code
* Inputs: 
* - priority queue (root node of tree)
* - result string
* - top (keeps track of what node the function is up to)
* Outputs: 
* - coded huffman tree as a string
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


result_t HuffmanCompression(String input)
{
    /*Convert string to an array of character_t structures with each element
    * representing a unique character and its corresponding frequency*/
    character_t character_array[256];

    int occ;
    char ch;
    int i, size = 0;

    /* checks for null character as string datatype automatically appends to 
       end */
    for(i = 0; i < input.length && input.text[i] != '\0'; i++)
    {
        occ = 0;
        ch = input.text[i];
        int unique_ch_flag = 0;

        /* Sets flag to check if new character is unique*/
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
            for(j = 0; j < input.length; j++)
            {
                if(ch == input.text[j])
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
    d_node huffman_dict[size];

    /* resets global variable each time function is called */
    d_index = 0;

    int top = 0;
    int code_array[256];

    SaveHuffmanCodes(priorityqueue[0], code_array, huffman_dict, top);


    /* Print Huffman Dictionary */
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

    /* result structure */
    result_t huff_comp;

    /* create string of changed bits (should i pass dict as const?) */
    huff_comp.comp_string = BitConversion(input, huffman_dict, size);
    printString(huff_comp.comp_string);

    /* Export huffman tree */
    top = 0;
    String* huff_str = newString(NULL);
    huff_comp.huff_tree = exportTree(priorityqueue[0], huff_str, top);
    printString(huff_comp.huff_tree);
    freeString(huff_str);

    /* Calculate the length of the huffman compressed string */
    huff_comp.code_len = 0;
    for(i = 0; i < input.length - 1; ++i)
    {
        char ch = input.text[i];
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
        huff_comp.code_len = huff_comp.code_len + huffman_dict[dict_pos].arr_size; 
    }
    printf("Length of huffman code: %d\n", huff_comp.code_len);

    /* free pointer nodes in the priority queue array */
    for(i = 0; i < priorityQ_length; ++i)
    {
        free(priorityqueue[i]);
    }

    return(huff_comp);
}