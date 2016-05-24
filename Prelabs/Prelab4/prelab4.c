#include <stdio.h>
#include <stdlib.h>


typedef struct node_{
        int number;
        struct node_* next;
}node;

//Prototypes
int factorial(int n);
node* insert(node* head, int value);
void print(node* head);


int main()
{
	//Creates empty linked list
	node* head = NULL;
	head = malloc(sizeof(node));

	//Value to be sent to factorial function
	int value = 0;
	while(value != -1)
	{
		//Prompts user for number and scans number into "Value"
		printf("?:");
		scanf("%d", &value);
		//Sends value to factorial function
		int fact = factorial(value);
		//Inserts factorial value into linked list
		head = insert(head, fact);
		//Prints linked list
		print(head);
	}//Ends while loop

	return 0;
}

int factorial(int n)
{
	if(n <= 1)
		return 1;
	else
		return (n * factorial(n-1));
}

node* insert(node* head, int value)
{
	node* current;
	node* newptr;
	node* prevptr;

	newptr = malloc(sizeof(node));

	if(newptr != NULL)
	{
		newptr->number = value;
		current = head;
		prevptr = NULL;
		newptr->next = NULL;

		while(current != NULL && value >current->number)
		{
			prevptr = current;
			current = current->next;
		}

		if(prevptr == NULL)
		{
			newptr->next = head;
			head = newptr;
		}
		else
		{
			prevptr->next = newptr;
			newptr->next = current;
		}
	}

	else
		printf("%d not inserted. No memory available.\n", value);

	return head;
}

void print(node* head)
{
	node* current;
	current = head;

	//While not at the end of the linked list
	while(current != NULL)
	{
		//Prints the value and moves to next node
		printf("%d -> ", current->number);
		current = current->next;
	}

	//At the end, print off NULL
	printf("NULL\n");
}
