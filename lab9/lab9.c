//
//  lab9.c
//  lab 9
//
//  Reece Jackson
//  COEN 11
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define name_size 10
#define header_size 50
char* savefile;


//Implement the structure for the customers
typedef struct NODE{
    char name[name_size];
    int num;
    struct NODE* next;
} NODE;

pthread_mutex_t save_lock;

//function prototypes
NODE* insert(NODE* head, char* name, int num);
NODE* delete(NODE* head);
void display(NODE* head);
NODE* display_binary(char* file, NODE* temp);
NODE* getdata(char* list, NODE* head);
void save(char* list, NODE* head);

void* autosave(void* list);

int main(int argc, char* argv[])
{
    argc = 2;
    argv[1] = "/DCNFS/users/student/rjackson/Desktop/list.txt";
    
    //make sure there are enough elements
    if(argc != 2)
    {
        printf("Error: Not enough arguments.\n");
        return 1;
    }
    
	savefile = malloc(sizeof(char)*strlen(argv[1]));
	strcpy(savefile, argv[1]);
    
    //make the waiting list
    NODE* head = NULL;
    head = getdata(argv[1], head);
    
    //declare variables
    int input = 0;             //the input from the users
	
    //make autosave thread
	pthread_t saver;
	
	pthread_create(&saver, NULL, autosave, (void *) &head);
    
    while('true')
    {
        //provide the interface that instructs the user on how to use the menu
        printf("Please enter a numnber 1-5 based on the following options:\n1:Add\n2:Remove\n3:Display\n4:Display Binary\n5:Quit\n");
        scanf("%d", &input);
        printf("\n");
        
        //switch through the different optinos depending on the input
        switch(input)
        {
            case 1:
            {
                char tmp_name[name_size];
                int tmp_num;
                
                printf("What is the name of the reservation?\n");
                scanf("%s", tmp_name);
                
                printf("What is the size of the reservation?\n");
                scanf("%d", &tmp_num);
                
                head = insert(head, tmp_name, tmp_num);
                printf("\n");
                break;
            }
            case 2:
                head = delete(head);
                break;
            case 3:
                display(head);
                break;
            case 4:
            {
                NODE* temp = NULL;
                temp = display_binary(argv[1], temp);
                display(temp);
                break;
            }
            case 5:
            {
                pthread_mutex_lock(&save_lock);
                pthread_cancel(saver);
                save(argv[1], head);
                pthread_mutex_unlock(&save_lock);
                
                return 0;
            }
            default:
                printf("Enter a valid selection.\n\n");
                break;
        }
    }
}

//asks for a name of guest and guest number and adds it to an array
NODE* insert(NODE* head, char* name, int num)
{
    //create the node where the information will be stored
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    new_node->next = NULL;
    
    //check to make sure the memory could be allocated
    if(new_node == NULL)
    {
        printf("The memory could not be allocated.\n");
        return head;
    }
    
    //make a temporary pointre to search through the list
    NODE* ptr = head;
    
    //check to make sure the name isn't already in the list
    while(ptr != NULL)
    {
        if(strcmp(ptr->name, name) == 0)
        {
            printf("The name is already in the list. Please enter a different name:\n");
            scanf("%s", name);
        }else{
            ptr = ptr->next;
        }
    }
    
    //add the name to the node
    strcpy(new_node->name, name);
    
    //add the number to the node
    new_node->num = num;
    
    //add the node to the bottom of the list
    ptr = head;
    
    //if it's the first element of the list make it the head
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

//load the specified file into the linked list to start out
NODE* getdata(char* list, NODE* head)
{
    //create the file pointer and open the file
    FILE* input = NULL;
    if((input = fopen(list, "rb")) == NULL)
    {
        printf("The waiting list cannot be opened.\n");
        return NULL;
    }
    
    //temporary variables
    char temp_name[name_size];
    int temp_num;
    
    //scan the string into the temporary variables until EOF and insert them into the list
    while((fread(&temp_name, sizeof(char), name_size, input) != 0 && (fread(&temp_num, sizeof(int), 1, input)) != 0))
    {
	    head = insert(head, temp_name, temp_num);
    }
    
    //close the file and return
    fclose(input);
    return head;
}

//save the list into the specified file
void save(char* list, NODE* head)
{
    //create file pointer and open the file
    FILE* output = NULL;
    if((output = fopen(list, "wb")) == NULL)
    {
        printf("The waiting list cannot be saved.\n");
        return;
    }
    
    //make pointers to traverse the list
    NODE* curr = head;
    NODE* prev = head;
    
    //copy elements into the linked list freeing as you go
    while(curr != NULL)
    {
        // fprintf(output, "%s %d\n", curr->name, curr->num);
        fwrite(curr->name, sizeof(char), name_size, output);
        fwrite(&curr->num, sizeof(int), 1, output);
        prev = curr;
        curr = curr->next;
    }
    
    //close the file
    fclose(output);
}

//worker function to save the list every 5 seconds
void* autosave(void* list)
{
    while('true')
    {
        NODE* head = *((NODE**)list);
        
        pthread_mutex_lock(&save_lock);
        save(savefile, head);
        pthread_mutex_unlock(&save_lock);
        
        sleep(5);
    	printf("Saving...\n");
    }
}

//display data currently saved in binary file
NODE* display_binary(char* file, NODE *temp)
{
    temp = getdata(file, temp);
    return temp;
}
