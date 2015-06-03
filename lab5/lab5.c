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
NODE* insert(NODE* head);
NODE* delete(NODE* head);
void display(NODE* head);

int main()
{
    //make the waiting list
    NODE* head = NULL;
    
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
                head = insert(head);
                break;
            case 2:
                head = delete(head);
                break;
            case 3:
                display(head);
                break;
            case 4:
            {
                NODE* ptr = head;
                NODE* preptr = ptr;
                
                while(ptr != NULL)
                {
                    preptr = ptr;
                    ptr=ptr->next;
                    free(preptr);
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
NODE* insert(NODE* head)
{
    //create the node where the information will be stored
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    new_node->next = NULL;
    
    //make a temporary array to store the name
    char temp[name_size];
    
    //check to make sure the memory could be allocated
    if(new_node == NULL)
    {
        printf("The memory could not be allocated.\n");
        return head;
    }
    
    //make a temporary pointre to search through the list
    NODE* ptr = head;
    
    //get the name from the user
    printf("Enter the name of the reservation:\n");
    scanf("%s",temp);
    
    //check to make sure the name isn't already in the list
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
    
    //add the name to the
    strcpy(new_node->name, temp);
    
    //get the number from the user
    printf("Enter the number of guests:\n");
    scanf("%d", &new_node->num);

    //add the node to the bottom of the list
    ptr = head;
    
    //check to see if it's a new head, if not make it 
    if(head == NULL)
    {
        head = new_node;
        printf("\n");
        return head;
    }
    
    //incrememnt through the list as long as you're not at the end
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    
    //make the last elemenet point to the new node
    ptr->next = new_node;
    
    printf("\n");

    return head;
}

//deletes the oldest member from the list
NODE* delete(NODE* head)
{
    //make a temporary pointer to traverse the list
    NODE* ptr = head;
    NODE* preptr = ptr;
    
    //get a value from the user to delete
    int selection = -1;
    printf("Enter the size of the open table:\n");
    scanf("%d", &selection);
    
    //check the list to find an entry with the number
    while(ptr != NULL && !(ptr->num <= selection))
    {
        //increment previous ptr and ptr as you move through the list
        preptr = ptr;
        ptr = ptr->next;
    }
    
    //if you're at the end of the list, the reservation wasn't found
    if(ptr == NULL)
    {
        printf("No avaliable tables found.\n\n");
        return head;
    }
    
    //prints the name of the oldest entry with the given size
    printf("%s", ptr->name);

    //print that they've been deleted
    printf("'s reservatiion has been removed.\n\n");
    
    //if you delete the head, make the next node the new head
    if(ptr == head)
    {
        head=head->next;
    }
       
    //remove the element of the linked list
    preptr->next = ptr->next;
       
    //deallocate the poitner
    free(ptr);

    return head;
}

//displays all the current people on the list
void display(NODE* head)
{
    NODE* ptr = head;
    int counter = 1;
    
    //itterates over the whole list printing out the people
    while(ptr != NULL)
    {
        printf("%d) Name: %s -- Size: %d\n", counter, ptr->name, ptr->num);
        ptr = ptr->next;
        counter++;
    }
    
    printf("\n");
}
