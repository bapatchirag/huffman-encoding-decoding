#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "huffman-init.h"

int main()
{
    NODE* huffmantree_root = getHuffmanTreeRoot();
    int fd_plain = open("ptext", O_RDONLY);
    int fd_encoded = open("etext", O_WRONLY | O_CREAT);
    
    NODE* route_head = NULL;
    int n;
    char rbuf[1];
    char wbuf[1];
    
    NODE* preorder = preorderWrap(huffmantree_root);
    
    while((n = read(fd_plain, rbuf, 1)) == 1)
    {
    	if(rbuf[0] == '\n' || rbuf[0] == ' ')
    	{
    		wbuf[0] = rbuf[0];
    		write(fd_encoded, wbuf, 1);
    		continue;
    	}
    	
    	route_head = routeList(preorder, rbuf[0]);
    	
    	NODE* temp = route_head;
    	NODE* temp_htree = huffmantree_root;
    	while(temp->next != NULL)    	
    	{
    		wbuf[0] = ((temp->next->c == temp_htree->left->c && temp->next->freq == temp_htree->left->freq)?'0':'1');
    		write(fd_encoded, wbuf, 1);
    		temp_htree = ((temp->next->c == temp_htree->left->c && temp->next->freq == temp_htree->left->freq)?temp_htree->left:temp_htree->right);
    		temp = temp->next;
    	}
    	wbuf[0] = '.';
    	write(fd_encoded, wbuf, 1);
    	
    	clearList(&route_head);
    }
    
    printf("Written to etext\n");
    clearList(&preorder);
    
    clearList(&sortedlist_head);
    clearList(&htree_root);

    close(fd_plain);
    close(fd_encoded);
    
    return 0;
}
