#include <stdio.h>

//Prototypes
void quick_sort(int* arr, int start, int end);
int partition(int* arr, int start, int end);

int main(int argc, char** argv)
{
	//Opens file
	FILE* input = fopen(argv[1], "r");
	
	//Finds length of file
	int length;
	fscanf(input, "%d", &length);
	
	//Inserts integers from file into array
	int array[length];
	int j;
	for(j=0; j<length; j++)
	{
		fscanf(input, "%d", &array[j]);
	}
	
	quick_sort(array, 0, length - 1);
		
	//Prints out sorted array
	int i;
	for(i=0; i<length; i++)
	{
		printf("%d  ", array[i]);
	}
	
	//Closes input file
	fclose(input);
}

//Sorts the array using quick sort
void quick_sort(int* arr, int start, int end)
{
	if(start < end)
	{
		int pivot = partition(arr, start, end);
		quick_sort(arr, start, pivot-1);
		quick_sort(arr, pivot+1, end);
	}
}

int partition(int* arr, int start, int end)
{
	int pVal, i, pPos, temp;
	pVal = arr[start];
	i = start;
	pPos = end+1;
	while(1)
	{
		do ++i; while(arr[i] <= pVal && i <= end);
		do --pPos; while(arr[pPos] > pVal);
		
		if(i >= pPos)
			break;
		
		temp = arr[i];
		arr[i] = arr[pPos];
		arr[pPos] = temp;
	}
	
	temp = arr[start];
	arr[start] = arr[pPos];
	arr[pPos] = temp;
	
	return pPos;
}
