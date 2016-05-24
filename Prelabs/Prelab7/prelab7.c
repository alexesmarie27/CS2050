#include <stdio.h>
#include <stdlib.h>

//linked list
typedef struct node_{
	char data;
	struct node_* next;
}node;

//Stack
typedef struct stack_{
	unsigned int size;
	node* stack;
}stack;

//Prototypes
stack* create_stack();
void push(stack* s, char val);
char top(stack* s);
void pop(stack* s);

int main()
{
	stack* stack;
	stack = create_stack();
	
	char data, data2;
	printf("Please enter a char: ");
	scanf("%c", &data);	

	push(stack, data);

	printf("Please enter a char: ");
        scanf("%c", &data2);

	push(stack, data2);

	char answer;
	answer = top(stack);
	printf("The top of the stack's data is %c\n", answer);

	pop(stack);
	answer = top(stack);
	printf("The top of the stack's data is %c\n", answer);
	
	return 0;
}

//returns a pointer to an empty stack
stack* create_stack()
{
	stack* newstack = malloc(sizeof(stack));

	newstack->size = 0;
	newstack->stack = NULL;

	return newstack;
}

//inserts a new element at the top of the stack
void push(stack* s, char val)
{
	node* newnode = malloc(sizeof(node));
	newnode->data = val;
	newnode->next = s->stack;
	s->stack = newnode;
	++s->size;
}

//returns value stored at top of stack
char top(stack* s)
{
	node* current;
	current = s->stack;
	return current->data;
}

//removes element at top of stack
void pop(stack* s)
{
	node* current;
	s->stack = current->next;
	free(current);
	--s->size;
}
