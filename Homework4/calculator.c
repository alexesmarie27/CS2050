#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

#define MAX_EQU_LEN 100

/*
 * Returns a number corresponding the the preccedence
 * of different arithmetic operators. * has a higher
 * precedence that / which is greater than %, +, -
 * in that order. Higher precedence should return a higher
 * number so say 5 for * 1 for - and 0 for a non operator
 */
static char prec(char operator)
{
	if(operator == '*')
		return 5;
	if(operator == '/')
		return 4;
	if(operator == '%')
		return 3;
	if(operator == '+')
		return 2;
	if(operator == '-')
		return 1;
	else
		return 0;
}

/*
 * Returns 1 if the string passed is an inteter
 * 0 otherwise
 */
static int isNumeric(char *num)
{
	int length;
	length = strlen(num);

	int i;
	for(i=0; i<length; i++)
	{
		if(!isdigit(num[i]))
			return 0;
	}

	return 1;
}

/*
 * converts a valid infix expression into postfix
 * Hint put a space between numbers and operators
 * so you can use strtok in evaluate_postfix
 * ex: get 7 8 + vs 78+
 *
 * This is done with the following algorithm
 *
 * for each token in the string
 *     if the next token is a number
 *         append it to the postfix string
 *     else if the next token is a left paren
 *          push it onto the stack
 *     else if the next token is a right paren
 *          while the stack is not empty and the left paren is not at the top of the stack
 *              pop the next operator off of the stack
 *              append it to the postfix string
 *          pop the left paren off of the stack and discard it
 *     else if the next token is an operator (+, -, *, /)
 *         while the stack is not empty and the operator at the top of the stack has a higher precedence than the token
 *              pop the top element off of the stack and append it to the postfix string
 *         push the current token onto the stack
 *
 * while there are elements remaining on the stack
 *     pop the top element off of the stack and append it to the postfix string
 */
char* infix_to_postfix(char* infix)
{
	//Finds length of string
	int length = strlen(infix);

	//Creates a stack
	stack* s = create_stack();

	//Postfix String
	char* postfix= malloc(sizeof(char)*MAX_EQU_LEN);
	int i;
	for(i=0; i<length; i++)
	{
		postfix[i] = 'x';
	}

	//Goes through infix array
	int counter;
	for(counter=0; counter < length; counter++)
	{
		char token = infix[counter];

		//If token is a number
		if(isdigit(token))
		{
			//Moves to next available index in array
			char* temp = postfix;
			while(*temp != 'x')
			{
				temp++;
			}

			*temp = token;
		}

		//If token is left parentheses
		else if(token == '(')
		{
			push(s, token);
		}

		//If token is right parentheses
		else if(token == ')')
		{
			//While stack is not 0 and top of stack is not left parentheses
			while(!isEmpty(s) && top(s) != '(')
			{
				int topVal = top(s);
				pop(s);

				//Moves to next available index in array
				char* temp = postfix;
				while(*temp != 'x')
				{
					temp++;
				}

				*temp = topVal;
			}

			pop(s);
		}

		//If the token is an operation
		else if(prec(token))
		{
			int temp = prec((char) top(s));
			int temp2 = prec(token);
			while(!isEmpty(s) && temp > temp2)
			{
				int topstack = top(s);
				pop(s);

				//Moves through postfix array
				char* pointer = postfix;
				while(*pointer != 'x')
				{
					pointer++;
				}

				*pointer = topstack;
			}

			push(s, token);

		}

	}

	//If stack is not empty, append to postfix string
	while(!isEmpty(s))
	{
		int topstack = top(s);

		pop(s);
		char* pointer = postfix;
		while(*pointer != 'x')
		{
			pointer++;
		}

		*pointer = topstack;
	}

	//Adds null terminator to end of postfix string
	char* pointer = postfix;
	while(*pointer != 'x')
	{
		pointer++;
	}

	*pointer = '\0';

	return postfix;
}

/*
 * This function takes in a valid postfix expression
 * and evaluate it to an integer
 *
 * for each token in the string
 *      if the token is numeric
 *          convert it to an integer
 *          push it onto the stack
 *      else
 *          pop the top 2 element off of the stack
 *          the first goes into the right variable
 *          the second goes into the left variable
 *          apply the operation:
 *              result = left op right
 *              ex result = left + right
 *
 *          push the result onto the stack
 *
 * return the rsult from the stack
 */

int evaluate_postfix(char* postfix)
{
	//Creates a stack
	stack* s = create_stack();

	//Runs through postfix array
	int length = strlen(postfix);
	int counter, result;
	for(counter=0; counter < length; counter++)
	{
		//Sets token as element
		char token = postfix[counter];

		//If the element is a digit, push
		if(isdigit(token))
		{
			push(s, token - '0');
		}
		//Else, uses the stack to find result of function
		else
		{

				int right = top(s);
				pop(s);
				int left = top(s);
				pop(s);

				//Switches between different operations
				switch (token)
				{
					case '/':
						result = left / right;
						break;
					case '*':
						result = left * right;
						break;
					case '%':
						result = left % right;
						break;
					case '+':
						result = left+ right;
						break;
					case '-':
						result = left - right;
						break;
					default:
						break;
				}

				push(s, result);

		}
	}

	free(postfix);

	return top(s);
}
