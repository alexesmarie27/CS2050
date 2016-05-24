#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
	int value;
	struct node_* next;
}node;

//Prototypes
node* insert(node* head, int value);
void print(node* head);

int main()
{
	int value;
	node* head;

	//Collects and stores value
	printf("?:");
	scanf("%d", &value);
	
	while(value != -1)
	{
		head = insert(head, value);
		print(head);

		printf("?:");
                scanf("%d", &value);
	}

	return 0;
}

node* insert(node* head, int value)
{
	node* current;
	node* newptr;
	node* prevptr;

	newptr = malloc(sizeof(node));
	if(newptr != NULL)
	{
		newptr->value = value;
		current = head;
		prevptr = NULL;
		newptr->next = NULL;

		while(current != NULL && value > current->value)
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
	{
		printf("%d not inserted. No memory available.\n", value);
	}
 	
	return head;
}

void print(node* head)
{
	node* current;
	current = malloc(sizeof(node));
	current = head;

	printf("\n");

	while(current != NULL)
	{
		printf("%d", current->value);
		current = current->next;

		if(current != NULL)
		{
			printf("->");
		}
	}

	printf("-> NULL");

	printf("\n");
}
