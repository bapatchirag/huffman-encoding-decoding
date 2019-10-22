#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "helper.h"

//char buf[10];
NODE* huffmantree_root = NULL;

NODE* freqlist(FILE*, NODE*);
NODE* sortlist(NODE*);
NODE* createHuffmanTree(NODE*);

int main()
{
    //int fd;
    char fname[50];
    NODE* freqlist_head = NULL;
    NODE* sortedlist_head = NULL;
    
    printf("Enter name of file in directory to read and initialise Huffman tree: ");
    scanf("%s", fname);
    
    FILE* fp = fopen(fname, "r");
    //fd = open(fname, O_RDONLY);

    freqlist_head = freqlist(fp, NULL);
    fclose(fp);
    
    NODE* temp = freqlist_head;
    while(temp != NULL)
    {
        //printf("%c\n");
        printf("%c\t%d\n", temp->c, temp->freq);
    }
    
    sortedlist_head = sortlist(freqlist_head);
    clearList(&freqlist_head);
    
    huffmantree_root = createHuffmanTree(sortedlist_head);
    printf("%d\n", huffmantree_root->freq);
    clearList(&sortedlist_head);
    
    return 0;
}

/*
@brief Creates frequency list of all characters in the file
@param __first File descriptor for file from which list is to be compiled
@param __second First node of frequency list
@return First node of frequency list

Only creates an unsorted list of characters and their respective frequencies. Spaces are ignored (feature can be changed).
*/
NODE* freqlist(FILE* fp, NODE* head)
{
    NODE* temp;
    int flag_elefound = 0;
    char ch;
    while(ch != EOF)
    {
        if(ch == ' ')
        {
            continue;
        }
        
        temp = head;       
        if(temp == NULL)
        {
            temp = createNode(ch, 1);
            head = temp;
        }
        else
        {
            while(temp->next != NULL)
            {
                if(temp->c == ch)
                {
                    temp->freq += 1;
                    flag_elefound = 1;
                    break;
                }
                temp = temp->next;
            }
            if(flag_elefound != 1)
            {
                temp->next = createNode(ch, 1);
            }
        }
    }
    if(ch == EOF)
    {
        return head;
    }
    else
    {
        return NULL;
    }
}

/*
@brief Sorts previously created frequency list
@param First node of frequency list
@return First node of sorted frequency list

Sorts the previously created frequency list and creates a new list.
*/
NODE* sortlist(NODE* head)
{
    NODE* temp_freqlist = head;
    NODE* sort_head = NULL;
    
    while(temp_freqlist != NULL)
    {
        sort_head = insertNode(sort_head, temp_freqlist);
        temp_freqlist = temp_freqlist->next;
    }
    
    return sort_head;
}

/*
@brief Creates Huffman Tree
@param First node of sorted frequency list
@return Root node of Huffman Tree

The tree is created via a bottom-up, max-heap approach (tree is actually a max-heap)
*/
NODE* createHuffmanTree(NODE* head)
{
    NODE* temp = head;
    NODE* root = NULL;
    
    while(temp != NULL)
    {
        root = createSubtree(temp);
        temp = temp->next->next;
    }
    
    return root;
}
