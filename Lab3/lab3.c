#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
	int val;
	struct node_* next;
}node;

//Prototypes
node* insert(node* head, int value);
node* delete(node* head, int value);
void mul_even(node* head, int multiplier);
void print(node* head);

int main(int argc, char* argv[])
{
	//If there are not enough command line arguments
	if(argc != 2)
	{
		printf("Incorrect number of command line arguments\nCorrect Ussage ./a.out <input file>\n");
		return 1;
	}

	//Opens input file
	FILE* input = fopen(argv[1], "r");

	if(input == NULL)
	{
		printf("Unable to open file\n");
		return 1;
	}

	node* head = NULL;
	char temp[6] = {0};

	int linecount = 0;
	while(fgets(temp, 10, input) != NULL)
	{
		linecount++;
	}

	rewind(input);

	char option;
	int value;

	while(linecount != 0)
	{
		fscanf(input, "%c %d%*c", &option, &value);

		if(option == 'i')
		{
			head = insert(head, value);
			printf("Inserting %d into the list\n", value);
		}
		if(option == 'd')
		{
			head = delete(head, value);
			printf("Deleting %d from the list\n", value);
		}
		if(option == 'm')
		{
			mul_even(head, value);
			printf("Multiplying all even numbers by %d\n", value);
		}

		print(head);

		linecount--;
	}

	fclose(input);

	return 0;
}

//Inserts node either at the beginning or the end of the linked list
node* insert(node* head, int value)
{
	node* newnode = malloc(sizeof(node));

	newnode->val = value;

	//If the value is even, place into head
	if(value % 2 == 0)
	{
        	newnode->next = head;

		return newnode;
	}
	//If the value is odd, place at end
	else
	{
		if(head == NULL)
			return newnode;

		node* pointer = head;
		while(pointer->next != NULL)
		{
			pointer = pointer->next;
		}

		pointer->next = newnode;

		newnode->next = NULL;

		return head;
	}
}

//Deletes node(s) from the linked list
node* delete(node* head, int value)
{
	node* current;
	node* previous = NULL;
	node* pointer = NULL;

	//Starts linked list at the beginning
	current = head;

	//If value is at the beginning of the linked list
	while(current->val == value)
	{
		pointer = current->next;
		free(current);
		current = pointer;
		head = current;
	}

	//While value is in the middle or end of the linked list
	while(current->next != NULL)
	{
		previous = current;
		current = current->next;

		if(current->val == value)
		{
			previous->next = current->next;
			free(current);
			current = previous->next;
		}
	}

	return head;
}

//Multiples all even numbers by multiplier
void mul_even(node* head, int multiplier)
{
	node* current;
	current = head;

	//While not at the end of the linked list
	while(current != NULL)
	{
		//If value is even
		if(current->val % 2 == 0)
		{
			current->val = (current->val * multiplier);
		}
		//Moves to next node of linked list
		current = current->next;
	}
}

//Prints linked list
void print(node* head)
{
	node* current;
	current = head;

	//While not at the end of the linked list
	while(current != NULL)
	{
		//Prints the value and then moves to next node
		printf("%d -> ", current->val);
		current = current->next;
	}

	//At the very end, prints a NULL
	printf("NULL\n");
}
