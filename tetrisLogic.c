#include <stdio.h>
#include <stdlib.h>
#include <pic32mx.h>
#include "function.h"


#define MARGIN 2

// define the starting point (where blocks will be created)
#define startR 1
#define startC 5

char Field[ROW + (2 * MARGIN)][COL + (2 * MARGIN)];
int pos[2] = {startR, startC};

void placeBlock()
{
    int r, c;
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            if (CurrentPiece[r][c] == '1')
            {
                Field[pos[0] + r - 2 + MARGIN][pos[1] + c - 2 + MARGIN] = '1';
            }
        }
    }
}

void removeBlock()
{
    int r, c;
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            if (CurrentPiece[r][c] == '1')
            {
                Field[pos[0] + r - 2 + MARGIN][pos[1] + c - 2 + MARGIN] = '0';
            }
        }
    }
}

void replaceArray(char arrayA[5][5], char arrayB[5][5])
{
    int r, c;
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            arrayA[r][c] = arrayB[r][c];
        }
    }
}

// block register/picker
void pickBlock(char block[5][5])
{

    int random = rand() % 7;
    switch (random)
    {
    case 0:;
        char newBlockTypeZ[5][5] = {
            {'0', '0', '0', '0', '0'},
            {'0', '1', '1', '0', '0'},
            {'0', '0', '1', '1', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}};
        replaceArray(block, newBlockTypeZ);
        break;
    case 1:;
        char newBlockTypeT[5][5] = {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '1', '1', '1', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}};
        replaceArray(block, newBlockTypeT);
        break;
    case 2:;
        char newBlockTypeS[5][5] = {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '1', '1', '0'},
            {'0', '1', '1', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}};
        replaceArray(block, newBlockTypeS);
        break;
    case 3:;
        char newBlockTypeO[5][5] = {
            {'0', '0', '0', '0', '0'},
            {'0', '1', '1', '0', '0'},
            {'0', '1', '1', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}};
        replaceArray(block, newBlockTypeO);
        break;
    case 4:;
        char newBlockTypeL[5][5] = {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '1', '0'},
            {'0', '1', '1', '1', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}};
        replaceArray(block, newBlockTypeL);
        break;
    case 5:;
        char newBlockTypeJ[5][5] = {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '1', '1', '1', '0'},
            {'0', '0', '0', '1', '0'},
            {'0', '0', '0', '0', '0'}};
        replaceArray(block, newBlockTypeJ);
        break;
    case 6:;
        char newBlockTypeI[5][5] = {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'1', '1', '1', '1', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}};
        replaceArray(block, newBlockTypeI);
        break;

    default:;
        break;
    }
}

void newBlock()
{
    int r, c;
    pos[0] = startR;
    pos[1] = startC;
    int alive = 1;
    // check that position is not allready filled
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            if (CurrentPiece[r][c] == '1' && Field[pos[0] + r - 2 + MARGIN][pos[1] + c - 2 + MARGIN] == '1')
            {
                alive = 0;
            }
        }
    }
    if (alive == 1)
    {
        placeBlock();
    }
    else
    {
        // proper game over function needed:
        display_string(1, "Game over!");
        display_string(2, "Enter name:");
    }
}

void moveLeft()
{
    int r, c;
    // remove the block:
    removeBlock();
    int obstruct = 0;
    // obstruction handler:
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            if (CurrentPiece[r][c] == '1' && Field[pos[0] + r - 2 + MARGIN][pos[1] + c - 3 + MARGIN] == '1')
            {
                obstruct = 1;
            }
        }
    }

    if (obstruct == 0)
    {
        // alter position
        pos[1] = pos[1] - 1;
    }
    // place the block:
    placeBlock();
}

void moveRight()
{
    int r, c;
    // remove the block:
    removeBlock();
    int obstruct = 0;
    // obstruction handler:
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            if (CurrentPiece[r][c] == '1' && Field[pos[0] + r - 2 + MARGIN][pos[1] + c - 1 + MARGIN] == '1')
            {
                obstruct = 1;
            }
        }
    }

    if (obstruct == 0)
    {
        // alter position
        pos[1] = pos[1] + 1;
    }
    // place the block:
    placeBlock();
}

