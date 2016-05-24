#include "bst.h"

//Prototypes
bst* createBST(int a[], int size);
void sort(int a[], int size);
bst* createMinBST(int a[], int start, int end);

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("usage: %s <input_filename>/n", argv[0]);
		return;
	}

	FILE* input = fopen(argv[1], "r");
	if (input == NULL)
		return;

	int i, size;
	fscanf(input, "%d", &size);
	int array[size];

	for(i=0; i<size; i++)
		fscanf(input, "%d", &array[i]);

	//Creates Binary Tree
	printf("Creating Binary Tree...\n");
	bst* root = createBST(array, size);

	//Printing Inorder Traversal
	printf("Inorder Traversal: ");
	printInorder(root);
	printf("\n");

	//Printing Pre-order Traversal
	printf("Pre-Order Traversal: ");
        printPreorder(root);
        printf("\n");

	//Printing Postorder Traversal
	printf("Postorder Traversal: ");
        printPostorder(root);
        printf("\n");

	//Printing the Binary Tree
	printf("\nMinimum Height BST\n");
	sort(array, size);
	root = createMinBST(array, array[0], array[size-1]);
	printTree(root);

	fclose(input);
	free(root);

	return 0;
}


//Creates a BST based on the sorted array
bst* createBST(int a[], int size)
{
	bst* r = NULL;

	int i;
	for(i=0; i<size; i++)
		r = insert(r, a[i]);

	return r;
}


//Sorts the numbers in the array using selection sort
void sort(int a[], int size)
{
	int left, right, i, temp;
	for(left = 0; left < size; left++)
	{
		right = left;
		for(i=left; i<size; i++)
		{
			if(a[i] <a[right])
				right = i;
		}

		temp = a[left];
		a[left] = a[right];
		a[right] = temp;
	}
}

//Creates a BST with minimum height
bst* createMinBST(int a[], int start, int end)
{
	if(start > end)
		return NULL;

	int middle = (start+end)/2;
	bst* r = create_node(middle);

	r->left = createMinBST(a, start, middle - 1);
	r->right = createMinBST(a, middle + 1, end);

	return r;
}
