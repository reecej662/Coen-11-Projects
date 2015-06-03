//
// lab8.c
// Lab 8
//
// Reece Jackson
// COEN 11
// 11-14-14
//

#include <stdio.h>
#include <string.h>

#define size 20

void reverse(char* line, int length);

int main(int argc, char*  argv[])
{
	//check to make sure there are enough inputs
	if(argc != 3)
	{
		printf("Error: not enough inputs.\n");
		return 1;
	}
	
	//create file pointers and open files
	FILE* in;
	FILE* out; 

	if((in = fopen(argv[1], "r")) == NULL)
	{
		printf("The input file could not be opened.\n");
		return 2;
	}

        if((out = fopen(argv[2], "w")) == NULL)
        {
                printf("The input file could not be opened.\n");
                return 3;
        }
	
	//make temporary array to read lines into
	char line[size];

	//read from the input file, reverse,  and write to the output file
	while((fgets(line, size, in)) != NULL)
	{
		int length = strlen(line);
		reverse(line, length);
		fputs(line, out);
	}

	return 0;
}

//reverse a string of given length
void reverse(char* line, int length)
{
	//if there's more than one element
	if(length >= 2)
	{
		//swap the first element of the array with the last element
		char temp = line[0];
		line[0] = line[length-2];
		line[length-2] = temp;

		//reverse the inner subset of the string		
		reverse(&line[1], length-2);
	}

	return;
}
