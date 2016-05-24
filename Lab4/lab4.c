#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int value;
	struct node* next;
}Node;

//Prototypes
Node* insert_end(Node* head, int data);
void print_list(Node* head);
int search(Node* head, int data);
void factorial_list(Node* head);
void delete_list(Node* head);
int factorial(int n);


int main(int argc, char* argv[])
{
	//If there are not enough arguments
	if(argc != 2)
	{
		printf("Incorrect number of command line arguments, please try again!\n");
		return 1;
	}

	//Opens input file to be read
	FILE* input = fopen(argv[1], "r");

	//If file does not exist
	if(input == NULL)
	{
		printf("Unable to open file!\n");
		return 1;
	}

	Node* head = NULL;

	int value;
	//Scans for values in file
	while(fscanf(input, "%d", &value)!=EOF)
	{
		//Places value at the end of linked list
		head = insert_end(head, value);
	}

	//Prints the linked list
	print_list(head);

	//Prompts user for value to be searched and reports if found or not
	int find;
	printf("Please enter a number to search for: ");
	scanf("%d", &find);
	int found = search(head, find);
	if(found == 1)//If value was found
		printf("%d was found!\n", find);
	else//If value was not found
		printf("%d was NOT found!\n", find);

	//Replaces each value in list with its factorial
	factorial_list(head);

	//Prints out the updated list
	print_list(head);

	//Deletes all the nodes from the list
	delete_list(head);

	fclose(input);
}

//Inserts node into back of linked list
Node* insert_end(Node* head, int data)
{
	Node* newnode = malloc(sizeof(Node));

        newnode->value = data;

	if(head==NULL)
	{
		Node* newnode = malloc(sizeof(Node));

	        newnode->value = data;

		newnode->next = NULL;

		return newnode;
	}
	else
	{
		head->next = insert_end(head->next, data);

		return head;
	}
}

//Prints contents of the linked list
void print_list(Node* head)
{
	Node* current;
	current = head;

	if(current != NULL)
	{
		printf("%d -> ", current->value);
		current = current->next;
		print_list(current);
	}
      else
	printf("NULL\n");
}


//Searches linked list for value
int search(Node* head, int data)
{
	Node* current;
	current = head;

	if(current != NULL)
	{
		if(current->value == data)
			return 1;
		else
		{
			current = current->next;
			return search(current, data);

		}
	}
}

//Replaces value of node with its factorial
void factorial_list(Node* head)
{
	Node* current;
	current = head;

	if(current != NULL)
	{
		int value = current->value;
		current->value = factorial(value);
		current = current->next;
		factorial_list(current);
	}
}

//Deletes each node in the linked list
void delete_list(Node* head)
{
	Node* current;
	current = head;

	if(current != NULL)
	{
		delete_list(current->next);

		free(current);
	}
}

//Finds the factorial for each value
int factorial(int n)
{
	if(n <= 1)
		return 1;
	else
		return (n * factorial(n-1));
}
