#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* Huffman tree node */
struct node
{
    char character;
    unsigned int frequency;
    struct node *left, *right;
    bool isleaf;
};
typedef struct node node_t;

/* Stores unique character and corresponding frequency  */
typedef struct{
    char ch;
    unsigned int freq;
}character_t;


/*******************************************************************************
* Function Prototypes
*******************************************************************************/
node_t* newLeafNode(char character, unsigned int frequency);
node_t* newInternalNode(node_t* node1, node_t* node2);
int BuildHuffmanTree(character_t character_array[], int size, 
                     node_t* priorityqueue[]);
/*void printHuffmanCodes(node_t* root_node, int code_array[], int top); */
void HuffmanCompression(char string[]);


/*******************************************************************************
* Function creates a new huffman leaf node for a character and its frequency
*******************************************************************************/
node_t* newLeafNode(char character, unsigned int frequency)
{
    node_t* new_leaf_node = (node_t*) malloc(sizeof(node_t));

    new_leaf_node->character = character;
    new_leaf_node->frequency = frequency;
    new_leaf_node->left = NULL;
    new_leaf_node->right = NULL;
    new_leaf_node->isleaf = true;

    return(new_leaf_node);
}


/*******************************************************************************
* Function creates a new huffman internal node, combining two leaf nodes
*******************************************************************************/
node_t* newInternalNode(node_t* node1, node_t* node2)
{
    node_t* new_internal_node = (node_t*) malloc(sizeof(node_t));

    new_internal_node->frequency = (node1->frequency + node2->frequency);

    /* right (bigger frequency node) */
    new_internal_node->left = node1;
    /* left (smaller frequency node) */
    new_internal_node->right = node2;
    new_internal_node->isleaf = false;

    return(new_internal_node);
}


/*******************************************************************************
* Takes array of unique characters and frequncies and builds huffman tree
*******************************************************************************/
int BuildHuffmanTree(character_t character_array[], int size, 
                      node_t* priorityqueue[])
{
    
    int priorityQ_size = 0;
    int free_size = 0;

    /*Create all leaf nodes and add them to priority queue in descending order*/
    int i;
    for(i = 0; i < size; ++i)
    {   
        priorityqueue[priorityQ_size] = newLeafNode(character_array[i].ch, character_array[i].freq);
        ++priorityQ_size;
        ++ free_size;
    }

    /* repeatebly take two lowest nodes, add them, and reorder the queue
     * until there is only one node left */

    while(priorityQ_size != 1)
    {
        priorityqueue[priorityQ_size] = newInternalNode(priorityqueue[priorityQ_size - 1],
        priorityqueue[priorityQ_size - 2]);
        
        ++priorityQ_size;
        ++ free_size;

        /* Bubble sort priority queue from largest to smallest frequency */
        int k;
        for(k = 0; k < priorityQ_size - 1; k++)
        {
            int j;
            for(j = 0; j < priorityQ_size - k - 1; ++j)
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

        /* get rid of the 2 nodes that were added to create the new internal node*/
        priorityQ_size -= 2;
    }

    return(free_size);
}


/*******************************************************************************
* Traverses huffman tree and assigns codes to each element in character_array
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
* Takes a string and returns an array of unique characters and an array of the 
* corresponding character frequencies
*******************************************************************************/
void HuffmanCompression(char string[])
{
    /*Convert string to an array of character_t structures with each element
    * representing a unique character and itscorresponding frequency*/
    character_t character_array[256];

    int occ;
    char ch;
    int i, size = 0;

    for(i = 0; i < strlen(string); i++)
    {
        occ = 0;
        ch = string[i];
        int unique_ch_flag = 0;

        int k;
        for(k = 0; k < size; k++)
        {
            if(ch == character_array[k].ch)
            {
                unique_ch_flag = 1;
                break;
            }
        }

        if(unique_ch_flag == 0)
        {
            int j;
            for(j = 0; j < strlen(string); j++)
            {
                if(ch == string[j])
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
    int num;

    num = BuildHuffmanTree(character_array, size, priorityqueue);
    
    int top = 0;
    int code_array[256];

    printHuffmanCodes(priorityqueue[0], code_array, top);

    /* free the priority queue array */
    for(i = 0; i < num; ++i)
    {
        free(priorityqueue[i]);
    }

}


/* Driver main function*/
int main(void)
{
    char user_input[] = "abb";

    HuffmanCompression(user_input);

    return(0);
}