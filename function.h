/* header file for functions in this file */
#define COMMAND_MODE (PORTFCLR = 0x10)
#define DATA_MODE (PORTFSET = 0x10)

char getbtn();
int delay(int ms);
unsigned char send_byte_spi(unsigned char bytesToSend);
unsigned char buffert_send128(unsigned char *data);
void update_display_to(unsigned char *array);
void update_display(void);
void display_string(int line, char *s);
void clearscreen();
void initIoPorts();
void intiOled();
void init();
void enable_interrupt();

// this part of code comes from Lab3, not ours!
const uint8_t font[128*8];
char textbuffer[4][16];
char *itoaconv(int num);

//for highscore
char highscoreString[3][16]; //like the text buffert, 16 characters long
int scorces[3];
char names[3][3];
void update_scores(int score, char* name);