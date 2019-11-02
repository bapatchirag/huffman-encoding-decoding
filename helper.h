typedef struct node
{
    struct node* left;
    char c;
    int freq;
    struct node* right;
    struct node* next;
} NODE;

NODE* toRet = NULL; // For preorder traversal

NODE* createNode(char, int);       
NODE* insertNode(NODE*, NODE*);    
NODE* createSubtree(NODE*);
NODE* copyNodeData(NODE*);
NODE* pushNode(NODE*, NODE*);
NODE* popNode(NODE*);
void preorder(NODE*);
NODE* preorderWrap(NODE*);
NODE* routeList(NODE*, char);
void clearList(NODE**);

/*
@brief Creates node to add to list of nodes available and tree/heap
@param __first Character to be encoded/decoded
@param __second Frequency of __first
@return New node created 

Creates a fresh node and initialises the data to the values of that of the parameters provided.
All pointers are initialised to NULL.
*/
NODE* createNode(char ch, int f)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    
    newNode->c = ch;
    newNode->freq = f;
    
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->next = NULL;
    
    return newNode;
}

/*
@brief Inserts node at right place in sorted list of nodes available
@param __first First node of sorted list/sublist
@param __second Node to be inserted in sorted list
@return First node of newly sorted list 

Inserts a node in the sorted list, used to construct Huffman Tree.
*/
NODE* insertNode(NODE* head, NODE* ins)
{
    if(ins == NULL)
    {
        return NULL;
    }
    
    NODE* toIns = createNode(ins->c, ins->freq);
    toIns->left = ins->left;
    toIns->right = ins->right;
    
    if(head == NULL)
    {
        head = toIns;
        return head;
    }
    
    if(head->next == NULL)
    {
        if(toIns->freq < head->freq)
        {
            toIns->next = head;
            head = toIns;
            return head;
        }
        
        head->next = toIns;
        return head;
    }
    
    NODE* temp = head;
    while(temp->next != NULL)
    {
        if(temp->freq < toIns->freq && toIns->freq <= temp->next->freq)
        {
            toIns->next = temp->next;
            temp->next = toIns;
            return head;
        }
        else if(temp->freq > toIns->freq)
        {
            toIns->next = head;
            head = toIns;
            return head;
        }
        temp = temp->next;
    }
    
    temp->next = toIns;
    
    return head;
}

/*
@brief Creates subtree
@param __first First node of sorted list/sublist
@return Root node of subtree created 

Creates a subtree from first two elements of the sublist whose first element is provided.
The new root of the subtree has the frequency value as the sum of each of the frequencies of its children.
The left child is the first node of list/sublist and the right child is the first node's successor.
The newly created root node is also inserted into the list of available nodes.
*/
NODE* createSubtree(NODE* head)
{
    if(head == NULL || head->next == NULL)
    {
    	return NULL;
    }
    
    NODE* intNode = createNode('-', head->freq + head->next->freq);
    intNode->left = head;
    intNode->right = head->next;
    //head = insertNode(head, intNode);
    
    return intNode;
}

/*
@brief Copies node data
@param Node to be copied
@return New node

Creates a new node, copies data from given node and returns the new new node.
No copying of pointers takes place, only data is copied.
*/
NODE* copyNodeData(NODE* src)
{
	NODE* dest = createNode(src->c, src->freq);	
	return dest;
}

/*
@brief Inserts node at end of list
@param __first First node of list
@param __second Node to be inserted
@return First node of list

Inserts a node at the end of the list, whose first node is provided. Basically, like a push operation on a stack.
*/
NODE* pushNode(NODE* head, NODE* toPush)
{
	if(head == NULL)
	{
		return toPush;
	}
	
	NODE* temp = head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	
	temp->next = toPush;
	return head;
}

/*
@brief Deletes node from end of list
@param First node of list
@return First node of list

Deletes a node from the end of the list, whose first node is provided. Basically, like a pop operation on a stack.
*/
NODE* popNode(NODE* head)
{
	NODE* temp = head;
	while(temp->next->next != NULL)
	{
		temp = temp->next;
	}
	
	free(temp->next);
	temp->next = NULL;
	
	return head;
}

/*
@brief Performs preorder traversal of tree
@param Root node of tree
@return Nothing

Recursiely traverses the tree whose root is given, in a preorder manner.
Every node is added to a list, which can be accessed from outside the function.
*/
void preorder(NODE* root)
{
	if(root == NULL)
	{
		return;
	}
	
	toRet = pushNode(toRet, copyNodeData(root));
	preorder(root->left);
	preorder(root->right);	
}

/*
@brief Wrapper for preorder()
@param Root node of tree
@return First node of preordered list

Calls the preorder() function; returns the first node of the preordered list which is compiled in the preorder function itself.
*/
NODE* preorderWrap(NODE* root)
{
	preorder(root);
	return toRet;
}

/*
@brief Creates a route to any leaf
@param __first First node of preorder list
@param __second Character for which route needs to be found
@return First node of route

Traversing the preordered list, the route for the character is calculated from the root of the tree.
Each node in the route is added at the end of a list, and at the end, the first node of that list is returned.
*/
NODE* routeList(NODE* head, char need)
{
	int cons_ctr = 0;
	NODE* temp = head;
	NODE* route = NULL;
	
	while(temp != NULL)
	{
		if(temp->c == '-')
		{
			cons_ctr = 0;
			route = pushNode(route, copyNodeData(temp));
		}
		else
		{
			if(temp->c == need)
			{
				route = pushNode(route, copyNodeData(temp));
				break;
			}
			else
			{
				cons_ctr++;
				if(cons_ctr >= 2)
				{
					route = popNode(route);
				}
			}
		}
		
		temp = temp->next;
	}
	
	return route;
}

/*
@brief Clears list
@param Address of first pointer of list
@return Nothing

Clears list iteratively by freeing up consecutive nodes from the start of the list
*/
void clearList(NODE** head_ref)
{
    NODE* current = *head_ref;
    NODE* next;
    
    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head_ref = NULL;
}
