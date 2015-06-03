/****************************************************************************
 * lab2.c
 *
 * Reece Jackson
 *
 * COEN 11
 * Lab 2
 *
 * Implements a restaurant's waiting list
 ***************************************************************************/

#include <stdio.h>
#include <string.h>

#define list_size 30

//function prototypes
void add();
void delete();
void display();

char input = 0;             //the input from the user
char names[list_size][10];  //the array of guest names
int nums[list_size];        //the array of guest numbers
int counter = 0;            //the counter for number of names
char *oldest = names[0];    //the pointer for the oldest entry in the array

int main()
{	
    while('true')
	{
        //provide the interface that instructs the user on how to use the menu
        printf("Please enter a numnber 1-4 based on the following options:\n1:Add\n2:Remove\n3:Display\n4:Quit\n");
        scanf("%s", &input);
        printf("\n");
        
        //switch through the different optinos depending on the input
		switch(input)
		{
            case '1':
				add();
				break;
			case '2':
				delete();
                break;
			case '3':
				display();
                break;
			case '4':
				return 0;
				break;	
			default:
                printf("Enter a valid selection.\n\n");
				break;
		}
	}
}

//asks for a name of guest and guest number and adds it to an array
void add()
{
	char guest[10];
	int num;
	
	//get the name from the user
	printf("Enter the name of the guest.\n");
	scanf("%s", guest);
	
        //check to make sure the name isn't already in the list
        for(int i = 0; i < list_size; i++)
        {
                while(strcmp(names[i], guest) == 0)
		{
			printf("Name already in list. Please enter a different name.\n");
			scanf("%s", guest);
		}
	} 

	//get the number from the user
	printf("Enter the number of guests.\n");
	scanf("%d", &num);

	//add the guest to the array of guests at the bottom of the list	
	strcpy(names[counter], guest);

	//adds the guest's number at a corresponding position in the num array
	nums[counter] = num;

    //increment the number of people in the list
	counter++;
    
	printf("\n");
}

//deletes the oldest member from the list
void delete()
{
    //prints the name of the oldest entry
	for(int i = 0; names[0][i] != 0; i++)
	{
		printf("%c", names[0][i]);
	}
	
    //moves all the other entrys up one line in the array
	for(int i = 0; i < (list_size - 1); i++)
	{
		strcpy(names[i], names[i + 1]);
		nums[i] = nums[i + 1];
	}	
	
    //print that they've been deleted
	printf(" has been deleted\n\n");
    
    //decrements the number of people in the list by one
	counter--;

}

//displays all the current people on the list
void display()
{
	printf("\n");
    
    //itterates over the whole list printing out the people
	for(int i = 0; i < counter; i++)
	{
		printf("%d)Guest: %s -- Number: %d\n", (i+1), names[i], nums[i]);
	}
    
    printf("\n");
}
