typedef struct node
{
    struct node* left;
    char c;
    int freq;
    struct node* right;
    struct node* next;
} NODE;

NODE* createNode(char, int);       
NODE* insertNode(NODE*, NODE*);    
NODE* createSubtree(NODE*);
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
