//
//  Term Project - Shuffle for Moodify
//  shuffler.c
//
//  Reece Jackson
//  11/22/14
//
//  COEN 11
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//define constants
#define song_number 5000
#define song_length 100

//function prototypes
int read_playlist(char* playlist_name, char* playlist[]);
void shuffle(char** playlist, int length);
void make_playlist(char** playlist, char* name, int length);

int main(int argc, char* argv[])
{
    //store the name of the playlist file
    char playlist_name[] = "playlist.txt";
    
    //make the dynamic string array for storing the contents of the playlist file
    char* playlist[song_number];
    
    //read the playlist file into the array playlist
    int length = read_playlist(playlist_name, playlist);
    
    //seed the random function
    srand(time(NULL));
    
    //make a different shuffled playlist for each day of the week
    make_playlist(playlist, "shuffle[Monday].txt", length);
    make_playlist(playlist, "shuffle[Tuesday].txt", length);
    make_playlist(playlist, "shuffle[Wednesday].txt", length);
    make_playlist(playlist, "shuffle[Thursday].txt", length);
    make_playlist(playlist, "shuffle[Friday].txt", length);
    make_playlist(playlist, "shuffle[Saturday].txt", length);
    make_playlist(playlist, "shuffle[Sunday].txt", length);
}

//read songs from a file into a dynamic string array
int read_playlist(char* playlist_name, char* playlist[])
{
    //make temporary variable for song name
    char tempsong[song_length];
    
    //create the file pointer for the file and open the file
    FILE* input;
    if((input = fopen(playlist_name, "r")) == NULL)
    {
        printf("Error: playlist cannot be opened.\n");
        return -1;
    }
    
    //itterate over each song in input copying it to playlist
    int i;
    for(i = 0; fgets(tempsong, song_length, input) != NULL; i++)
    {
        //make each playlist[i] element point to a string
        playlist[i] = (char *) malloc(sizeof(char)*strlen(tempsong));
        
        //copy the songname into that string
        strcpy(playlist[i], tempsong);
    }
    
    //return the number of songs
    return i;
}


//shuffle a playlist given its length
void shuffle(char** playlist, int length)
{
    //make variable to be used for random value
    int j;
    
    //itterate over the length of playlist swaping strings
    for(int i = length-1; i > 0; i--)
    {
        //store random index between 0 and i in j
        j = rand() % i;
        
        //swap playlist[j] with playlist[i]
        char* temp = playlist[j];
        playlist[j] = playlist[i];
        playlist[i] = temp;
    }
}

//make a new shuffled playlist file from playlist given a name and length
void make_playlist(char** playlist, char* name, int length)
{
    //create the file pointer for the outfile and open the file
    FILE* output;
    if((output = fopen(name, "w")) == NULL)
    {
        printf("Error: unable to create file.\n");
        return;
    }
    
    //save the time that the shuffling begins
    double time_start = clock() / (double) CLOCKS_PER_SEC;
    
    //shuffle the playlist array
    shuffle(playlist, length);
    
    //save and print the final clock times
    double time_stop = clock() / (double) CLOCKS_PER_SEC;
    printf("Time start:    %f\nTime Stop:     %f\n\n", time_start, time_stop);

    //itterate over the playlist writing each string to the new file
    for(int i = 0; i < length; i++)
    {
        fputs(playlist[i], output);
    }
}