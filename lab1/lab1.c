#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <time.h>

int main()
{
	//declare global variables for the whole program
	//values for player 1 and player 2
	char player1 = 0; //player
	char player2 = 0; //computer

	//score for player 1 and player 2  
	int score1 = 0; 
	int score2  = 0;

	//itterate to play the game ten times 
	for(int i = 0; i<10; i++)
	{
		//get the input from the user
		printf("Enter R for rock, P for paper, or S for scissors:");
		scanf(" %c", &player1);
		
		//convert it to uppercase if they put in a lowercase
		player1  = toupper(player1);
		printf("\n");

		//check to see if the user input a valid character, if not get it again
		if(player1 != 'R' && player1 != 'P' && player1 != 'S')
		{
			printf("Please enter a valid choice:\n");
			scanf(" %c", &player1);
			player1 = toupper(player1);
		} 

		//get a random value for player2
		player2 = rand()%3+1;
		
		//map the values from 1 to 3 to R P or S
		switch(player2)
		{
			case 1:
				player2 = 'R';
				break;
			case 2:
				player2 = 'P';
				break;
			case 3:
				player2 = 'S';
				break;
		}

		//now compare
		//check to see if player 1 won
		if((player1 == 'R' && player2 == 'S' ) || (player1 == 'P' && player2 == 'R') || (player1 == 'S' && player2 == 'P'))
		{
			printf("Player 1 has %c and Player 2 has %c. Player 1 wins!\n\n", player1, player2);
			score1++;  

		//now check to see if player 2 won
		}else if((player2 == 'R' && player1 == 'S') || (player2 == 'P' && player1 == 'R') || (player2 == 'S' && player1 == 'P'))
		{
	                printf("Player 1 has %c and Player 2 has %c. Too bad. Player 2 wins\n\n", player1, player2);
                        score2++; 		

		//now check to see if it was a tie
		}else if(player1 == player2){
			printf("It's a tie! Play again\n\n");
		}		
	}

	//once all ten games have been played check to see who has won
	//print the scores of the two players
	printf("Player 1 has score %d\nPlayer 2 has score %d\n", score1, score2);

	//now compare to see the results
	if(score1 > score2){
		printf("Player 1 wins!\n\n");
	}else if(score1 < score2){
		printf("Player 2 wins!\n\n");
	}else if(score1 == score2){
		printf("It's a tie!\n\n");
	}
	return 0;
}
