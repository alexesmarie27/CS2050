#include <stdlib.h>
#include "stack.h"

/*
 * Creates an empty stack and sets
 * the size equal to 0
 */

stack* create_stack()
{
	stack* newstack = malloc(sizeof(stack));

	newstack->size = 0;
	newstack->stack = NULL;

	return newstack;
}

/*
 * pushes the value into the top of the stack
 */
void push(stack *s, int val)
{
	node *n = malloc(sizeof(node));
    n->data = val;
    n->next = s->stack;
    s->stack = n;
    s->size++;
}

/*
 * pops the head of the stack
 * the value is not returned
 */
void pop(stack *s)
{
	//if stack is empty, return
	if(s->size == 0)
		return;

	node* current = s->stack;
	s->stack = current->next;
	free(current);

	--s->size;
}


/*
 * returns the value at the top of the stack
 * the stack remains unchanged
 */
int top(stack *s)
{
	if(s->size == 0)
		return 0;

	node* current = s->stack;
	return current->data;
}

/*
 * returns 1 if the stack is empty
 * 0 otherwise
 */
int isEmpty(stack *s)
{
	if (s->size == 0)
		return 1;

	else
		return 0;
}
