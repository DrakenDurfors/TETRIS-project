#include <stdio.h>
#include <pic32mx.h>
#include "function.h"


//CODE descriptions supplied by HARRIS&HARRIS, implemented 
void lcdInit()
{
    TRISDCLR = 0xE; //sets to 1110
    PORTD = 0x0;

    delay(16000);
    lcdwrite(0x30, Inst); //to 8-bit mode
    delay(5000);
    lcdwrite(0x30, Inst); //repeat
    delay(100);
    lcdwrite(0x30, Inst); //repeat
    wait_lcd();
    lcdwrite(0x3C, Inst); //set 2 lines, 5x8 font
    wait_lcd();
    lcdwrite(0x08, Inst); //turn display off
    wait_lcd();
    lcd_clear();
    lcdwrite(0x06, Inst); // set to increment the cursor position
    wait_lcd();
    lcdwrite(0x0C, Inst); //turn display on and turn off cursor
    wait_lcd();
}
void lcdwrite(char content, mode md)
{
    TRISE = 0xFF00;
    PORTD = 0b0010 | md << 2;
    PORTE = content << 8;
    PORTDSET = 0b1000;
    PORTD = 0b1000; //turn on the pulse to send the content of PORTE to the LCD
    delay(20);
    PORTDCLR = 0b1000; //stop sending
    delay(20);
}
char lcdread()
{
    char content;
    TRISE = 0xFFFF;
    PORTD = 0b1010;
    delay(20);
    content = PORTE & 0x00FF;
    PORTD = 0b0110;
    delay(20);
    return content;
}
void wait_lcd()
{
    char state;
    do{
        state = lcdread();
    } while (state & 0x80);
}
char print_lcd(char *str)
{
    while(*str != 0) 
    {
        lcdwrite(*str, Data); // print this character
        wait_lcd();
        str++; // advance pointer to next character in string
    }
}
void lcd_clear()
{
    lcdwrite(0x01, Inst); // clear - display command
    lcdwrite(0x02, Inst);
    delay(1600); // wait until done
}
