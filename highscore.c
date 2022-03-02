#include <stdio.h>
#include <pic32mx.h>
#include "function.h"

/* update the current 3 highscores according to their value */
void update_scores(int score, char *name)
{
    int tempscore;
    char tempname[3];
    int n = 0;
    int m;
    while (n < 3)
    {
        if (score > scorces[n])
        {
            // change the score in appropiate place
            tempscore = scorces[n];
            scorces[n] = score;
            score = tempscore; // update score, old scores should be moved down

            // change the characters (in the name) in appropiate places
            for (m = 0; m < 3; m++)
            {
                tempname[m] = names[n][m];
                names[n][m] = name[m];
                name[m] = tempname[m]; // update name, old names should also move down
            }
        }
        n++;
    }
}

// local to this file, update the current name scores in
void conv_highscore_string()
{
    char stringRepres[12];
    int i, j, k, n, tempint;
    for (i = 0; i < 3; i++)
    {
        // digit to ascii
        tempint = scorces[i];
        for (n = 11; n >= 0; n--)
        {
            stringRepres[n] = (tempint %10) + '0';
            tempint /= 10;
        }

        // get each character first
        for (j = 0; j < 3; j++)
        {
            highscoreString[i][j] = names[i][j];
        }
        highscoreString[i][3] = ' '; // example at this point "AAA "
        for (k = 4; k < 16; k++)
        {
            highscoreString[i][k] = stringRepres[k - 4];
        }
    }
}
void show_highscores()
{
    conv_highscore_string(); // updates highscore,
    display_string(0, "Highscores:");
    char temp[17];
    int i, j;
    for (j = 0; j < 3; j++)
    {
        for (i = 0; i < 16; i++)
        {
            temp[i] = highscoreString[j][i];
        }
        display_string((j + 1), temp);
    }
    display_update();
}

// may implement I2C to write-to-memory and ready-from-memory