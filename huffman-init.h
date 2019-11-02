#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "helper.h"

char buf[1];
NODE* freqlist_head = NULL;
NODE* sortedlist_head = NULL;
NODE* htree_root = NULL;

NODE* getHuffmanTreeRoot();
NODE* freqlist(int, NODE*);
NODE* sortlist(NODE*);
NODE* createHuffmanTree(NODE*);

NODE* getHuffmanTreeRoot()
{
    int fd;
        
    fd = open("charset", O_RDONLY);

    freqlist_head = freqlist(fd, NULL);
    close(fd);

    sortedlist_head = sortlist(freqlist_head);
    clearList(&freqlist_head);
    
    htree_root = createHuffmanTree(sortedlist_head);
    
    return htree_root;
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
    NODE* temp_sorted = head;
    NODE* root = NULL;
    NODE* temp_root = NULL;
    
    while(temp_sorted != NULL)
    {
    	temp_root = createSubtree(temp_sorted);
    	if(temp_root == NULL)
    	{
    		return root;
    	}
    	root = temp_root;
    	
    	head = insertNode(head, root);
    	
    	if(temp_sorted->next != NULL)
    	{
    		temp_sorted = temp_sorted->next->next;
    	}
    	else
    	{
    		temp_sorted = NULL;
    	}
    }
    
    return root;
}