void moveDown()
{
    int r, c, moveRows, moveColumns;
    // remove the block:
    removeBlock();
    // Obstruction handler
    int obstruct = 0;
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            if (CurrentPiece[r][c] == '1' && Field[pos[0] + r - 1 + MARGIN][pos[1] + c - 2 + MARGIN] == '1')
            {
                obstruct = 1;
            }
        }
    }
    if (obstruct == 0)
    {
        // alter position
        pos[0] = pos[0] + 1;
        // place the block:
        placeBlock();
    }

    else
    {
        // replace the block:
        placeBlock();
        // block has reached the bottom
        // 1. check full rows and move down
        // 2. give points
        // 3. new block

        // 1.
        int checkRows = 0;
        // go through all rows
        for (r = MARGIN; r < ROW + MARGIN; r++)
        {
            // check for filled space
            if (Field[r][0] == '1')
            {
                // check for full row
                int checkColumns = 0;
                for (c = MARGIN; c < COL + MARGIN; c++)
                {
                    if (Field[r][c] == '1')
                    {
                        checkColumns++;
                    }
                }
                // if full row is found
                if (checkColumns == COL)
                {
                    // move all rows above, down one row (remove the full row)
                    checkRows++;
                    for (moveRows = r; moveRows > MARGIN; moveRows--)
                    {
                        for (moveColumns = MARGIN; moveColumns < COL + MARGIN; moveColumns++)
                        {
                            Field[moveRows][moveColumns] = Field[moveRows - 1][moveColumns];
                        }
                    }
                }
            }
        }
        // 2.
        // Award points for number of rows removed
        switch (checkRows)
        {
        case 1:;
            highscore += 40 * (level + 1);
            break;
        case 2:;
            highscore += 100 * (level + 1);
            break;
        case 3:;
            highscore += 300 * (level + 1);
            break;
        case 4:;
            highscore += 1200 * (level + 1);
            break;
        default:;
            break;
        }
        // 3.
        // Create new block
        replaceArray(CurrentPiece, nextPiece);
        newBlock();
        pickBlock(nextPiece);
    }
}

// This will rotate the shape of the block clockwise 90 degrees
void rotate()
{
    int r, c;
    // remove the block:
    removeBlock();
    // alter rotation:
    char newRotation[5][5];
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            newRotation[r][c] = CurrentPiece[4 - c][r];
        }
    }
    // Obstruction checker:
    int obstruct = 0;
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            if (newRotation[r][c] == '1' && Field[pos[0] + r - 2 + MARGIN][pos[1] + c - 2 + MARGIN] == '1')
            {
                obstruct = 1;
            }
        }
    }

    if (obstruct == 0)
    {
        replaceArray(CurrentPiece, newRotation);
    }

    // place the block:
    placeBlock();
}

void getDisplay()
{
    int r, c;
    for (r = 0; r < ROW; r++)
    {
        for (c = 0; c < COL; c++)
        {
            displayField[r][c] = Field[r + MARGIN][c + MARGIN];
        }
    }
}

// Following function is only for terminal testiing purpouses:
void displayTest()
{
    // int r, c;
    // for (r = MARGIN; r < ROW + MARGIN; r++)
    // {
    //     for (c = MARGIN; c < COL + MARGIN; c++)
    //     {
    //         printf("%c", Field[r][c]);
    //     }
    //     printf("\n");
    // }
    // printf("----------\n");
}

void startupReset()
{
    int r, c;
    // reset the playing field
    for (r = 0; r < ROW + 2 * MARGIN; r++)
    {
        for (c = 0; c < COL + 2 * MARGIN; c++)
        {
            if (r < MARGIN || r >= ROW + MARGIN || c < MARGIN || c >= COL + MARGIN)
            {
                Field[r][c] = '1';
            }
            else
            {
                Field[r][c] = '0';
            }
        }
    }
    // get new pieces
    pickBlock(CurrentPiece);
    pickBlock(nextPiece);
}

// void manualStart()
// {
//     srand(TMR2);
//     startupReset();

// }
