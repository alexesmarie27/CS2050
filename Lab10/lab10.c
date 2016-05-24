#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 250

//Prototypes
int is_phone_number(char* word);
int is_date(char* word);
int looks_like_name(const char* word);
int is_email(char* word);

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
