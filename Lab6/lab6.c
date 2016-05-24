#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct node{
	int number;
	struct node* next;
}Node;

//Prototypes
int linearSearch(int array[], int length, int key);
int nodeSearch(Node* head, int key);
void free_Nodes(Node* head);
Node* insert_end(Node* head, int data);

int main(int argc, char** argv)
{
	//Converts the key into an integer
	int key = atoi(argv[1]);

	//Opens input file for reading
	FILE* input = fopen(argv[2], "r");

	//Finds length of input file
	int length;
	fscanf(input, "%d", &length);

	//Scans input file and places information into an int array
	int i;
	int array[length];
	for(i=0; i<length; i++)
	{
		fscanf(input, "%d", &array[i]);
	}

	struct timeval t1, t2, t3;
        gettimeofday(&t1, NULL);

	//Searches for the key in the array
	int foundLin = linearSearch(array, length, key);

	gettimeofday(&t2, NULL);
	timersub(&t2, &t1, &t3);
	printf("Linear search array of size 10000\n");
	printf("%lu", t3.tv_usec);

	Node* head = NULL;

	//Places integers from input file into a linked list
	for(i=0; i<length; i++)
	{
		int data = array[i];
		head = insert_end(head, data);
	}

	struct timeval t4, t5, t6;
        gettimeofday(&t4, NULL);

	//Searches for the key in the linked list
	int foundNode = nodeSearch(head, key);

	gettimeofday(&t5, NULL);
        timersub(&t5, &t4, &t6);
	printf("\n\nL search on linked list of size 10000\n");
        printf("%lu\n", t6.tv_usec);

	fclose(input);

	return 0;
}

//Searches array for specific number, or key
int linearSearch(int array[], int length, int key)
{
	int i;
	for(i=0; i<length; i++)
	{
		//returns 1 if key is found
		if(array[i] == key)
			return 1;
	}

	//returns 0 if key is not found
	return 0;
}

//Searches linked list for specific number, or key
int nodeSearch(Node* head, int key)
{
	Node* current;
	current = head;

	while(current != NULL)
	{
		//if key is found, returns 1
		if(current->number == key)
			return 1;
		else
		{
			current = current->next;
		}
	}

	//returns 0 if key is not found
	return 0;
}

//Frees the nodes from a linked list
void free_Nodes(Node* head)
{
	Node* current = head;
	Node* temp;

	while(current != NULL)
	{
		temp  = current;
		current = current->next;
		free(temp);
	}
}

//Inserts data into the end of the linked list
Node* insert_end(Node* head, int data)
{ if(head==NULL){
	Node* newnode = malloc(sizeof(Node));
	newnode->number = data;

	//If head is null, make newnode the head
//	if(head==NULL)
//	{
		newnode->next = NULL;
		return newnode;
	}
	//else, move to the end of the list and insert the node at the end
	else
	{
		head->next = insert_end(head->next, data);
		return head;
	}
 }
