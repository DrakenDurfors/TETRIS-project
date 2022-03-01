#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "function.h" 
int counter = 0;
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
	init();
	TRISECLR = 0xff;
	display_string(1, "LETS PLAY TETRIS");
	display_update();
	delay(100000);
	showmeny();

	int btns;
	while(1)
	{
		btns = getbtn();
		if(btns & 0x1)
		{
			//update display to the game
			
		}
		else if(btns >> 1 & 0x1)
		{
			//btn2 action from main menu
			
		}
	}
	return 0;
}
void user_isr( void )
{
	if(IFS(0) & 0x100 && 1)
	{
		//Check buttons and maybe count to 
		counter++;
		if(counter == 10)
		{
			counter = 0;
		}
		IFSCLR(0) = 0x100;
	}
}
