#include <stdio.h>
#include <pic32mx.h>
#include "function.h"

//only 3 since we only have 4 pages to display text on
//first page for "Highscores"
int scorces[3];
char names[3][3];


/* update the current 3 highscores according to their value */
void update_scores(int score, char* name)
{
    int iterimscore;
    char iterimname[3];
    int n,m;
    for(n = 0; n < 3; n++)
    {
        if(score > scorces[n])
        {
            //change the score in appropiate place
            iterimscore = scorces[n];
            scorces[n] = score;

            //change the characters (in the name) in appropiate places
            for(m = 0; m < 3; m++) 
            {
                iterimname[m] =  names[n][m];
                names[n][m] = name[m];
            }
        }
    }
}

void conv_highscore_string()
{
    char* stringRepres;
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        //get each character first
        for(j = 0; j < 3; j++)
        {
            highscoreString[i][j] = names[i][j];
        }
        highscoreString[i][3] = " "; //example at this point "AAA "
        stringRepres = itoaconv(scorces[i]);
        for(k = 4; k < 16; k++)
        {
            highscoreString[i][k] = stringRepres[k - 4];
        }
    }
}


//may implement I2C to write-to-memory and ready-from-memory 