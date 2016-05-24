#include <stdio.h>

#define MAX_NAME_LENGTH 20
#define MAX_ARRAY_LENGTH 25

//Prototypes
int read_file(FILE* input);
void print_grade_distribution(int num_students);
void calculate_gpa(int index);
void write_to_file(FILE* output, int num_students);

typedef struct student_{
	char name[MAX_NAME_LENGTH];
	int num_A;
	int num_B;
	int num_C;
	int num_D;
	int num_F;
	float gpa;
}student;

student class[MAX_ARRAY_LENGTH];

int main(int argc, char* argv[])
{
	//If there are not enough components
	if(argc < 2)
	{
		printf("Incorrect number of command line argumnets/n");
		return 1;
	}

	//Opens file to be read
	FILE* input = fopen(argv[1], "r");

	//Stores student info in global array and calculates gpa for each student, and returns number of students within file
	int size = read_file(input);

	//Closes file
	fclose(input);

	//Prints the histogram for grade distribution
	print_grade_distribution(size);

	//Opens the output file for writing
	FILE* output = fopen(argv[2], "w");

	//Writes the names and gpa's of the students
	write_to_file(output, size);

	//Closes output file
	fclose(output);

	return 0;
}

int read_file(FILE* input)
{
	int size;//Size of file
	int i;//Counter

	//Collects size of file
	fscanf(input, "%d", &size);

	//Places info in global class array
	for(i=0; i<size; i++)
	{
		//Scans info into global array
		fscanf(input, "%s %d %d %d %d %d", &class[i].name, &class[i].num_A, &class[i].num_B, &class[i].num_C, &class[i].num_D, &class[i].num_F);

		//Calculates gpa for each student
		calculate_gpa(i);
	}

	return size;
}

void print_grade_distribution(int num_students)
{
	int i, k, index;//Counters
	char j = 'A';//Counter
	int freq[5]={0};//Frequency array for grades

	//Counts the frequency of each grade
	for(index = 0; index < num_students; index++)
	{
		freq[0] += class[index].num_A;
		freq[1] += class[index].num_B;
		freq[2] += class[index].num_C;
		freq[3] += class[index].num_D;
		freq[4] += class[index].num_F;
	}

	for(i = 0; i < 5; i++)
	{
		//Prints column titles for each grade
		printf("%c: ", j);
		if(j == 'D')//Skips E
			j++;
		j++;

		for(k = 0; k < freq[i]; k++)
		{
			//Prints the dashes for each grade
			printf("-");
		}
          printf("\n");
	}
}

void calculate_gpa(int index)
{
	//Total collects amount of total grades
	int total = class[index].num_A * 4;
	total += (class[index].num_B * 3);
	total += (class[index].num_C * 2);
	total += (class[index].num_D + class[index].num_F);

	//Averages them out to collect the gpa
	class[index].gpa = (float) total/(class[index].num_A + class[index].num_B + class[index].num_C + class[index].num_D + class[index].num_F);
}

void write_to_file(FILE* output, int num_students)
{
	int i;//Counter

	//Prints name and gpa for each student into the output file
	for(i=0; i<num_students; i++)
	{
		fprintf(output, "%s %.6f", class[i].name, class[i].gpa);

		fprintf(output, "\n");
	}
}
