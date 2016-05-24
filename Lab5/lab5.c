#include <stdlib.h>
#include <stdio.h>

//Prototypes
void merge_sort(int array[], int low, int high);
void merge(int array[], int low, int middle, int high);
void print(int array[], int length);
int is_sorted(int array[], int length);
int binary_search(int array[], int key, int low, int high);

int main(int argc, char* argv[])
{
	//Converts user's key from a char to an int
	int key = atoi(argv[1]);

	//Opens input file for reading
	FILE* input = fopen(argv[2], "r");

	//collects length of file
	int len;
	fscanf(input, "%d", &len);

	//Scans ints from file into int array
	//int list[len];
	int * list = malloc(sizeof(int) * len);
	int i;
	for(i=0; i<len; i++)
	{
		fscanf(input, "%d", &list[i]);
	}

	//Checks if array is sorted
	int result = is_sorted(list, len);
	//Return 1 if array is sorted
	if(result == 1)
		printf("The array is sorted\n");
	//Return 0 if array is not sorted
	else
		printf("The array is not sorted\n");

	//Sorts the array
	printf("Calling mergesort\n");
	merge_sort(list, 0, len-1);

	//Recalls is_sorted to check if mergesort worked correctly
	result = is_sorted(list, len);
	//return 1 if the array is sorted
	if(result == 1)
		printf("The array is sorted\n");
	//return 0 if the array is not sorted
	else
		printf("The array is not sorted\n");

	//Searches for key within array
	int findInt = binary_search(list, key, 0, len-1);
	//If key was found in the array, return 1. Else, return 0
	if(findInt == 1)
		printf("%d was found in the array\n", key);
	else
		printf("%d was not found in the array\n", key);

	//Prints the sorted array
	print(list, len);

	//Closes input file
	fclose(input);

	return 0;
}

//Checks if the array is sorted
int is_sorted(int array[], int length)
{
	int i;
	for(i=0; i<length; i++)
	{
		//If the array is not sorted, return 1
		if(array[i] > array[i+1])
			return 0;
	}

	//Returns 1 if array is sorted
	return 1;
}

//Searches for an int within the int array
int binary_search(int array[], int key, int low, int high)
{
	int middle;

	while(low <= high)
	{
		//Finds the middle int
		middle = (low+high)/2;
		//If the key equals the middle, return middle
		if(key == array[middle])
			return middle;
		//If key is less than middle, move into lower half of array
		else if(key < array[middle])
			high = middle - 1;
		//If key is greater than middle, move into upper half of array
		else
			low = middle + 1;
		//Returns 0 if not found
		return 0;
	}
}

//Prints the int array
void print(int array[], int length)
{
	//Header
	printf("\nThe sorted array\n");

	//Runs through list and prints the int at each index
	int i;
	for(i=0; i<length; i++)
	{
		printf("%d\n", array[i]);
	}
}

//Sorts elements within an int array based on mergesort
void merge_sort(int array[], int low, int high)
{
	if(low < high){
		//Finds the middle
		int middle = (low+high)/2;

		//Sorts lower half
		merge_sort(array, low, middle);

		//Sorts upper half
		merge_sort(array, middle+1, high);

		//Merges halves together
		merge(array, low, middle, high);
	}
}

//Merges two sorted arrays into one
void merge(int array[], int low, int middle, int high)
{
	//int helper[(high-low)+1];
	int * helper = malloc(sizeof(int) * (high - low + 1));
	int i;
	for(i=0; i<((high-low)+1); i++)
	{
		helper[i] = array[i + low];
	}

	int j, k, q = 0;
	//Lowest index in bottom half of array
	j = low;
	//Lowest index in upper half of array
	k = middle + 1;
	while(j <= middle  && k <= high)
	{
		if(array[j] < array[k])
			helper[q++] = array[j++];
		else
			helper[q++] = array[k++];
	}
	while( j <= middle ) helper[q++] = array[j++];
	while( k <= high ) helper[q++] = array[k++];
	int f;
	for(f=0; f <((high-low)+1); f++)
	{
		array[f+low] = helper[f];
	}
}
