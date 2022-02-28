#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "function.h" 

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
	display_string(1, "LETS PLAY TETRIS");
	display_update();

	int btns;
	while(1)
	{
		btns = getbtn();
		if(btns & 0x1)
		{
			//btn1 action from main menu
		}
		else if(btns >> 1 & 0x1)
		{
			//btn2 action from main menu
		}
		else if(btns >> 2 & 0x1)
		{
			//btn3 action from main menu
		}
		else if(btns >> 3 & 0x1)
		{
			//btn4 action from main menu
		}
	}
	return 0;
}
