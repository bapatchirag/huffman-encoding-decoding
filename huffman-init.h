#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "helper.h"

char buf[1];
NODE* huffmantree_root = NULL;

int getHuffmanTreeRoot();
NODE* freqlist(int, NODE*);
NODE* sortlist(NODE*);
NODE* createHuffmanTree(NODE*);

int getHuffmanTreeRoot()
{
    int fd;
    NODE* freqlist_head = NULL;
    NODE* sortedlist_head = NULL;
    
    fd = open("charset.txt", O_RDONLY);

    freqlist_head = freqlist(fd, NULL);
    close(fd);

    sortedlist_head = sortlist(freqlist_head);
    clearList(&freqlist_head);
    
    huffmantree_root = createHuffmanTree(sortedlist_head);
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
NODE* freqlist(int fd, NODE* head)
{
    NODE* temp;
    int n = 0;
    char ch;
    while((n = read(fd, buf, 1)) == 1)
    {
        int flag_elefound = 0;
        ch = buf[0];
        if(ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
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
            if(temp->c == ch)
            {
                temp->freq += 1;
                flag_elefound = 1;
            }
            if(flag_elefound != 1)
            {
                temp->next = createNode(ch, 1);
            }
        }
    }
    if(n == 0)
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
    int i = 0;
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
    NODE* temp_sortlist = head;
    NODE* temp_root;
    NODE* root = NULL;
    
    while(temp_sortlist != NULL || temp_sortlist->next != NULL)
    {
        temp_root = createSubtree(temp_sortlist);
        if(temp_root != NULL)
        {   
            root = temp_root;
        }
        else
        {
            return root;
        }
        
        if(temp_sortlist->next != NULL)
        {
            temp_sortlist = temp_sortlist->next->next;
        }
        else
        {
            temp_sortlist = temp_sortlist->next;
        }
    }
    
    return root;
}
