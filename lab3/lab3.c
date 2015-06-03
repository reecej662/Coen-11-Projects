/****************************************************************************
 * lab3.c
 *
 * Reece Jackson
 *
 * COEN 11
 * Lab 3
 *
 * Implements a restaurant's waiting list by using structs
 ***************************************************************************/

#include <stdio.h>
#include <string.h>

#define list_size 30
#define name_size 10


//Implement the structure for the customers
typedef struct guest{
    char name[name_size];
    int num;
} guest;

//function prototypes
void add(guest guest_list[], int *counter);
void delete(guest guest_list[], int *counter);
void display(guest guest_list[], int counter);

int main()
{
    //make the waiting list
    guest guest_list[list_size];
    
    //declare variables
    char input = 0;             //the input from the users
    int counter = 0;            //the counter for number of names
    
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
				add(guest_list, &counter);
				break;
			case '2':
				delete(guest_list, &counter);
                break;
			case '3':
				display(guest_list, counter);
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
void add(guest guest_list[], int *counter)
{
    char temp[name_size];
	
	//get the name from the user
	printf("Enter the name of the guest.\n");
	scanf("%s",temp);
	
    //check to make sure the name isn't already in the list
	if(*counter==0)
    {
        for(int i = 0; i < *counter; i++)
        {
            while(strcmp(guest_list[i].name,temp) == 0)
            {
                    printf("Name already in list. Please enter a different name.\n");
                    scanf("%s",temp);
            }
        }
    }
    
	//get the number from the user
	printf("Enter the number of guests.\n");
	scanf("%d", &guest_list[*counter].num);

	//add the guest to the array of guests at the bottom of the list
	strcpy(guest_list[*counter].name, temp);
    
    //increment counter
    *counter = *counter + 1;
    
	printf("\n");
}

//deletes the oldest member from the list
void delete(guest guest_list[], int *counter)
{
    //prints the name of the oldest entry
    printf("%s", guest_list[0].name);
	
    //moves all the other entrys up one line in the array
    for(int i = 0; i < (list_size - 1); i++)
    {
        guest_list[i] = guest_list[i+1];
    }
	
    //print that they've been deleted
	printf(" has been deleted\n\n");
    
   	 //decrements the number of people in the list by one
	*counter = *counter - 1;

}

//displays all the current people on the list
void display(guest guest_list[], int counter)
{
    //itterates over the whole list printing out the people
	for(int i = 0; i < counter; i++)
	{
        printf("%d) Name: %s -- Number: %d\n", (i+1), guest_list[i].name, guest_list[i].num);
	}
    
    printf("\n");
}
