/* header file for functions in this file */
#include <stdint.h>
#define COMMAND_MODE (PORTFCLR = 0x10)
#define DATA_MODE (PORTFSET = 0x10)

unsigned char bitarray[4][60];
unsigned char block_bitarray[2][24];

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

// this part of code comes from Lab3, not ours!
const uint8_t font[128*8];
char textbuffer[4][16];
char *itoaconv(int num);

//for highscore
char highscoreString[3][16]; //like textbuffert, 16 characters long
int scorces[3];
char names[3][3];
void update_scores(int score, char* name);

//for screens
void showmeny();
void game_array();
void show_nextblock();
void name_meny();

//game logic
#define ROW 20
#define COL 10
char displayField[ROW][COL];
int highscore = 0;
int level = 0;

char CurrentPiece[5][5] = {
    {'0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0'}};

char nextPiece[5][5] = {
    {'0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0'}};

//functions:
void placeBlock();
void removeBlock();
void replaceArray(char arrayA[5][5], char arrayB[5][5]);
void pickBlock(char block[5][5]);
void newBlock();
void moveLeft();
void moveRight();
void moveDown();
void rotate();
void getDisplay();
void displayTest();
void startupReset();

