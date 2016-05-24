#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_{
	char data;
	struct node_* next;
}node;

typedef struct stack_{
	unsigned int size;
	node* stack;
}stack;

#define MAX_EQU_LEN 100

//Prototypes
stack* create_stack();
void push(stack* s, char val);
char top(stack* s);
void pop(stack* s);
int paren_match(char* equation);
int paren_and_brackets_match(char* equation);

int main(int argc, char* argv[])
{
	//If there are not enough command line arguments
	if(argc != 2)
	{
		printf("Incorrect number of command line arguments\n");
		return 1;
	}

	//Opens the file for reading
	FILE* input = fopen(argv[1], "r");

	//If the file DNE
	if(input == NULL)
	{
		printf("Unable to open file\n");
		return 1;
	}

	char equation[MAX_EQU_LEN];

	//sends each equation into the parenmatch function and determines if equal parentheses
	while((fscanf(input, "%s", equation)) != EOF)
	{
		int match = paren_match(equation);
		int match2 = paren_and_brackets_match(equation);
		if(match == 1)
			printf("For equation %s; Parensmatch:", equation);
                if(match != 1)
        	        printf("For equation %s; Parens do not match:", equation);
		if(match2 == 1)
			printf(" Brackets match\n");
		if(match2 != 1)
			printf(" Brackets do not match\n");
	}

	return 0;
}

//creates an empty stack
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

//returns the value stored at the top of the stack
char top(stack* s)
{
	node* current = s->stack;
	return current->data;
}

//removed element from top of stack
void pop(stack* s)
{
	//if stack is empty, return
	if(s->size == 0)
		return;

	node* current = s->stack;
	s->stack = current->next;
	free(current);

	--s->size;
}

//checks if equation is balanced with parentheses
int paren_match(char* equation)
{
	//The stack is created
	stack* newstack = create_stack();

	int i;

	//puts parentheses in the stack, pops them if other parentheses is found
	for(i=0; i<MAX_EQU_LEN; i++)
	{
		if(equation[i] == '(')
			push(newstack, equation[i]);
		if(equation[i] == ')')
			pop(newstack);
	}

	//If stack is empty, it is balanced
	if (newstack->size == 0)
	{
		return 1;
	}
	//If stack is not empty, it is not balanced
	else
		return 0;
}

//checks if equation is balanced with parentheses and brackets
int paren_and_brackets_match(char* equation)
{
	stack* newstack = create_stack();

	int i;

	 //puts parentheses/brackets in the stack, pops them if other parentheses/brackets are found
	for(i=0; i<MAX_EQU_LEN; i++)
	{
		//if(equation[i] == '(')
                  //      push(newstack, equation[i]);
                //if(equation[i] == ')')
                //        pop(newstack);
		if(equation[i] =='[')
			push(newstack, equation[i]);
		if(equation[i] == ']')
			pop(newstack);
	}

	//If stack is empty, it is balanced
	if (newstack->size == 0)
        {
                return 1;
        }
	//If stack is not empty, it is not balanced
	else
                return 0;
}
