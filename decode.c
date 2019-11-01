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
    
    int fd_encoded = open("etext", O_RDONLY);
    int fd_decoded = open("ptext", O_WRONLY | O_CREAT);
    
    int n, x;
    char rbuf[1];
    char wbuf[1];
    
    NODE* temp = huffmantree_root;
    do
    {
    	n = read(fd_encoded, rbuf, 1);
    	
    	if(n == 1)
    	{
    		if(rbuf[0] == '\n')   		
    		{
    			wbuf[0] = temp->c;
    			write(fd_decoded, wbuf, 1);
    			wbuf[0] = '\n';
    			write(fd_decoded, wbuf, 1);
    			break;
    		}    		
    		if(temp->left != NULL && temp->right != NULL)
    		{
				if(rbuf[0] == '0')
				{
					temp = temp->left;
					continue;
				}
				else if(rbuf[0] == '1')
				{
					temp = temp->right;
					continue;
				}
				else if(rbuf[0] == ' ')
				{
					wbuf[0] = ' ';
					write(fd_decoded, wbuf, 1);
					continue;
				}
			}
			wbuf[0] = temp->c;
			write(fd_decoded, wbuf, 1); 
			temp = huffmantree_root;
    	}
    }
    while(rbuf[0] != '\n');
    
	close(fd_encoded);
	close(fd_decoded);
	
	printf("Written to ptext.txt\n");
	    
    return 0;
}
