#include <stdio.h>
#include <pic32mx.h>
#include "function.h"


//main meny
void showmeny()
{
    display_string(0, "Meny:");
    display_string(1, "1 Play a game");
    display_string(2, "2 Highscorces");
    display_string(3, "");
    display_update();
}

//game with next block indicator
void game_array()
{
    int i, j;
    fields_to_bit_array(); //updates global variabel bitarray to current array values in the game
    block_to_bit_array();

    for(i = 0; i < 4; i++)
    {
        COMMAND_MODE;
        send_byte_spi(0x22);
        send_byte_spi(i);

        send_byte_spi(0x0);
        send_byte_spi(0x10);

        DATA_MODE;
        for(j = 0; j < 128; j++) 
        {
            if(j < 60)
            {
                send_byte_spi(bitarray[i][j]);
            }
            else if(j == 60)
            {
                send_byte_spi(0xFF);
            }
            else if(j > 70 && (i == 1 || i == 2))
            {
                send_byte_spi(block_bitarray[i][j - 71]);
            }
            else
            {
                send_byte_spi(0x00);
            }                
        }
    }
    
}


void game_over()
{
    //animation of everything being filld with white
    int i, j;
    for(i = 0; i < 4; i++)
    {
        COMMAND_MODE;
        send_byte_spi(0x22);
        send_byte_spi(i);
        
        send_byte_spi(0x0);
        send_byte_spi(0x10);
        DATA_MODE;
        for(j = 0; j < 60; j++)
        {
            send_byte_spi(0xff);
            delay(1000);
        }
    }
    
}

//meny after gamover
void name_meny()
{
    clearscreen();
    display_string(0, "Enter a name:");
    display_string(1, "A A A");
    display_string(2, "");
    display_string(3, "Use btns 3 2 1");
    display_update();
    char letters[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char name[3] = {'A', 'A', 'A'};
    int CurrentA, CurrentB, CurrentC = 0;
    char flag = 1;
    while (flag)
    {
        int buttons = getbtn();// need a delay, its updating to quickly
        if(buttons >> 2 & 0x1) //1# letter
        {
            if(CurrentA < 25 && CurrentA >= 0)
            {
                CurrentA++;
            }
            else{
                CurrentA = 0;
            }
            name[0] = letters[CurrentA];
        }
        if(buttons >> 1 & 0x1) //2# letter
        {
            if(CurrentB < 25 && CurrentB >= 0)
            {
                CurrentB++;
            }
            else{
                CurrentB = 0;
            }
            name[1] = letters[CurrentB];
        }
        if(buttons & 0x1) //3# letter increment
        {
            if(CurrentC < 25 && CurrentC >= 0)
            {
                CurrentC++;
            }
            else{
                CurrentC = 0;
            }
            name[2] = letters[CurrentC];
        }
        if(buttons >> 3 & 0x1) //Exit setting, btn4
        {
            flag = 0;
            break;
        }
        display_string(1, (name));
        display_update();
    }
    update_scores(highscore, name);
    PORTE = 1; //Go to main menu
}