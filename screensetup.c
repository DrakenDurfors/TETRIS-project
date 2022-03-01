#include <stdio.h>
#include <pic32mx.h>
#include "function.h"


//main meny
void showmeny()
{
    display_string(0, "Meny:");
    display_string(1, "0 Play a game");
    display_string(2, "1 Highscorces");
    display_string(3, "");
    display_update();
}

//game with next block indicator
void game_array()
{
    int i, j;
    //fields_to_bit_array(); //updates global variabel bitarray 
    for(i = 0; i < 4; i++) //chose page1 and page2
    {
        COMMAND_MODE;
        send_byte_spi(0x22);
        send_byte_spi(i);

        send_byte_spi(0x0);
        send_byte_spi(0x10);

        DATA_MODE;
        for(j = 0; j < 128; j++) 
        {
            if(j < 70)
            {
                send_byte_spi(bitarray[i][j-1]);
            }
            else if(j == 70)
            {
                send_byte_spi(0xFF);
            }
            else
            {
                send_byte_spi(0x00);
            }                
        }
    }
    show_nextblock();
}

//nextblock indicator, 
void show_nextblock()
{
    int x = 96;
    int i, j;
    for (i = 1; i < 3; i++)
    {
        COMMAND_MODE;
        send_byte_spi(0x22);
        send_byte_spi(i);

        //This code part comes from the display_image function from lab3
        send_byte_spi(x & 0xF); 
		send_byte_spi(0x10 | ((x >> 4) & 0xF));
        for(j = 0; j < 32; j++)
        {
            if(j > 8 && j < 25)
            {
                send_byte_spi(block_bitarray[i-1][j-1]);
            }
            else if(j == 8 || j == 25)
            {
                send_byte_spi(0xff);
            }
            else
            {
                send_byte_spi(0x0);
            }

        }
    }
}

//meny after gamover
void name_meny()
{
    
}