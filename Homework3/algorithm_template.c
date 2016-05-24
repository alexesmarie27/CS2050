//libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*This is needed in order to for us to use our functions because they contain the prototypes
as well as our structures. Make sure you understand what this header file is here
for and why we include it outside of our algorithm.c file*/
#include "header.h"

/********************************** createTreeNode *******************************
 parameters: int value to be inserted in the binary search tree
 returns: pointer to a newly created binary search tree node (BST*)

 -> createTreeNode simply creates a new tree node using the value passed as the
    parameter.
*********************************************************************************/

BST* createTreeNode(int nodeValue, int treeNum)
{
	 //Mallocs memory for new node and establishes the data within the new node
	 BST* newnode = malloc(sizeof(BST));
	 newnode->value = nodeValue;
	 newnode->treeNum = treeNum;
	 newnode->left = NULL;
	 newnode->right = NULL;
	 return newnode;
}

/********************************** insert_BST *****************************************
 parameters: the reference of the root (BST**) and the int value to be inserted.
 returns: void

 -> This function recursively finds the right position in the binary search tree
    for the new value and inserts the node containing the new value in that position.
*****************************************************************************************/

void insert_BST(BST** root, int insertValue, int treeNum)
{
	//If BST is empty
	if(*root == NULL)
	{
		*root = createTreeNode(insertValue, treeNum);
	}

	//If insertValue is less than root value
	else if((*root)->value > insertValue)
	{
		insert_BST(&((*root)->left), insertValue, treeNum);
	}

	//If insertValue is greater than or equal to root value
	else if((*root)->value <= insertValue)
	{
		insert_BST(&((*root)->right), insertValue, treeNum);
	}

}


/********************************** insert_rootList ******************************
 parameters: the reference of the head pointer to the list (BST**) and pointer
             to the root of the new binary search tree
 returns: void

 -> This function inserts the new binary search tree at the BACK of the linked
    list containing pointers to the roots of the binary search trees.
*********************************************************************************/

void insert_rootList(rootList** listHead, BST* new_root)
{
	rootList* current = *listHead;

	//If rootList is empty
	if(*listHead == NULL)
	{
		*listHead = malloc(sizeof(rootList));
		(*listHead)->root = new_root;
		(*listHead)->next = NULL;
	}

	//Moves through linked list to get to the end
	else
	{
		while(current->next != NULL)
		{
			current = current->next;
		}

		current->next = malloc(sizeof(BST));
		current->next->root = new_root;
		current->next->next = NULL;
	}
}

/************************************** BFS **************************************
 parameters: the pointer to the start of the linked list and the int value to be
 searched
 returns: void

 -> This function implements a variant of a level by level search or formally
 called as the BREADTH FIRST SEARCH.
 -> This function searches for a given value in the binary trees and it does that
 by searching for level 1 in each binary trees, then moving on to level 2 if
 it fails to find it that value in level 1 and so on.
 -> Basically, you have to search for a given value in all the binary trees, one
 level at a time, in the linked list simultaneously.

 //////////////////////////////////////////////////////////////////////////////
 / HINT: Use the enqueue and dequeue functions to solve this problem. You will
 /       have a hard time solving this problem without using the enqueue and
 /       dequeue functions.
 /////////////////////////////////////////////////////////////////////////////

 *********************************************************************************/

