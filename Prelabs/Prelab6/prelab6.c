//Prelab 6

#include <stdio.h>
#include <stdlib.h>

//Linked list
typedef struct node{
	int number;
	struct node* next;
}Node;

int main()
{
	srand(time(NULL));

	//Creates an array of size 10 and fills it with 10 random numbers
	int i;
	int array[10] = {0};
	for(i=0; i<10; i++)
	{
		array[i] = rand() % 10 + 1;
		printf("%d\n", array[i]);
	}

	//Creates an empty linked list and fills the list with 10 random numbers
	int j;
	Node* head = NULL;
	for(j=0; j<10; j++)
	{
		Node* newnode = malloc(sizeof(Node));
		newnode->number = rand() % 10 + 1;
		if(head==NULL)
		{
			head = newnode;
			newnode->next = NULL;
		}
		else
		{
			head->next = newnode;
			newnode->next = NULL;
		}
	}

	//Prints the linked list
	printf("Linked list:\n");
	Node* current = head;
	while(current != NULL)
	{
		printf("%d\n", current->number);
		current = current->next;
	}

	return 0;
}
