#include <stdio.h>
#include <pic32mx.h>
#include "function.h"

//for readability
#define VDD_ENABLE (PORTFCLR = 0x40)
#define VBAT_ENABLED (PORTFCLR = 0x20)

//predefined for oled easy-of-use
#define BUFF_SIZE_OLED (512)
#define MAX_PAGE (4) //from https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf, ours is 32 columns not 64 as stated on the website

char getbtn()
{
    char btns = 0;
    btns = (PORTD & 0xE0) >> 4;         //save buttons 4,3 and 2 to (1110) byte formation in the first nibble
    btns = btns | ((PORTF & 0x2) >> 1); //PORTF: ... 0010, 0010 >> 1 = 0001, and save this possible bit value to btns
    return btns;                        //return one nibble with the information from (and in order) button wfe4,3,2,1 
}


int delay(int ms)
{
    int timeToDelayMS = ms * 100;
    while(timeToDelayMS > 0)
    {
        timeToDelayMS--;
    }
    return 1;
}

/*Disclaimer: This is the same function "spi_send_recv" in mipslabfunc.c from Lab3 */
unsigned char send_byte_spi(unsigned char bytesToSend)
{
    while(!(SPI2STAT & 0x8)); //Check transmitter buffert if its empty then continue
    SPI2BUF = bytesToSend;    //Load and send byte to reciever of slave(OLED)
    while(!(SPI2STAT & 0x1)); //Check for the reciever buffert if its sent its information to SPI2BUF
    return SPI2BUF;
}

//Func: updates the buffert on the PIC32
//input: data, the pointer from which to write the first 128 values from 
//output: through the SPI protocol, we have sent 128 bytes of data to the SPIBuf, hardwired with the oledBuf variable
//Example: data points to a part of the oledBuf (array) and 
unsigned char buffert_send128(unsigned char *data)
{
    int index;
    for(index = 0; index < 128; index++)
    {
        //increase the unsigned char pointer to next unsigned char data value by increasing the "index" value each iteration
        send_byte_spi(data[index]);
    }
}

//update the oled to sent buffer in the PIC32
//PAGE0-PAGE3 is the whole screen. 
//update the oled to sent buffer in the PIC32
//Input: a array (or pointer) to 512 unsigned char values 
void update_display_to(unsigned char *array)
{
    unsigned char *data = array;  //points to the first unsigned char
    int current_page;
    for(current_page = 0; current_page < MAX_PAGE; current_page++)  
    {
        COMMAND_MODE;
        send_byte_spi(0x22);            //page-set command.
        send_byte_spi(current_page);    //will start att PAGE0, and for our purpose, it starts from (COM31) ROW0 until ROW31 (COM0)

        //start in left column
        send_byte_spi(0x00);
        send_byte_spi(0x10);

        DATA_MODE;
        buffert_send128(data);          //send the first 128bytes to the PAGE0 which is ROW31-ROW28, PAG1...etc

        //update pointer to the next set of 128 bytes to send
        data += 128;
    }
}

void clearscreen()
{
    char ary[512];
    DATA_MODE;
    int i;
    for(i = 0; i < 512; i++)
    {
        ary[i] = 0;
    }
    update_display_to(ary);
}

//eftersom en vi har en 20 x 10 array och skrämen är uppdelad i 69x30 
//betyder det att om en rad innehåller en etta ska 3 bitar vara ettor på displayen, därav används 0x7
//Resultatet sparas i biarray
void fields_to_bit_array()
{
    int i, j;
    int row; //32 bit, since we are shifting 3 bits 9 times 
    for(i = 0; i < 20; i++)                  
    {
        row = 1; //for showing the outline
        for(j = 9; j >= 0; j--)
        {
            row = row << 3;
            if(displayField[19-i][j] != '0')
            {
                row |= 0x7;
            }
        }
        row = row << 1; //for showing outline
        row |= 1;
        //at this point, row has the whole column value from playField with the witdh 10 translated to witdh 30;
        for(j = 0; j < 4; j++)
        {
            //effectivly writes a 3x3 block for each block in the 20x10 array in the first row
            bitarray[j][i*3] = row & 0xff;
            bitarray[j][i*3 + 1] = row & 0xff;
            bitarray[j][i*3 + 2] = row & 0xff;
            row = row >> 8; //next set of 8 bits to make a row (on the display) complete
        }
    }
}
void block_to_bit_array()
{
    int i, j, row;
    for(i = 0; i < 5; i++)
    {
        row = 0;
        for(j = 4; j >= 0; j--)
        {
            row = row << 3;
            if(nextPiece[4-i][j] != '0')
            {
                row |= 0x7;
            }
        }
        row = row << 1;
        row |= 0x1;
        for(j = 0; j < 2; j++)
        {
            block_bitarray[j][i*3] = row & 0xff;
            block_bitarray[j][i*3 + 1] = row & 0xff;
            block_bitarray[j][i*3 + 2] = row & 0xff;
            row = row >> 8;
        }
    }
}

