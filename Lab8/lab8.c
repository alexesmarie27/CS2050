#include <stdio.h>
#include <stdlib.h>

typedef struct bt_{
	int value;
	struct bt_* right;
	struct bt_* left;
}BST;

//Prototypes
BST* insert(BST* root, int value);
int search(BST* root, int value);
void printTree(BST* root);
void displayBST(BST* root, int depth);
void padding(char toPrint, int numTimes);

int main(int argc, char* argv[])
{
	//Creates root
	BST* root = NULL;

	FILE* input = fopen(argv[1], "r");

	//Scans numbers into the BST
	int value;
	while(fscanf(input, "%d", &value) != EOF)
	{
		root = insert(root, value);
	}

	//Prints the BST
	printTree(root);

	//Searches for a number in the BST
	int lookNum;
	printf("Enter a number to search for in the tree: ");
	scanf("%d", & lookNum);

	//Looks for number and returns either 1(found) or 0(not found)
	int searchNum = search(root, lookNum);
	if(searchNum == 1)
		printf("%d was found\n", lookNum);
	else
		printf("%d was not found\n", lookNum);

	fclose(input);

	return 0;
}

//Inserts values into the BST in order
BST* insert(BST* root, int value)
{
	//If root is empty, place value at designated place
	if(root == NULL)
	{
		root = malloc(sizeof(BST));
		root->value = value;
		root->right = NULL;
		root->left = NULL;
		return root;
	}

	//If value is less than root, go left
	else if(root->value > value)
	{
		root->left = insert(root->left, value);
		return root;
	}

	//If value is greater than root, go right
	else if(root->value <= value)
	{
		root->right = insert(root->right, value);
		return root;
	}
}

//Searches for a number in the BST
int search(BST* root, int value)
{
	BST* current = root;

	while(current != NULL)
	{
		//If value equals root
		if(value == current->value)
			return 1;

		//If value is greater than root, move right
		else if(value > current->value)
		{
			current = current->right;
		}

		//If value is less than root, move left
		else if(value < current->value)
		{
			current = current->left;
		}
	}

	//If value is not found, return 0
	return 0;

}

//Prints the BST tree
void printTree(BST* root)
{
	displayBST(root, 0);
}

//Supports printTree by displaying the root and its branches
void displayBST(BST* root, int depth)
{
	if(root == NULL)
	{
		padding(' ', depth);
		printf("-\n");
		return;
	}

	displayBST(root->right, depth+4);
	padding(' ', depth);
	printf("%d\n", root->value);
	displayBST(root->left, depth+4);
}

//Adds spaces in between numbers in the tree
void padding(char toPrint, int numTimes)
{
	int i;
	for(i=0; i<numTimes; i++)
		printf("%c", toPrint);
}
