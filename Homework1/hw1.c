#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 20
#define CHAMP_LENGTH 20
#define TEAM_LENGTH 10

typedef struct player{
	char* name;
	char* champion;
	char* team;
	int kills;
	int deaths;
	struct player* next;
}Player;

//Prototypes
Player* new_player(char* name, char* champion, char* team, int kills, int deaths);
Player* insert_by_player(Player* head, Player* node);
void print_list(Player* head);
int update_records(Player* head, char* champion, char* champ_name, int kills, int deaths);
void free_node(Player* node);
Player* delete_player_even(Player* head);
Player* delete_player_odd(Player* head);
Player* reverse_list(Player* head);

int main(int argc, char** argv)
{
	//If not enough command line arguments
	if(argc != 2)
	{
		printf("Incorrect number of command line arguments\n");
		return 1;
	}

	//Opens input file
	FILE* input = fopen(argv[1], "r");

	//If input file does not exist
	if(input == NULL)
	{
		printf("Unable to open file\n");
		return 1;
	}

	Player* head = NULL;

	//Details for each new node in list
	Player* new = NULL;
	char* name = malloc(NAME_LENGTH * sizeof(char));
	char* champ = malloc(CHAMP_LENGTH * sizeof(char));
	char* team = malloc(TEAM_LENGTH	* sizeof(char));
	int kills, deaths;

	//While not at the end of file, place new info into node and sort in list
	do{
		fscanf(input, "%s %s %s %d %d\n", name, champ, team, &kills, &deaths);
		new = new_player(name, champ, team, kills, deaths);
		head = insert_by_player(head, new);
	} while(!feof(input));

	//Prints list
	print_list(head);

	//Information for champion to change
	char* champname = malloc(NAME_LENGTH * sizeof(char));
	int success, champkills, champdeaths;

	//Runs until list is updated with new champion
	do{
		printf("Enter a champion to change: ");
		scanf("%s", champ);
		printf("\nEnter new champion, kills, and deaths: ");
		scanf("%s %d %d", champname, &champkills, &champdeaths);
		success = update_records(head, champ, champname, champkills, champdeaths);
		if(success == 0)
			printf("Champion to change could not be found!\n\n");
	} while(success != 1);

	//Prints list with new champion
	print_list(head);

	//Deletes all players with an even KS ratio and prints list
	head = delete_player_even(head);
	print_list(head);

	//Reverses list and reprints it
	head = reverse_list(head);
	print_list(head);

	//Deletes all players with an odd KD ratio and prints list
	head = delete_player_odd(head);
	print_list(head);

	//Closes input file
	fclose(input);

	return 0;
}

//Creates new player
Player* new_player(char* name, char* champion, char* team, int kills, int deaths)
{
	//Creates memory for new player
	Player* newplayer = malloc(sizeof(Player));

	//Sets player's name
	newplayer->name = malloc(NAME_LENGTH * sizeof(char));
	strcpy(newplayer->name, name);

	//sets player's champion
	newplayer->champion = malloc(CHAMP_LENGTH * sizeof(char));
	strcpy(newplayer->champion, champion);

	//sets player's team
	newplayer->team = malloc(TEAM_LENGTH * sizeof(char));
	strcpy(newplayer->team, team);

	//sets player's kills
	newplayer->kills = kills;

	//sets player's deaths
	newplayer->deaths = deaths;

	//player's pointer set to null
	newplayer->next = NULL;

	//returns pointer to next node
	return newplayer;
}

//Inserts player alphabetically into linked list
Player* insert_by_player(Player* head, Player* node)
{


	//If linked list is empty, return new node as head
	if(head == NULL)
	{
		return node;
	}

	Player* previous = head;
        Player* current = head->next;

	//If new node is behind head alphabetically, move head one down the list
	if(strcmp(head->name, node->name) > 0)
	{
		node->next = head;
		return node;
	}

	//While not at the end of the linked list, check where new node belongs alphabetically
	while(previous != NULL)
	{

		//If names are in correct order, move to next node
		if(strcmp(current->name, node->name) < 0)
		{
			current = current->next;
			previous = previous->next;
		}
		//If names are not in correct order, switch names
		else
		{
			previous->next = node;
			node->next  = current;
			return head;
		}
	}

	return head;
}