void BFS(rootList* listHead, int searchValue)
{
	//While not at the end of the linked list
	rootList* c = listHead;
	while(c != NULL)
	{
		bfsQ* queue = NULL;
		enqueue(&queue, c->root);
		bfsQ* temp = queue;
		int level = 0;
		int counter = 0;

		//Enqueues each branch
		while(temp != NULL)
		{
			if(temp->treeNode->left != NULL)
			{
				enqueue(&queue, temp->treeNode->left);
			}

			if(temp->treeNode->right != NULL)
			{
				enqueue(&queue, temp->treeNode->right);
			}

			temp = temp->next;
		}

		BST* current = dequeue(&queue);

		//As the numbers are dequeued, searches for the desired value
		while(current != NULL)
		{

			if(current->value == searchValue)
			{
				//print info
				printf("%-7d%-7s%-7d%-7d\n", searchValue, "YES", current->treeNum, level);

				//Frees the queue
				while(current != NULL)
				{
					current = dequeue(&queue);
				}

				return;
			}

			current = dequeue(&queue);
			counter++;

			//Determines level
			if(counter >= 2*level+1)
			{
				level++;
			}
		}

		//Moves to next root
		c = c->next;
	}

	//print info if not found
	printf("%-7d%-7s%-7s%-7s\n", searchValue, "NO", "N/A", "N/A");
}

/************************************ enqueue ************************************
 parameters: the reference of the head of the queue and pointer to the tree node
             to be inserted in the queue
 returns: void

 -> This Function inserts the new tree node in the queue that is used to do a BFS.

 *********************************************************************************/

void enqueue(bfsQ** qHead, BST* new_tree_node)
{
	bfsQ* current = *qHead;

	//If queue is empty
	if(*qHead == NULL)
	{
		*qHead = malloc(sizeof(bfsQ));
		(*qHead)->treeNode = new_tree_node;
		(*qHead)->next = NULL;

	}
	//Else, move to end of queue
	else
	{
		while(current->next != NULL)
		{
			current = current->next;
		}

		current->next = malloc(sizeof(bfsQ));
		current->next->treeNode = new_tree_node;
		current->next->next = NULL;
	}
}

/********************************** dequeue **************************************
 parameters: the reference of the head of the queue.
 returns: pointer to the dequeued tree node

 -> This Function dequeue's the tree node in front of the queue and returns it.

 *********************************************************************************/

BST* dequeue(bfsQ** qHead)
{
	//If queue is empty, dont do anything
	if(*qHead == NULL)
		return NULL;

	BST* deQNode = (*qHead)->treeNode;
	*qHead = (*qHead)->next;

	return deQNode;
}

/********************************** printTrees **************************************
 parameters: pointer to the head of the linked list
 returns: void

 -> This Function prints all the binary search trees in the linked list
 *********************************************************************************/

void printTrees(rootList* listHead)
{
	//Empty
	if(listHead == NULL)
		return;

	//Calls print inorder to print BST
	int treeNum = 1;
	while(listHead != NULL)
	{
		printf("Tree %d: ", treeNum++);
		print_BST_inorder(listHead->root);
		printf("\n");
		listHead = listHead->next;
	}
}

/****************************** print_BST_inorder *******************************
 parameters: pointer to the root of the tree
 returns: void

 -> This Function prints the binary search tree using inorder traversal
 *********************************************************************************/

void print_BST_inorder(BST* root)
{
	if(root == NULL)
		return;

	print_BST_inorder(root->left);
	printf("%d ", root->value);
	print_BST_inorder(root->right);
}

/********************************* free_list *************************************
 parameters: reference of the pointer to the head of the linked list
 returns: void

 -> This function frees all the allocated memory.
 -> This function also calls the free_BSTs function to free the binary search trees.
 *********************************************************************************/

void free_list(rootList** listHead)
{
	if(*listHead == NULL)
		return;

	rootList* temp = *listHead;

	//Goes through list erasing memory usage
	while(temp != NULL)
	{
		free_BSTs((temp)->root);
		rootList* temp2 = temp;
		free(temp);
		temp = temp2;
		temp = temp->next;
	}

}

/********************************* free_BSTs *************************************
 parameters: Pointer to the root of the binary search tree
 returns: void

 -> This function frees all the nodes in the given binary search tree recursively.
 *********************************************************************************/

void free_BSTs(BST* root)
{
	if(root == NULL)
		return;

	//Frees memory from BSTs
	free_BSTs(root->left);
	free_BSTs(root->right);

	free(root);
}
