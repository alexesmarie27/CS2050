#include <stdio.h>
#include <time.h>
#include "header.h"

int compareSmallerOnLeft(int num1, int num2)
{
	//If numbers are equal
	if(num1 == num2)
		return 0;
	//If num1 is greater
	if(num1 > num2)
		return -1;
	//If num1 is smaller
	if(num1 < num2)
		return 1;
}

int compareSmallerOnRight(int num1, int num2)
{
	//If numbers are equal
	if(num1 == num2)
		return 0;
	if(num1 > num2)
		return 1;
	if(num1 < num2)
		return -1;
}

//Sorts array with divide and conquer approach
void quick_sort(int* arr, int start, int end, int (*compare)(int, int))
{
	if(start<end)
	{
		int pivot = partition(arr, start, end, compare);
		quick_sort(arr, start, pivot - 1, compare);
		quick_sort(arr, pivot +1, end, compare);
	}
}

//Uses a pivot to sort the array into halves
int partition(int* arr, int start, int end, int (*compare)(int, int))
{
	srand(time(NULL));
	int pivotIdx, i, j, pivotPos, temp, temp2;

	//Finds a random pivot index
	pivotIdx = start + rand() % (end-start);
	temp2 = arr[start];
	arr[start] = arr[pivotIdx];
	arr[pivotIdx] = temp2;
	 pivotPos = arr[start];

	i = start + 1;
	j = end ;

	//If going in ascending order
	if(compare == compareSmallerOnLeft)
	{
		while(i < j)
		{

			//While smaller indexes are smaller than the pivot, move to next index
			if((compareSmallerOnLeft(arr[i], pivotPos) == 1 || compareSmallerOnLeft(arr[i], pivotPos) == 0) && i <= end)
			{
				i++;
			}

			//While larger indexes are larger than pivot value, move down the array
			if(compareSmallerOnLeft(arr[j], pivotPos) == -1)
			{
				j--;
			}
		}
	}

	//If going in descending order
	if(compare == compareSmallerOnRight)
	{
		while(i < j)
		{

			//While smaller indexes are larger than the pivot, move to next index
			if((compareSmallerOnRight(arr[i], pivotPos) == 1 || compareSmallerOnRight(arr[i], pivotPos) == 0) && i <= end)
			{
				i++;
			}

			//While larger indexes are smaller than pivot value, move down array
			if(compareSmallerOnRight(arr[j], pivotPos) == -1)
			{
				j--;
			}
		}
	}

	temp = arr[start];
        arr[start] = arr[j];
        arr[j] = temp;


	return pivotIdx;
}

//Uses binary search to search for specific data
int b_search(int* arr, int data, int (*compare)(int, int), int start, int end)
{
	if(compare == compareSmallerOnLeft)
	{
		while(start <= end)
		{
			int middle = (end+start)/2;
			if(compareSmallerOnLeft(data, arr[middle]) == 0)
				return 0;
			else if(data < arr[middle])
				end = middle - 1;
			else
				start = middle+1;

			return 1;
		}
	}

	if(compare == compareSmallerOnRight)
	{
		while(end <= start)
		{
			int middle = (start+end)/2;

			if(compareSmallerOnRight(data, arr[middle]))
				return 0;
			else if(data > arr[middle])
				start = middle -1;
			else
				end = middle+1;

			return 1;
		}
	}
}

//Prints out the sorted array
void print(int* arr, int length)
{
	int i;
	for(i=0; i<length; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
}
