/****************************************************************************
 * lab5.c
 *
 * Reece Jackson
 *
 * COEN 11
 * Lab 5
 *
 * Implements a restaurant's waiting list by using linked lists
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define name_size 10


//Implement the structure for the customers
typedef struct NODE{
    char name[name_size];
    int num;
    struct NODE* next;
} NODE;

//function prototypes
void insert(NODE* head[], NODE* tail[]);
void delete(NODE* head[], NODE* tail[]);
void display(NODE* head[]);

int main()
{
    //make the waiting list
    NODE* head[4] = {NULL, NULL, NULL, NULL};
    NODE* tail[4] = {NULL, NULL, NULL, NULL}; 
    
    //declare variables
    int input = 0;             //the input from the users
    
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
                insert(head, tail);
                break;
            case 2:
                delete(head, tail);
                break;
            case 3:
                display(head);
                break;
            case 4:
            {
            	for(int i = 0; i < 4; i++)
		{
			NODE* ptr = head[i];
                	NODE* preptr = ptr;
                
                	while(ptr != NULL)
                	{
                    		preptr = ptr;
                    		ptr=ptr->next;
                    		free(preptr);
                	}
		}

                return 0;
                
                break;
            }
            default:
                printf("Enter a valid selection.\n\n");
                break;
        }
    }
}

//asks for a name of guest and guest number and adds it to an array
void insert(NODE* head[], NODE* tail[])
{
    //create the node where the information will be stored
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    new_node->next = NULL;
    
    char temp[name_size];
    
    //check to make sure the memory could be allocated
    if(new_node == NULL)
    {
        printf("The memory could not be allocated.\n");
    }

    //make a temporary pointre to search through the list
    NODE* ptr = head[0];
    
    //get the name from the user
    printf("Enter the name of the reservation:\n");
    scanf("%s",temp);
    
    //check to make sure the name isn't already in the list
    for(int i = 0; i < 4; i++)
    {
	ptr = head[i];
	while(ptr != NULL)
    	{
        	if(strcmp(ptr->name, temp) == 0)
        	{
            		printf("The name is already in the list. Please enter a different name:\n");
            		scanf("%s", temp);
        	}else{
            		ptr = ptr->next;
       		}
    	}
    }

    //add the name to the
    strcpy(new_node->name, temp);
    
    //get the number from the user
    printf("Enter the number of guests:\n");
    scanf("%d", &new_node->num);

    //add the node to the bottom of the list
    switch(new_node->num)
    {
	case 1:
	case 2:
		ptr = head[0];
		if(head[0] == NULL)
		{
			head[0] = new_node;
			return;
		}
		while(ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = new_node;
		tail[0] = new_node;
		break;
	case 3:
	case 4:
		ptr = head[1];
                if(head[1] == NULL)
                {
                        head[1] = new_node;
			return;
                }
                while(ptr->next != NULL)
                {
                        ptr = ptr->next;
                }
                ptr->next = new_node;
                tail[1] = new_node;
		break;
	case 5:
	case 6:
		ptr = head[2];
                if(head[2] == NULL)
                {
                        head[2] = new_node;
                	return;
		}
                while(ptr->next != NULL)
                {
                        ptr = ptr->next;
                }
                ptr->next = new_node;
                tail[2] = new_node;
		break;
	default:
                ptr = head[3];
                if(head[3] == NULL)
                {
                        head[3] = new_node;
			return;
                }
                while(ptr->next != NULL)
                {
                        ptr = ptr->next;
                }
                ptr->next = new_node;
                tail[3] = new_node;
		break;
	}
}    

//deletes the oldest member from the list
void delete(NODE* head[], NODE* tail[])
{
    //make a temporary pointer to traverse the list
    NODE* ptr = head[0];
    NODE* preptr = ptr;
    
    //get a value from the user to delete
    int selection = -1;
    printf("Enter the size of the open table:\n");
    scanf("%d", &selection);
    int s = 0;

    switch(selection)
    {
	case 1:
	case 2:
		s = 0;
		break;
	case 3:
	case 4: 
		s = 1;
		break;
	case 5:
	case 6:
		s=2;
		break;
	default:
		s = 3;
		break;
    }
		
    for(int i = s; i >= 0; i--)
    {
	ptr = head[i];
    	//check the list to find an entry with the number
    	while(ptr != NULL && !(ptr->num <= selection))
    	{
        	//increment previous ptr and ptr as you move through the list
        	preptr = ptr;
        	ptr = ptr->next;
    	}
	s = i;
	if(ptr != NULL && ptr->num <= selection)
		i = -1;
    }

    //if you're at the end of the list, the reservation wasn't found
    if(ptr == NULL)
    {
        printf("No avaliable tables found.\n\n");
	return;   
    }

    //prints the name of the oldest entry with the given size
    printf("%s", ptr->name);

    //print that they've been deleted
    printf("'s reservatiion has been removed.\n\n");

    //if you delete the head, make the next node the new head
    if(ptr == head[s])
    {
        head[s]=head[s]->next;
    }
       
    //remove the element of the linked list
    preptr->next = ptr->next;
       
    //deallocate the poitner
    free(ptr);

}

//displays all the current people on the list
void display(NODE* head[])
{
    NODE* ptr = head[0];
    int counter = 1;
    
    //itterates over the whole list printing out the people
    for(int i = 0; i<4; i++)
    {
	ptr = head[i];
	printf("List %d contains:\n", i+1);   	

	while(ptr != NULL)
    	{
        	printf("%d) Name: %s -- Size: %d\n", counter, ptr->name, ptr->num);
        	ptr = ptr->next;
        	counter++;
    	}
	printf("\n");
    }
    
    printf("\n");
}
