#include <stdlib.h>
#include <stdio.h>

#define MAX_FILE_LENGTH 20

typedef struct node_{
	int value;
	/*struct node_ next;
	1) added a missing * behind node_ */
	struct node_* next;
}Node;

typedef Node* List;

int create_list(List**,FILE*);
void print_list(List*, int);
void free_list(List*, int);
int list_sum(Node*);
void insertion_sort(List*, int);
/*2) Missing prototype*/
Node* new_node(int);

/* Main will read in an input file from the command line,
if the file fails to open the program should prompt the user for a new file,
at no point should the program quit. If the program reads in a new file name,
it can be up to size MAX_FILE_LENGTH.
From there the program should read in the file, print it out, sort it,
print it out again and then free it. */
int main (int argc, char* argv[]){

	if(argc != 2){
		printf("Incorrect number of command line arguments.\n");
		return 1;
	}

	/*FILE* fp = fopen(argv[0], "r");
	3) changed argv[0] to argv[1]*/
	FILE* fp = fopen(argv[1], "r");

	while(fp == NULL){
		char file[MAX_FILE_LENGTH];
		printf("Unable to open file, enter a new file name: ");
		/*scanf("%d", file);
		should not be %d, should be %s*/
		scanf("%s", file);
		fp = fopen(file, "r");
	}

	/*List array;
	4)Must be List* because it is an array of lists*/
	List* array;
	/*int length = create_list(array, fp);
	5) parameter not of right type*/
	int length = create_list(&array, fp);

	printf("Pre Sort\n");
	/*print_list(&array, length);
	6) Parameter must be of type List*/
	print_list(array, length);

	/*insertion_sort(length, array);
	7) Parameters are mixed*/
	insertion_sort(array, length);
	printf("\nPost Sort\n");
	print_list(array, length);


	return 0;
}

/*This function takes in a pointer to a list and a file pointer.
The first line of the input file is the length of the array to be created.
Each subsequent line is composed of two numbers, an index and a value.
The index is the index of the linked list where a node with the value of value should be inserted.
So for example, if index = 0 and value = 3, and before the insertion array[0] = 1 -> 2 -> NULL,
after the insertion array[0] = 3 -> 1 -> 2 -> NULL. This function returns the length of the array.*/
int create_list(List** array,FILE* fp){

	int length, i, index, value;

	fscanf(fp, "%d", &length);

	/*array = malloc(sizeof(Node));
	8) this changes the pointer rather than changing the array*/
	*array = malloc(length * sizeof(List*));

	for(i = 0; i < length; i++)
		(*array)[i] = NULL;

	/*while(1){
	9) infinite while loop*/
	while(fscanf(fp, "%d %d", &index, &value) !=  EOF){
		/*fscanf(fp, "%d %d", &index, &value);
		10) Moved into the while loop*/

		Node* node = new_node(value);

		/*node->next = array[index];
		11) Must dereference the array*/
		node->next = (*array)[index];

		/*array[index] = node;
		12) Must dereference the array*/
		(*array)[index] = node;
	}

	return length;
}

/*Creates a new node of type Node, sets node->value = value and returns it. */
Node* new_node(int value){
	/*Node* node;
	11) Needs to malloc node*/
	Node* node = malloc(sizeof(node));
	node->value = value;
	node->next = NULL;

	return node;
}

/*Takes in the head to a single linked list and returns the sum of the values of each of its nodes.
Ex: Node* head = 1 -> 2 -> 3 -> NULL then list_sum(head) = 6.*/
int list_sum(Node* head){
	/*12) Would get a seg fault if dereferenced NULL*/
	if(head == NULL)
		return 0;

	return head->value + list_sum(head->next);

}

/*For each index in the array, print the index, the linked list it points to,
and the sum of its nodes. See the sample output for an example.*/
void print_list(List* array, int length){

	int i;

	for(i = 0; i < length; i++){
		Node* curr = array[i];

		printf(" -\n|%d| ", i);

		/*13) Missing while loop*/
		while(curr != NULL){
			printf("%d ->", curr->value);

			curr = curr->next;
		}

		printf("NULL = %d\n -\n", list_sum(array[i]));
	}

	/*return curr;
	14) Function should not return anything*/
}

/*Sorts the array using insertion sort in ascending order by the sums of each linked list. */
void insertion_sort(List* array, int length){
	int* sum = malloc(sizeof(int) * length);
	int i, j, value;
	Node* node;

	/*15) Need to initialize sum array*/
	for(i=0; i< length; i++)
	{
		sum[i] = list_sum(array[i]);
	}

	for(i = 1; i < length; i++){
		value = sum[i];
		node = array[i];
		/*for(j = i; j > 0 && value < sum[j + 1]; j++)
		16) Going down the list*/
		for(j = i; j > 0 && value < sum[j - 1]; j--){
			sum[j] = sum[j - 1];
			/*17) Missing code to store temp variable*/
			sum[j-1] = value;
			array[j] = array[j - 1];
			/*18) Missing code to store temp variable*/
			array[j-1] = node;
		}
	}

	printf("\n");
	free(sum);
}

/*Free all allocated memory.*/

/*void free_list(List array, int length){
19) Parameters do not match up with prototype*/
void free_list(List* array, int length){
	int i;

	/*while(curr != NULL){
	20) Current not declared outside loop*/
	List curr = *array;
	while(curr != NULL){
		Node* prev = curr;
		curr = curr->next;
		/*free(curr);
		21)Should free prev, not curr*/
		free(prev);
	}
}
