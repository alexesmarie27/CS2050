#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
	int value;
	struct node_* next;
}node;

//Prototypes
node* insert_top(node* head, int value);
node* delete(node* head, int value);
void print(node* head);

int main()
{
	node* head = NULL;
	//head = malloc(sizeof(node));

	//Prompts insert 5 times and prints linked list
	int value, i;
	for(i=0; i<5; i++)
	{
		printf("insert: ");
		scanf("%d", &value);
		head = insert_top(head, value);
		print(head);
	}

	//Prompts delete 3 times and prints linked list
	int j, delvalue;
	for(j=0; j<3; j++)
	{
		printf("delete: ");
		scanf("%d", &delvalue);
		head = delete(head, delvalue);
		print(head);
	}

	return 0;
}

//Inserts new node at the beginning of linked list
node* insert_top(node* head, int value)
{
	node* newnode = malloc(sizeof(node));
	
	//Value of node is placed
	newnode->value = value;

	newnode->next = NULL;

	
	//If at the beginning of the empty linked list, place node in front
	if(head == NULL)
	{
		head = newnode;
		
		return head;
	}
	//Else, place node at the beginning of filled linked list
	else

	{
		newnode->next = head;
		
		return newnode;
	}
}


//Deletes node from linked list
node* delete(node* head, int value)
{
	node* current;
	node* previous = NULL;
	node* pointer = NULL;

	//Starts at the beginning of the linked list
	current = head;

	//If value is at the front of the linked list
	while(current->value == value)
	{
		pointer = current->next;
		free(current);
		current = pointer;
		head = current;
	}

	//If value is in the middle or the end of the linked list
	while(current->next != NULL)
	{
		previous = current;
		current = current->next;

		//if the node's value is the same as the entered value
		if(current->value == value)
		{
			previous->next = current->next;
			//delete node's value
			free(current);
			current = previous->next;
		}
	}

	return head;
}

//Prints off the linked list
void print(node* head)
{
	node* current;
	current = head;

	//While not at the end of the linked list
	while(current != NULL)
	{
		//Prints the value and then moves to next node
		printf("%d -> ", current->value);
		current = current->next;
	}

	//At the end, prints off NULL
	printf("NULL\n");
}
