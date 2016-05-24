#include <stdio.h>
#include <string.h>
#include "parser.h"

int is_phone_number(char* word)
{
	//If number length is not 14, invalid
	 if(strlen(word) != 14)
                return 0;

	//If no parentheses, invalid
	 else if(word[0] != '(' && word[4] != ')')
                return 0;

	//If area code is not three numbers, invalid
	else if(word[1] < 48 || word[1] > 57)
                return 0;
        else if(word[2] < 48 || word[2] > 57)
                return 0;
        else if(word[3] < 48 || word[3] > 57)
                return 0;

	//If dashes not in correct place, invalid
	else if(word[5] != '-' && word[9] != '-')
                return 0;

	//Checks three middle numbers
	else if(word[6] < 48 || word[6] > 57)
                return 0;
        else if(word[7] < 48 || word[7] > 57)
                return 0;
        else if(word[8] < 48 || word[1] > 57)
                return 0;

	 //Checks last four numbers
	 else if(word[10] < 48 || word[10] > 57)
                return 0;
        else if(word[11] < 48 || word[11] > 57)
                return 0;
        else if(word[12] < 48 || word[12] > 57)
                return 0;
        else if(word[13] < 48 || word[13] > 57)
                return 0;

	 //If everything is correct, returns 1
	  else
                return 1;
}

/*
int is_date(char* word)
{
        if(word[0] != 48 || word[0] != 49)
        {
                if(word[1] != 48 || word[1] != 49)
                        return 0;
        }

        if(word[2] != '/' || word[5] != '/')
                return 0;

	if(word[3] == '0' && word[4] == '2')
	{
		if(word

        1 3 5 7 8 10 12

        2 4 6 9 11
}
*/

int looks_like_name(const char* word)
{
	 //Finds name length
	 int length = strlen(word);

	//ASCII table = 65-90 are uppercase letters
	//Checks for capital letter
	if(word[0] <65 || word[0] > 90)
                        return 0;

	 //Goes through rest of name
	  int i;
        for(i=1; i<length; i++)
        {
		 //ASCII table = 97-122 are lowercase letters
		 //If all the rest of the letters are not lowercase
		 if(word[i] < 97 || word[i] > 122)
                        return 0;

	}

	//If it is a name, return 1
	return 1;
}

int is_email(char* word)
{
	//length of email
	int length = strlen(word);

	//Used ASCII table
	//Checks letters before the '@'
	 int i, j=0;
        for(i=0; i<length; i++)
        {
                if(word[i] == '@')
                {
                        j=i;
                        break;
                }

                if(word[i] < 48)
                        return 0;

                if(word[i] > 57 && word[i] <65)
                        return 0;

                if(word[i] < 90)
                        return 0;
        }

	//Used ASCII table
	//checks letters after the '@'
	 int k;
        for(k=j+1; k<length; k++)
        {
		 //Stops at the period
		if(word[k] == '.')
                        break;

                if(word[k] < 48)
                        return 0;

                if(word[k] > 57 && word[k] <65)
                        return 0;

                if(word[k] < 90)
                        return 0;
        }

	//If last three letters are not "com"
	if(word[length-3] != 'c')
		return 0;
       	if(word[length-2] != 'o')
		return 0;
        if(word[length-1] != 'm')
        	return 0;



	//If it is an email, return 1
	else
                return 1;
}