//Prints linked list
void print_list(Player* head)
{
	Player* current;

	printf("\n");

	//If list is empty
	if(head == NULL)
	{
		printf("Player list is empty!\n");
		return;
	}

	//Header
	printf("%-12s%-12s%-12s%-12s%-12s\n","Player", "Champion", "Team", "Kills", "Deaths");

	printf("\n");

	//While not at the end of the linked list, run through list and print info
	current = head;
	while(current != NULL)
	{
		printf("%-12s%-12s%-12s%-12d%-12d\n", current->name, current->champion, current->team, current->kills, current->deaths);
		current = current->next;
	}

	printf("\n");
}

//Searches through linked list and changes the champion, kills, and deaths
int update_records(Player* head, char* champion, char* champ_name, int kills, int deaths)
{
	Player* current;
	current = head;

	//While not at the end of the list, run through list and change info
	if(current != NULL)
	{
		//If desired champion is found, change champion name, kills, and deaths
		if(strcmp(current->champion, champion) == 0)
		{
			strcpy(current->champion, champ_name);
			current->deaths = deaths;
			current->kills = kills;
			return 1;
		}
		//If desired champion is not found, move down the list
		else
		{
			current = current->next;
			return update_records(current, champion, champ_name, kills, deaths);
		}

		//Returns 0 if linked list was not updated
		return 0;
	}
}

//Deletes node if kill death ratio is even
Player* delete_player_even(Player* head)
{
	Player* previous = NULL;
	Player* current = head;
	Player* temp = NULL;

	int ratio = 0;
	//While not at the end of the linked list
	while(current->next != NULL)
	{
		//Calculates KD ratio
		ratio = current->kills/current->deaths;

		//If ratio is even
		if(ratio % 2 == 0)
		{
			//Delete the node with the end KD ratio
			temp = current;
			current = current->next;
			free_node(temp);
			previous->next = current;
		}
		//Moves to next node in linked list
		else
		{
			previous = current;
                	current = current->next;
		}
	}

	//If at the last node
	if(current->next == NULL)
        {
                 //Calculates KD ratio
                 ratio = current->kills/current->deaths;

		//If ratio is odd
                 if(ratio % 2 == 0 || ratio == 0)
                 {
                 	//Delete node with the odd KD ratio
                        temp = current;
                        current = current->next;
                        free_node(temp);
                        previous->next = current;
                  }
	}

	return head;
}

//Deletes node if kill death ratio is odd or zero
Player* delete_player_odd(Player* head)
{
	Player* previous = NULL;
	Player* current = NULL;
       	Player* temp = NULL;

	//Finds KD ratio
        int ratio = head->kills/head->deaths;

	//If first node's KD is odd, delete node.
	//Establishes head
	while(ratio % 2 != 0 &&  head != NULL)
	{
		temp = head;
		head = head->next;
		free_node(temp);
		if(head != NULL)
			ratio = head->kills/head->deaths;
	}

	//If list is empty
	if(head == NULL)
		return head;

	previous = head;
	current = head->next;

	//While not at the end of the linked list
        while(current != NULL)
        {
		//Calculates KD ratio
	        ratio = current->kills/current->deaths;

		//If ratio is odd
                if(ratio % 2 != 0 || ratio == 0)
                {
		     //Delete node with the odd KD ratio
  	             temp = current;
                     current = current->next;
		     previous->next = current;
                     free_node(temp);
                }
		//If KD is not odd
		else
		{
			//Move to next node in linked list
			previous = current;
        	        current = current->next;
		}

        }

	return head;
}

//Frees memory for a node
void free_node(Player* node)
{
	//Frees memory malloced for name
	free(node->name);
	//Frees memory malloced for champion name
	free(node->champion);
	//Frees memory malloced for team name
	free(node->team);
	//Finally, frees node altogether
	free(node);
}

//Reverses the linked list
Player* reverse_list(Player* head)
{
	Player* prev = NULL;
	Player* current = head;
	Player* temp = NULL;

	//While not at the end of the linked list, move each node into reverse order
	while(current != NULL)
	{
		temp = current->next;
		current->next = prev;
		prev = current;
		current = temp;
	}

	head = prev;

	return head;

}
