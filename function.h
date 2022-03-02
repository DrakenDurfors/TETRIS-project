/* header file for functions in this file */
#include <stdint.h>
#define COMMAND_MODE (PORTFCLR = 0x10)
#define DATA_MODE (PORTFSET = 0x10)


//game logic
#define ROW 20
#define COL 10
char displayField[ROW][COL];
int highscore;
int level;

char CurrentPiece[5][5];

char nextPiece[5][5];

//game logic functions:
void placeBlock(); //
void removeBlock(); //
void replaceArray(char arrayA[5][5], char arrayB[5][5]); //
void pickBlock(char block[5][5]); //
void newBlock(); //
void moveLeft();
void moveRight();
void moveDown();
void rotate();
void getDisplay();
void displayTest(); //
void startupReset();




unsigned char bitarray[4][60];
unsigned char block_bitarray[2][24];

//for SPI, Display and misc
char getbtn();
int delay(int ms);
unsigned char send_byte_spi(unsigned char bytesToSend);
unsigned char buffert_send128(unsigned char *data);
void update_display_to(unsigned char *array);
void display_update(void);
void display_debug( volatile int * const addr );
void display_string(int line, char *s);
void clearscreen();
void initIoPorts();
void initOled();
void init();
void enable_interrupt(void);
void fields_to_bit_array();
void block_to_bit_array();
static void num32asc( char * s, int n );

// this part of code comes from Lab3, not ours!
const uint8_t font[128*8];
char textbuffer[4][16];
char *itoaconv(int num);

//for highscore
char highscoreString[3][16]; //like textbuffert, 16 characters long, only 3 since we only have 4 pages to display text on
int scorces[3];
char names[3][3];
void update_scores(int score, char* name);
void show_highscores();

//for screens
void showmeny();
void game_array();
void show_nextblock();
void name_meny();


