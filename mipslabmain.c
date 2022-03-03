#include <stdint.h> /* Declarations of uint_32 and the like */
#include <stdlib.h>
#include <stdio.h>
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "function.h"

#define ToMENY (directory = 1)
#define ToGAME (directory = 2)
#define ToEND (directory = 4)
#define ToNAME (directory = 8)
#define ToHIGHSCORE (directory = 16)
#define ToEgg (directory = 32)

#define AtMENY (directory == 1)
#define AtGAME (directory == 2)
#define AtEND (directory == 4)
#define AtNAME (directory == 8)
#define AtHIGHSCORE (directory == 16)
#define AtEgg (directory == 32)

int counter = 0;
int btns;

// PORTE as a global game directory
// 1 = meny
// 2 = game
// 4 = endscreen
// 8 = name meny
// 16 = show top 3 highscore
int main(void)
{
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

	// program starts here
	while (1)
	{	
		ToMENY;
		btns = getbtn();
		if (btns & 0x1)
		{
			// initialize game field
			highscore = 0;
			startupReset();
			ToGAME;
			while(AtGAME);
			while(AtEND);
			while(AtNAME);

		}
		else if (btns >> 1 & 0x1)
		{
			ToHIGHSCORE;
			while(AtHIGHSCORE);
		}
		else if (btns >> 2 & 0x1){
			ToEgg;
			while(AtEgg);
		}
	}
	return 0;
}
void user_isr(void)
{
	if (IFS(0) & 0x100) // when T2 gives a interupt flag
	{
		counter += 1;
		if (AtMENY)
		{
			showmeny();
		}
		if (AtGAME)
		{
			if (counter % 10 == 0)
			{
				btns = getbtn();
				if (btns & 0x1)
				{
					//rotate
					rotate();
				}
				else if (btns >> 1 & 0x1)
				{
					//move right
					moveRight();
				}
				else if (btns >> 2 & 0x1)
				{
					//move left
					moveLeft();
				}
				else if (btns >> 3 & 0x1)
				{
					//move down
					moveDown();
					highscore += (level + 1);
				}
				getDisplay();
				game_array();
			}
			
			if (counter % (80-8*level) == 0)
			{
				if(highscore >= ((level+1)*(level+1)*100) && level < 9){
					level +=1;
				}
				moveDown();
				getDisplay();
				game_array();
				// update date the game with new values after, function game_array()
				// should check points and update the speed accordingly
				// check buttons and use moveLeft, moveRight, moveDown accordingly
				// do neccesary checks to update the logical array, this is for the game_array to update the Display correctly
				counter = 0;
			}
			char string_score[8];
			int curnint = highscore;
			int i;
			for(i = 7; i >= 0; i--)
			{
				string_score[i] = curnint % 10 + '0';
				curnint /= 10;
			}
			print_lcd("string");
		}
		if (AtEND)
		{
			game_over();
			delay(1000);
			ToNAME;
		}
		if (AtHIGHSCORE)
		{
			// show highscore
			show_highscores();
			btns = getbtn();
			if(btns >> 3 & 1)
			{
				ToMENY;
			}
		}
		if (AtNAME)
		{
			name_meny();
			
			ToMENY;
		}
		if(AtEgg){
			show_egg();
			btns = getbtn();
			if(btns >> 3 & 1){
				ToMENY;
			}
		}
		IFSCLR(0) = 0x100;
	}
}
