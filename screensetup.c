#include <stdio.h>
#include <pic32mx.h>
#include "function.h"

// main meny
void showmeny()
{
    display_string(0, "Meny:");
    display_string(1, "1 Play a game");
    display_string(2, "2 Highscorces");
    display_string(3, "");
    display_update();
}

// game with next block indicator
void game_array()
{
    int i, j;
    fields_to_bit_array(); // updates global variabel bitarray to current array values in the game
    block_to_bit_array();

    for (i = 0; i < 4; i++)
    {
        COMMAND_MODE;
        send_byte_spi(0x22);
        send_byte_spi(i);

        send_byte_spi(0x0);
        send_byte_spi(0x10);

        DATA_MODE;
        for (j = 0; j < 128; j++)
        {
            if (j < 60)
            {
                send_byte_spi(bitarray[i][j]);
            }
            else if (j == 60)
            {
                send_byte_spi(0xFF);
            }
            else if (j >= 71 && (i == 1 || i == 2) && j <= 86)
            {
                send_byte_spi(block_bitarray[i - 1][j - 71]);
            }
            else if (j >= 69 && j <= 88 && i == 0)
            {
                send_byte_spi(0x80);
            }
            else if (j >= 69 && j <= 88 && i == 3)
            {
                send_byte_spi(0x03);
            }
            else if ((j == 70 || j == 69 || j == 87 || j == 88) && (i == 1 || i == 2))
            {
                send_byte_spi(0xff);
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
    // animation of everything being filld with white
    int i, j;
    for (i = 0; i < 4; i++)
    {
        COMMAND_MODE;
        send_byte_spi(0x22);
        send_byte_spi(i);

        send_byte_spi(0x0);
        send_byte_spi(0x10);
        DATA_MODE;

        for (j = 0; j < 128; j++)
        {
            if (j < 61)
            {
                send_byte_spi(0xff);
                delay(250);
            }
            else if (j > 60 && j % 8 == 0)
            {
                send_byte_spi(0x0);
                delay(250);
            }
            else if (j > 60 && j % 8 == 1)
            {
                send_byte_spi(0b00101010);
                delay(250);
            }
            else if (j > 60 && j % 8 == 2)
            {
                send_byte_spi(0b00111110);
                delay(250);
            }
            else if (j > 60 && j % 8 == 3)
            {
                send_byte_spi(0b01110111);
                delay(250);
            }
            else if (j > 60 && j % 8 == 4)
            {
                send_byte_spi(0b01111111);
                delay(250);
            }
            else if (j > 60 && j % 8 == 5)
            {
                send_byte_spi(0b01001001);
                delay(250);
            }
            else if (j > 60 && j % 8 == 6)
            {
                send_byte_spi(0b01001001);
                delay(250);
            }
            else if (j > 60 && j % 8 == 7)
            {
                send_byte_spi(0b00111110);
                delay(250);
            }
            else
            {
                send_byte_spi(0x0);
            }
        }
    }
    DATA_MODE;
    display_string(0, "");
    display_string(1, " ");
    display_string(2, "  <3");
    display_string(3, "");
    display_update();
    delay(10000);
    COMMAND_MODE;
    send_byte_spi(0xA7);
    delay(10000);
    COMMAND_MODE;
    send_byte_spi(0xA6);
    delay(10000);
    COMMAND_MODE;
    send_byte_spi(0xA7);
    delay(10000);
    DATA_MODE;
    display_string(2, "  <\\3");
    display_update();
    delay(10000);
    COMMAND_MODE;
    delay(10000);
    send_byte_spi(0xA6);
    DATA_MODE;
}

// meny after gamover
void name_meny()
{
    clearscreen();
    display_string(0, "Enter a name:");
    display_string(1, "A A A");
    display_string(2, "");
    char text3[16] = "Score:         "; // these must be equal lenght, on both side
    int tempint = highscore;
    int i;
    for (i = 15; i >= 8; i--) // konvertera highscore till ASCII
    {
        text3[i] = (tempint % 10) + '0';
        tempint /= 10;
    }
    display_string(3, text3);
    display_update();
    char letters[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char name[3] = {'A', 'A', 'A'};
    int CurrentA, CurrentB, CurrentC = 0;
    char flag = 1;
    while (flag)
    {
        int buttons = getbtn(); // need a delay, its updating to quickly
        if (buttons >> 2 & 0x1) // 1# letter
        {
            if (CurrentA < 25 && CurrentA >= 0)
            {
                CurrentA++;
            }
            else
            {
                CurrentA = 0;
            }
            name[0] = letters[CurrentA];
        }
        if (buttons >> 1 & 0x1) // 2# letter
        {
            if (CurrentB < 25 && CurrentB >= 0)
            {
                CurrentB++;
            }
            else
            {
                CurrentB = 0;
            }
            name[1] = letters[CurrentB];
        }
        if (buttons & 0x1) // 3# letter increment
        {
            if (CurrentC < 25 && CurrentC >= 0)
            {
                CurrentC++;
            }
            else
            {
                CurrentC = 0;
            }
            name[2] = letters[CurrentC];
        }
        if (buttons >> 3 & 0x1) // Exit setting, btn4
        {
            flag = 0;
            break;
        }
        display_string(1, (name));
        display_update();
    }
    update_scores(highscore, name);
}
void show_egg()
{
    int j, i, t;
    for (i = 0; i < 4; i++)
    {

        COMMAND_MODE;
        send_byte_spi(0x22);
        send_byte_spi(i);

        send_byte_spi(0x0);
        send_byte_spi(0x10);
        DATA_MODE;
        t = 0;
        for (j = 0; j < 128; j++)
        {
            if (j > 56 && j < 71 && (i == 1 || i == 2))
            {
                if (i == 1)
                {
                    if (t == 0)
                    {

                        send_byte_spi(0b10000000);
                    }
                    else if (t == 1)
                    {

                        send_byte_spi(0b11100000);
                    }
                    else if (t == 2)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b00010000);
                        }
                        else
                        {
                            send_byte_spi(0b00011000);
                        }
                    }
                    else if (t == 3)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b10100000);
                        }
                        else
                        {
                            send_byte_spi(0b00111100);
                        }
                    }
                    else if (t == 4)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b01000000);
                        }
                        else
                        {
                            send_byte_spi(0b00111110);
                        }
                    }
                    else if (t == 5)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b01100000);
                        }
                        else
                        {
                            send_byte_spi(0b10011101);
                        }
                    }
                    else if (t == 6)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b10100000);
                        }
                        else
                        {
                            send_byte_spi(0b10000001);
                        }
                    }
                    else if (t == 7)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b11000000);
                        }
                        else
                        {
                            send_byte_spi(0b10000001);
                        }
                    }
                    else if (t == 8)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b00100000);
                        }
                        else
                        {
                            send_byte_spi(0b00000001);
                        }
                    }
                    else if (t == 9)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b00100000);
                        }
                        else
                        {
                            send_byte_spi(0b00111010);
                        }
                    }
                    else if (t == 10)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b01110000);
                        }
                        else
                        {
                            send_byte_spi(0b01111100);
                        }
                    }
                    else if (t == 11)
                    {
                        if (highscore > 1000)
                        {
                            send_byte_spi(0b01110000);
                        }
                        else
                        {
                            send_byte_spi(0b01111100);
                        }
                    }
                    else if (t == 12)
                    {

                        send_byte_spi(0b01110000);
                    }
                    else if (t == 13)
                    {

                        send_byte_spi(0b10000000);
                    }
                }
                if (i == 2)
                {
                    if (t == 0)
                    {
                    }
                    else if (t == 1)
                    {

                        send_byte_spi(0b00011100);
                    }
                    else if (t == 2)
                    {

                        send_byte_spi(0b00111100);
                    }
                    else if (t == 3)
                    {

                        send_byte_spi(0b01111000);
                    }
                    else if (t == 4)
                    {

                        send_byte_spi(0b01000111);
                    }
                    else if (t == 5)
                    {

                        send_byte_spi(0b10001111);
                    }
                    else if (t == 6)
                    {

                        send_byte_spi(0b10001111);
                    }
                    else if (t == 7)
                    {

                        send_byte_spi(0b10001111);
                    }
                    else if (t == 8)
                    {

                        send_byte_spi(0b10000111);
                    }
                    else if (t == 9)
                    {

                        send_byte_spi(0b01000000);
                    }
                    else if (t == 10)
                    {

                        send_byte_spi(0b01011100);
                    }
                    else if (t == 11)
                    {

                        send_byte_spi(0b00111110);
                    }
                    else if (t == 12)
                    {

                        send_byte_spi(0b00011110);
                    }
                    else if (t == 13)
                    {

                        send_byte_spi(0b00000111);
                    }
                }
                t++;
            }
            else
            {
                send_byte_spi(0x0);
            }
        }
    }
}