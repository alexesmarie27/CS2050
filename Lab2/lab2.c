#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20

typedef struct node_{
	char* name;
	struct node_* next;
}node;

//Prototypes
node* insert(node* head, char* name);
node* create_node(char* name);
void print(node* head);
void delete(node* head);

int main(int argc, char* argv[])
{
	//If there are not enough command arguments
	if(argc != 2)
	{
		printf("Incorrect Number of Command Line Arguments\nCorrect Usage ./a.out <input file>\n");
		return 1;
	}

	//Opens input file to be read
	FILE* input = fopen(argv[1], "r");

	//If file does not exist
	if(input == NULL)
	{
		printf("Unable to open file %s\n", argv[1]);
		return 1;
	}

	node* head = NULL;
	char name[MAX_NAME_LEN];

	while(fgets(name, MAX_NAME_LEN, input) != NULL)
	{
		head = insert(head, name);
	}

	fclose(input);

	print(head);

	delete(head);

	return 0;
}

//Inserts node at the end of the linked list
node* insert(node* head, char* name)
{
	node* newnode = create_node(name);
	node* new_ptr = head;

	//Starts new pointer at beginning of linked list
	if(head == NULL)
		return newnode;

	//While the pointer is not pointing at end of linked list
	while(new_ptr->next != NULL)
	{
		//Move to next node
		new_ptr = new_ptr->next;
	}

	//Places new node at end of linked list
	new_ptr->next = newnode;
	return head;
}

//Allocates memory for node
node* create_node(char* name)
{
	node* new_node;

	//Allocates memory for node
	new_node =(node*) malloc(sizeof(node));
	new_node->name = malloc(20 * sizeof(char));

	//Name is placed within node
	strcpy(new_node->name, name);

	//Next pointer is set to NULL
	new_node->next = NULL;

	return new_node;
}

//Prints the linked list
void print(node* head)
{
	node* current;
	current = head;

	//While not at the end of the linked list
	while(current != NULL)
	{
		printf("%s -> ", current->name);
		current = current->next;
	}

	printf("NULL\n");
}

void delete(node* head)
{
	node* current;

	//Starts at the beginning
	current = head;

	//While not at the end of the linked list
	while(current != NULL)
	{
		node* pointer = current->next;
		free(current);
		current = pointer;
	}

}
