#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*This is needed in order to for us to use our functions located in algorithm.c
as well as our structures. Make sure you understand what this header file is here
for and why we include it outside of our driver.c file*/
#include "header.h"

/********************************** MAIN *****************************************

 parameters: int argc (total number of command line arguments.
             char*argv[] (an array that holds the command line arguments)
 returns: int value of success (0) or failure (1)

 -> Your main function should read two files from the command line:
    1.) argv[1] should read the file input.txt. This file will have
        integer values that you will use to insert into the binary search tree.
        -1 values indicate the end of the list for the current binary search tree.
        DO NOT INSERT -1 IN THE binary search treeS.

    2.) argv[2] should read the file search.txt. This file will have
        integer values that you will use to search the binary search tree using BFS
 -> Main will call the functions: insert_BST, insert_rootList and BFS.

*********************************************************************************/

int main (int argc, char*argv[]){

	//If there are not enough command line arguments
	if(argc != 3)
	{
		printf("Not enough command line arguments. Exiting program...\n");
		return 1;
	}

	//Opens the files for reading
	FILE* input = fopen(argv[1], "r");
	FILE* search = fopen(argv[2], "r");

	//If the files DNE
	if(input == NULL || search == NULL)
	{
		printf("Not all files exist. Exiting program...\n");
		return 1;
	}

	BST* root = NULL;
	rootList* head = NULL;


	//Inserts values into the BST
	int insertValue, treeNum = 1;
	while(fscanf(input, "%d", &insertValue) != EOF)
	{
		if(insertValue == -1)
		{
			++treeNum;
			insert_rootList(&head, root);
			root = NULL;
		}
		else
		{
			insert_BST(&root, insertValue, treeNum);
		}

	}

	printTrees(head);

	//Prints out the trees and searches for values within the trees
	//Calls the free functions
	int searchValue;
	printf("Number %-7s%-7s%-7s\n", "Found", "Tree", "Level");
	while(fscanf(search, "%d", &searchValue) != EOF)
	{
		BFS(head, searchValue);
	}

	//Closes files
	fclose(input);
	fclose(search);

	//Calls the free functions
	free_list(&head);

    return 0;
}
