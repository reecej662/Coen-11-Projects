//////////////////////////////////////////////
//
//  lab4.c
//
//  Reece Jackson
//
//  COEN 11
//  Lab 2
//
//  Makes a list of people
//
//////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#define list_size 30
#define name_size 10
#define school_name 20

//Start implementing a struct instead of the double arrays

typedef union info{
        char school[school_name];
        float salary;
        int years_retire;
} info;

typedef struct people{
    char name[name_size];
    int age; 
    info status;
} people;

//if age is <= 21 store school
//if age is 21 < ag e< 65 store salary per month
//if age is > 65 store years of retirement

//function prototypes
void add(people *people_list, int* counter);
void delete(people *people_list, int* counter);
void display(people *people_list, int counter);

int main()
{
    //declare variables
    int counter = 0;
    int input;
    
    //make the list of people
    people people_list[list_size];

    while('true')
	{
        //provide the interface that instructs the user on how to use the menu
        printf("Please enter a numnber 1-4 based on the following options:\n1:Add\n2:Remove\n3:Display\n4:Quit\n");
        scanf("%d", &input);
        printf("\n");
    
        //switch through the different optinos depending on the input
		switch(input)
		{
            case 1:
				add(people_list, &counter);
				break;
			case 2:
				delete(people_list, &counter);
                break;
			case 3:
				display(people_list, counter);
				break;
			case 4:
				return 0;
			default:
                printf("Enter a valid selection.\n\n");
				break;
        }
    
    }
    return 0;
}

//asks for a name of guest and guest number and adds it to an array
void add(people *people_list, int *counter)
{
	//get the name from the user
	printf("Enter the name of the person.\n");
	scanf("%s", (people_list[*counter].name));

	//get the age from the user
	printf("Enter the age of the person.\n");
	scanf("%d", (&people_list[*counter].age));
	
    //check the age in order to store the right status
	if(people_list[*counter].age <= 21)
	{	
		printf("Enter the name of the person's school: ");
		scanf("%s", (people_list[*counter].status.school));
		printf("\n");
	}
    
    else if(people_list[*counter].age > 21 && people_list[*counter].age < 65)
	{
		printf("Enter their salary per month: ");
        scanf("%f", (&people_list[*counter].status.salary));
        printf("\n");
    }
    
    else
    {
		printf("Enter their years of retirement: ");
        scanf("%d", (&people_list[*counter].status.years_retire));
        printf("\n");
	}
    
    //incrememnt the counter
    (*counter)++;
    
    return;
}

//deletes the specified person from the list 
void delete(people *people_list, int* counter)
{
    //create a temporary variable to store the name
	char rname[name_size];	

	printf("Who would you like to remove: ");
	scanf("%s", rname);

	//store the index where the person is found
	int index = -1;
	
    //search the whole array for the person
	for(int i = 0; i < list_size; i++)
    	{
		if((strcmp(rname, people_list[i].name)) == 0)
		{
            //if found store the index and break
			index = i;
			break;
		}else if(i == list_size)
		{
            //if reach the end of the array print it wasn't found and break
			printf("Person not found.\n");
			break;
		}
	}

    //shift all the following people up to fill the empty spot
    for(int i=index; i < *counter; i++)
    {
        people_list[i] = people_list[i+1];
    }
    
	//print that they've been deleted
	printf("%s has been deleted\n\n", rname);
    
    //decrement the counter to the new list size
    (*counter)--;

}

//displays all the current people on the list
void display(people *people_list, int counter)
{
	//itterates over the whole list printing out the people
	for(int i = 0; i < counter; i++)
    {
        //print out the name and age
		printf("%d) Person: %s -- Age: %d -- ", (i+1), people_list[i].name, people_list[i].age);
		
        //then checl the age to determine the other information to be printed
		if(people_list[i].age <= 21)
        {
            printf("School: %s\n", people_list[i].status.school);
        }
        else if(people_list[i].age > 21 && people_list[i].age < 65)
		{
            printf("Salary per Month: %f\n", people_list[i].status.salary);
        	
        }else
        {
            printf("Years of Retirement: %d\n", people_list[i].status.years_retire);
        }
	}
    	
    printf("\n");
}