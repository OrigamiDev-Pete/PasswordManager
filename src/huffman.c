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


/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/
node_t* newLeafNode(char character, unsigned int frequency);
node_t* newInternalNode(node_t* node1, node_t* node2);
int BuildHuffmanTree(character_t character_array[], int size, 
                     node_t* priorityqueue[]);
void printHuffmanCodes(node_t* root_node, int code_array[], int top);
String HuffmanCompression(String input);


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
* - code array, 
* - pointer to top node of huffman tree
* - int to track current level of binary tree
* Outputs: 
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


String HuffmanCompression(String input)
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
    
    int top = 0;
    int code_array[256];

    printHuffmanCodes(priorityqueue[0], code_array, top);

    /* free pointer nodes in the priority queue array */
    for(i = 0; i < priorityQ_length; ++i)
    {
        free(priorityqueue[i]);
    }


    /* Create dictionary from printed codes */

    /*https://www.youtube.com/watch?v=Y2mP61demhA/*/
    
    /* Generate compressed string from dictionary */



    /* Output compressed string */ 
    String* test = newString("this is a test");
    return(*test);
}