//IO ports initilization
void initIoPorts()
{
    TRISFCLR = 0x70;    //VDD,VBAT and Data/Command ports to outputs
    TRISGCLR = 0x100;   //Reset port to output
    TRISDSET = 0xe0;    //BTN(4-2) to input
    TRISFSET = 0x2;     //BTN1 to input
}

//Oled setup initialzation
void initOled()
{    
    //Oled reset - PORTG (bit #9)
    //Oled data/command select - PORTF (bit #4)
    //Oled serial clock- PORTG (bit #5)
    //Oled serial data in - PORTG (bit #8)
    //Oled VBAT Enable - PORTF (bit #5)
    //Oled VDD Enable  - PORTF (bit #6)
    //in main, Make VDD, VBAT and DATA/COMMAND to output bits 0111 0000
    
    //start by giving commands to the display
    COMMAND_MODE; 
    delay(100);
    VDD_ENABLE; //VDD on
    delay(100);
    
    send_byte_spi(0xAE); //Screen turn off command
   
    //reset once
    PORTGCLR = 0x200;
    delay(10);
    //then turn on
    PORTGSET = 0x200;

    send_byte_spi(0x8D); //charge pump setting    
    send_byte_spi(0x14); 

    send_byte_spi(0xD9); //Pre charge Period command (meny entry)
	send_byte_spi(0xF1);

    //wait for power
    VBAT_ENABLED;
    delay(100000);

    //chose map configuration
    send_byte_spi(0xA1); // Segment, normal/[Remapped] From SEG127 to SEG0
    send_byte_spi(0xC8); // C0/[C8], normal mode/[remapped mode]. Set to Scan from COM31 - COM0

    //chose scan configuration
    send_byte_spi(0xDA); // this enters the COM pin selection (like in a meny)
    send_byte_spi(0x20); // bit 5: scan left to right (1, 0 reverse), bit 4: sequensial pin layout (1, pain), block-like pin layout (0, big chunks)

    /* turn-on display command */
    send_byte_spi(0xAF);
}

void init(){
    initIoPorts();
    lcdInit();

    /*  SPI-configuration (lab3 setup used as reference, for MODE<32,16> and CKP */
    int dataT;
    SPI2CON = 0x0;        // Reset SPI2 module
    IECCLR(1) = 0xE0;     // Turn off Interupt enable bits (7-5) and clear interuptflags
    IFSCLR(1) = 0xE0; 
    dataT = SPI2BUF;      // this clears the receive buffert (by reading it, its being cleared)
    SPI2BRG = 4;          // We will send 4096 (32 x 128) possible combination to the OLED screen
                          // SPI2BRG: 4 => baud rate: 80MHz/2([4]+1) = 8MHz 
    SPI2CONCLR = 3 << 10; // we are only sending 16 bits (MODE)
    SPI2STAT = SPI2STAT & ~0x40;   // clear SPIROV status bit, since no overflow has occurd
    SPI2CONSET = 0x20;    // bit 5 determins Master/slave operation, SPI2 is Master, hence setting bit #5 
    SPI2CONSET = 0x40;    // set clock to be active low (CKP)
    SPI2CONSET = 0x8000;  // turn on SPI module 

    //Timer2 setup
    T2CON = 0;
    T2CONSET = 0x70;    // setting prescale to 1:256
    TMR2 = 0;           // timer2 to start count from 0;
    PR2 = (80000000/256)/50; //preliminar period time of 1/20 sec 
    T2CONSET = 0x8000;  // start timer2, set bit 16

    IFSCLR(0) = 0x100; //clear potenital T2 interupt flag
    IECSET(0) = 0x100; //enable to be able interupts for T2 
    IPCSET(2) = 0x5;
    asm volatile("ei"); //assembly instruction to enable interuppts

    initOled();
}