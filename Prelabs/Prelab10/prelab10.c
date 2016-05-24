#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 250

int is_phone_number(char* string);

int main(int argc, char** argv)
{
	FILE* input = fopen(argv[1], "r");
	
	char string[50];
	char* token;
	while(fgets(string, MAX_LINE, input))
	{
		if(string[strlen(string)-1] == '\n')
			string[strlen(string)-1] == '\0';
			
		token = strtok(string, " \n\r\t");
		
		while(token != NULL)
		{
			int result = is_phone_number(token);
			
			if(result == 1)
				printf("Phone number: %s\n", token);
			
			token = strtok(NULL, " \n\r\t");
		}
	}
	
	return 0;
}

int is_phone_number(char* string)
{
	if(strlen(string) != 14)
		return 0;
	else if(string[0] != '(')
		return 0;
	else if(string[1] < 48 || string[1] > 57)
		return 0;
	else if(string[2] < 48 || string[2] > 57)
		return 0;
	else if(string[3] < 48 || string[3] > 57)
		return 0;
	else if(string[4] != ')')
		return 0;
	else if(string[5] != '-')
		return 0;
	else if(string[6] < 48 || string[6] > 57)
		return 0;
	else if(string[7] < 48 || string[7] > 57)
		return 0;
	else if(string[8] < 48 || string[1] > 57)
		return 0;
	else if(string[9] != '-')
		return 0;
	else if(string[10] < 48 || string[10] > 57)
		return 0;
	else if(string[11] < 48 || string[11] > 57)
		return 0;
	else if(string[12] < 48 || string[12] > 57)
		return 0;
	else if(string[13] < 48 || string[13] > 57)
		return 0;
	else
		return 1;
}
	
