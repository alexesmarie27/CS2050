//Prelab8

#include <stdio.h>
#include <stdlib.h>

typedef struct bt_{
	int value;
	struct bt_* right;
	struct bt_* left;
}BST;

BST* insert(BST* root, int value);
void printTree(BST* root);
void displayBST(BST* root, int depth);
void padding(char toPrint, int numTimes);

int main()
{
	int number, i;
	BST* root = NULL;

	for(i=0; i<9; i++)
	{
		printf("Enter a number: ");
                scanf("%d", &number);
                root = insert(root, number);
	}

	/*
	do{
		printf("Enter a number: ");
		scanf("%d", &number);
		root = insert(root, number);
	}while(number != -1);
	*/	
	
	printTree(root);
		
	return 0;
}

BST* insert(BST* root, int value)
{
	if(root == NULL)
	{
		root = malloc(sizeof(BST));
		root->value = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	
	else if(root->value > value)
	{
		root->left = insert(root->left, value);
		return root;
	}
	
	else if(root->value <= value)
	{
		root->right = insert(root->right, value);
		return root;
	}
		
}

void printTree(BST* root)
{
	displayBST(root, 0);
}

void displayBST(BST* root, int depth)
{
	if(root == NULL)
	{
		padding(' ', depth);
		printf("-\n");
		return;
	}
	
	displayBST(root->left, depth+4);
	padding(' ', depth);
	printf("%d\n", root->value);
	displayBST(root->right, depth+4);
}

void padding(char toPrint, int numTimes)
{
	int i;
	for(i=0; i < numTimes; i++)
		printf("%c", toPrint);
}
