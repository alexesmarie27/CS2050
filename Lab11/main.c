#include <stdio.h>
#include <time.h>
#include "header.h"

int main(int argc, char** argv)
{
	FILE* input = fopen(argv[1], "r");
	FILE* searchf = fopen(argv[2], "r");

	//If files DNE
	if(input == NULL)
	{
		printf("Not all files exist!\n");
	}

	//If not enough files are entered
	if(argc != 3)
	{
		printf("Not enough command line arguments!\n");
	}

	//Determines length
	int length;
	fscanf(input, "%d", &length);

	//Puts numbers into array
	int i;
	int array[length];
	for(i=0; i<length; i++)
	{
		fscanf(input, "%d", &array[i]);
	}

	//Prompts option
	int option;
	printf("Do you want to sort with smaller values on the left(1) or on the right(2)?\n");
	scanf("%d", &option);

	//If neither option is chosen, prompt for new option
	while(option != 1 && option != 2)
	{
		printf("Please enter 1 for smaller values on left or 2 for smaller values on right:\n");
		scanf("%d", &option);
	}

	//If smaller values are on the left
	if(option == 1)
	{
		//Sorts the array
		quick_sort(array, 0, length-1, compareSmallerOnLeft);

		//Prints the array
		print(array, length);

		//Searches through the array
		int found, searchNum;
		while(fscanf(searchf, "%d", &searchNum) != EOF)
		{
			found = b_search(array, searchNum, compareSmallerOnLeft, 0, length-1);
			if(found == 0)
				printf("%d was found in the array!\n", searchNum);
			else
				printf("%d was not found in the array.\n", searchNum);
		}
	}

	//If smaller values are on the left
	if(option == 2)
	{
		//Sorts the array
		quick_sort(array, 0, length-1, compareSmallerOnRight);

		//Prints the array
		print(array, length);

		//Searches through the array
		int found, searchNum;
                while(fscanf(searchf, "%d", &searchNum) != EOF)
                {
                        found = b_search(array, searchNum, compareSmallerOnRight, 0, length-1);
                        if(found == 0)
                                printf("%d was found in the array!\n", searchNum);
                        else
                                printf("%d was not found in the array.\n", searchNum);
                }
	}

	fclose(input);
	fclose(searchf);

	return 0;
}
