#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdlib.h>
#include <stdio.h>
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "function.h" 

#define ToMENY (PORTE = 1)
#define ToGAME (PORTE = 2)
#define ToEND (PORTE = 4)
#define ToNAME (PORTE = 8)
#define ToHIGHSCORE (PORTE = 16)
#define AtMENY (PORTE == 1)
#define AtGAME (PORTE == 2)
#define AtEND (PORTE == 4)
#define AtNAME (PORTE == 8)
#define AtHIGHSCORE (PORTE == 16)
int counter = 0;
int btns; 
//PORTE as a global game directory
//1 = meny
//2 = game
//4 = endscreen
//8 = name meny
//16 = show top 3 highscore
int main(void) {
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* initialize SPI and neccessery ports*/
	TRISECLR = 0xff;
	init();
	display_string(1, "LETS PLAY TETRIS");
	display_update();
	delay(100000);
	
	//program starts here
	ToMENY;
	while(1)
	{		
		
		ToMENY;
		btns = getbtn();
		if(btns & 0x1)
		{
			//make first time setup for the game, then use interupts to keep the game alive
			//write setup here
			game_over();
			delay(1000);
			//play a game, makes the if statement with PORTE == 2 in user_isr active with command below
			// PORTE = 2;
			while(AtGAME);
			//PR2 = (80000000/256)/20; //orignal value;
			
			//Game over? show game over screen, then name_meny() lastly

		}
		else if(btns >> 1 & 0x1)
		{
			//btn2 action from main menu
			ToHIGHSCORE;

		}
	}
	return 0;
}
void user_isr( void )
{
	if(IFS(0) & 0x100) //when T2 gives a interupt flag
	{
		counter += 1;
		if(AtMENY)
		{	
			showmeny();
		}
		if(AtGAME)
		{
			if(counter = 20)
			{
				game_array;
				//update date the game with new values after, function game_array()
				//should check points and update the speed accordingly
				//check buttons and use moveLeft, moveRight, moveDown accordingly
				//do neccesary checks to update the logical array, this is for the game_array to update the Display correctly
				//if(PORTE == 4)
				//{ 
				//	game_over();
				//  delay(1000);
				//  ToMENY;
				//}
			}
		}
		if(AtHIGHSCORE)
		{
			//show highscore
			display_string(0, "Highscores:");
			display_string(1, highscoreString[0]);
			display_string(2, highscoreString[1]);
			display_string(3, highscoreString[2]);
			display_update();
			if(btns >> 1 & 1)
			{
				ToMENY;
			}
		}
		if(AtNAME)
		{
			name_meny();
		}
		IFSCLR(0) = 0x100;
	}
}
