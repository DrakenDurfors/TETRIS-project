#include <stdio.h>
#include <pic32mx.h>
#include "function.h"

/* update the current 3 highscores according to their value */
void update_scores(int score, char* name)
{
    int n = 0;
    int m;
    while(n < 3)
    {
        if(score > scorces[n])
        {   
            //change the score in appropiate place
            scorces[n] = score;

            //change the characters (in the name) in appropiate places
            for(m = 0; m < 3; m++) 
            {
                names[n][m] = name[m];
            }
            n = 2; //end while loop, we have found the score thats to be replaced
        }
        n++;
    }
}

//local to this file, update the current name scores in 
void conv_highscore_string()
{
    char* stringRepres;
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        //digit to ascii
        stringRepres = itoaconv(scorces[i]);
        
        //get each character first
        for(j = 0; j < 3; j++)
        {
            highscoreString[i][j] = names[i][j];
        }
        //highscoreString[i][3] = " "; //example at this point "AAA "
        for(k = 4; k < 16; k++)
        {
            highscoreString[i][k] = stringRepres[k - 4];
        }
    }
}
void show_highscores()
{
    conv_highscore_string(); //updates highscore, 
	display_string(0, "Highscores:");
	display_string(1, highscoreString[0]);
	display_string(2, highscoreString[1]);
	display_string(3, highscoreString[2]);
}



//may implement I2C to write-to-memory and ready-from-memory 