#include <stdio.h>
#include <string.h>
#include "parser.h"

int main(int argc, char** argv)
{
        FILE* input = fopen(argv[1], "r");

        char buffer[MAX_LINE];
        char* token;
		int counter = 0;
        while(fgets(buffer, MAX_LINE, input))
        {
			if(buffer[strlen(buffer)-1] == '\n')
				buffer[strlen(buffer)-1] = '\0';

			token = strtok(buffer, " \n\r\t");

			while(token != NULL)
			{
				//Checks for phone number
				int isphone = is_phone_number(token);
                        if(isphone == 1)
                                printf("Phone number: %s\n", token);

				/*
				//Checks for date
				int isdate = is_date(token);
							if(isdate == 1)
									printf("Date: %s\n", token);
				*/

				//Checks for name
				int isname = looks_like_name(token);
                        if(isname == 1)
                        {
                                char* token2 = strtok(NULL, " \n\r\t");
                                int isname = looks_like_name(token2);
                                if(isname == 1)
                                        printf("Name: %s %s\n", token, token2);
				counter++;
                        }

			//Checks for email
			int ismail = is_email(token);
                        if(ismail == 1)
                                printf("Email: %s\n", token);

			counter++;
                        token = strtok(NULL, " \n\r\t");
                }
        }

	printf("There are %d words in the file\n", counter);

	fclose(input);

        return 0;
}
