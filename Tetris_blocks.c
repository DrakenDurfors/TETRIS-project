<<<<<<< Updated upstream
#include <stdio.h>
#include <stdlib.h>
#include <pic32mx.h> //hope we are allowed to use this library

// define the size of the 
#define ROW 20
#define COL 10
#define MARGIN 2 // pruposed attempt at dealing with any and all out of bounds issues (to be implemented)

// define the starting point (where blocks will be created)
#define startR 1
#define startC 5

// define global variables
int highscore = 0;
int level = 0;

char Field[ROW + (2 * MARGIN)][COL + (2 * MARGIN)];
char displayField[ROW][COL];
int pos[2] = {startR, startC};

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
        break;
=======
// #include <stdio.h>
// #include <stdlib.h>
// #include <pic32mx.h>

// #define ROW 20
// #define COL 10

// #define startR 1
// #define startC 5

// int highscore = 0;
// int level = 0;

// char CurrentPiece[3][3] = {
//     {'0', '0', '0'},
//     {'0', '0', '0'},
//     {'0', '0', '0'}};

// char nextPiece[3][3] = {
//     {'0', '0', '0'},
//     {'0', '0', '0'},
//     {'0', '0', '0'}};

// void clearField(char Field[][COL])
// {
//     for (int r = 0; r < ROW; r++)
//     {
//         for (int c = 0; c < COL; c++)
//         {
//             Field[r][c] = '0';
//         }
//     }
// }

// void placeBlock(char Field[][COL], char block[3][3], int pos[])
// {
//     for (int r = 0; r <= 2; r++)
//     {
//         for (int c = 0; c <= 2; c++)
//         {
//             if (block[r][c] == '1')
//             {
//                 Field[pos[0] + r - 1][pos[1] + c - 1] = '1';
//             }
//         }
//     }
// }

// void removeBlock(char Field[][COL], char block[3][3], int pos[])
// {
//     for (int r = 0; r <= 2; r++)
//     {
//         for (int c = 0; c <= 2; c++)
//         {
//             if (block[r][c] == '1')
//             {
//                 Field[pos[0] + r - 1][pos[1] + c - 1] = '0';
//             }
//         }
//     }
// }

// void replaceArray(char arrayA[3][3], char arrayB[3][3])
// {
//     for (int r = 0; r < 3; r++)
//     {
//         for (int c = 0; c < 3; c++)
//         {
//             arrayA[r][c] = arrayB[r][c];
//         }
//     }
// }

// // block register/picker
// void pickBlock(char block[3][3])
// {

//     int random = rand() % 6;
//     switch (random)
//     {
//     case 0:;
//         char newBlockTypeZ[3][3] = {
//             {'1', '1', '0'},
//             {'0', '1', '1'},
//             {'0', '0', '0'}};
//         replaceArray(block, newBlockTypeZ);
//         break;
//     case 1:;
//         char newBlockTypeT[3][3] = {
//             {'0', '1', '0'},
//             {'1', '1', '1'},
//             {'0', '0', '0'}};
//         replaceArray(block, newBlockTypeT);
//         break;
//     case 2:;
//         char newBlockTypeS[3][3] = {
//             {'0', '1', '1'},
//             {'1', '1', '0'},
//             {'0', '0', '0'}};
//         replaceArray(block, newBlockTypeS);
//         break;
//     case 3:;
//         char newBlockTypeO[3][3] = {
//             {'1', '1', '0'},
//             {'1', '1', '0'},
//             {'0', '0', '0'}};
//         replaceArray(block, newBlockTypeO);
//         break;
//     case 4:;
//         char newBlockTypeL[3][3] = {
//             {'0', '0', '1'},
//             {'1', '1', '1'},
//             {'0', '0', '0'}};
//         replaceArray(block, newBlockTypeL);
//         break;
//     case 5:;
//         char newBlockTypeJ[3][3] = {
//             {'1', '0', '0'},
//             {'1', '1', '1'},
//             {'0', '0', '0'}};
//         replaceArray(block, newBlockTypeJ);
//         break;
>>>>>>> Stashed changes

//     default:;
//         break;
//     }
// }

<<<<<<< Updated upstream
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
        printf("Game over!");
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
    int r, c;
    for (r = MARGIN; r < ROW + MARGIN; r++)
    {
        for (c = MARGIN; c < COL + MARGIN; c++)
        {
            printf("%c", Field[r][c]);
        }
        printf("\n");
    }
    printf("----------\n");
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

void main()
{
    srand(TMR2);
    int points = 0;
    int position[] = {1, 1}; // This defines the central position of the figure
    // pickBlock(CurrentPiece);
    // pickBlock(nextPiece);

    char testpiece[5][5] = {
        {'0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0'},
        {'1', '1', '1', '1', '1'},
        {'0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}};
    // pickBlock(testpiece);
    replaceArray(CurrentPiece, testpiece);

    startupReset();
    displayTest();

    moveRight();
    moveRight();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    moveLeft();
    moveLeft();
    moveLeft();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveDown();
    displayTest();
    moveRight();
    displayTest();
    moveRight();
    displayTest();
    moveRight();
    displayTest();
    moveRight();
    displayTest();
    moveLeft();
    displayTest();
    moveLeft();
    displayTest();
    moveLeft();
    displayTest();
    moveLeft();
    displayTest();
    moveLeft();
    displayTest();
    moveLeft();
    displayTest();
    moveLeft();
    displayTest();
    moveLeft();
    displayTest();
}
=======
// void newBlock(char Field[][COL], char block[3][3], int pos[])
// {
//     pos[0] = startR;
//     pos[1] = startC;
//     int alive = 1;
//     // check that position is not allready filled
//     for (int r = 0; r <= 2; r++)
//     {
//         for (int c = 0; c <= 2; c++)
//         {
//             if (block[r][c] == '1' && Field[pos[0] + r - 1][pos[1] + c - 1] == '1')
//             {
//                 alive = 0;
//             }
//         }
//     }
//     if (alive == 1)
//     {
//         placeBlock(Field, block, pos);
//     } else {
//         // proper game over function needed:
//         printf("Game over!");
//     }
// }

// void moveLeft(char Field[][COL], char block[3][3], int pos[])
// {
//     // Note: needs check for blocks in the way
//     if (pos[1] > 1)
//     {
//         // remove the block:
//         removeBlock(Field, block, pos);
//         int obstruct = 0;
//         // obstruction handler:
//         for (int r = 0; r < 3; r++)
//         {
//             for (int c = 0; c < 3; c++)
//             {
//                 if (block[r][c] == '1' && Field[pos[0] + r - 1][pos[1] + c - 2] == '1')
//                 {
//                     obstruct = 1;
//                 }
//             }
//         }

//         if (obstruct == 0)
//         {
//             // alter position
//             pos[1] = pos[1] - 1;
//         }
//         // place the block:
//         placeBlock(Field, block, pos);
//     }
// }

// void moveRight(char Field[][COL], char block[3][3], int pos[])
// {
//     // Note: needs check for blocks in the way
//     if (pos[1] < COL - 2)
//     {
//         // remove the block:
//         removeBlock(Field, block, pos);
//         int obstruct = 0;
//         // obstruction handler:
//         for (int r = 0; r < 3; r++)
//         {
//             for (int c = 0; c < 3; c++)
//             {
//                 if (block[r][c] == '1' && Field[pos[0] + r - 1][pos[1] + c] == '1')
//                 {
//                     obstruct = 1;
//                 }
//             }
//         }

//         if (obstruct == 0)
//         {
//             // alter position
//             pos[1] = pos[1] + 1;
//         }
//         // place the block:
//         placeBlock(Field, block, pos);
//     }
// }

// void moveDown(char Field[][COL], char block[3][3], int pos[])
// {
//     // Note: needs check for blocks in the way
//     if (pos[0] < ROW - 1)
//     {
//         // remove the block:
//         removeBlock(Field, block, pos);
//         // Obstruction handler
//         int obstruct = 0;
//         for (int r = 0; r < 3; r++)
//         {
//             for (int c = 0; c < 3; c++)
//             {
//                 if (block[r][c] == '1' && Field[pos[0] + r][pos[1] + c - 1] == '1')
//                 {
//                     obstruct = 1;
//                 }
//             }
//         }
//         if (obstruct == 0)
//         {
//             // alter position
//             pos[0] = pos[0] + 1;
//         }
//         // place the block:
//         placeBlock(Field, block, pos);
//     }
//     else
//     {
//         // block has reached the bottom
//         // 1. check full rows and move down
//         // 2. give points
//         // 3. new block

//         // 1.
//         int checkRows = 0;
//         // go through all rows
//         for (int r = 0; r < ROW; r++)
//         {
//             // check for filled space
//             if (Field[r][0] == '1')
//             {
//                 // check for full row
//                 int checkColumns = 0;
//                 for (int c = 0; c < COL; c++)
//                 {
//                     if (Field[r][c] == '1')
//                     {
//                         checkColumns++;
//                     }
//                 }
//                 // if full row is found
//                 if (checkColumns == COL)
//                 {
//                     // move all rows above, down one row (remove the full row)
//                     checkRows++;
//                     for (int moveRows = r; moveRows > 0; moveRows--)
//                     {
//                         for (int moveColumns = 0; moveColumns < COL; moveColumns++)
//                         {
//                             Field[moveRows][moveColumns] = Field[moveRows - 1][moveColumns];
//                         }
//                     }
//                 }
//             }
//         }
//         // 2.
//         // Award points for number of rows removed
//         switch (checkRows)
//         {
//         case 1:;
//             highscore += 40 * (level + 1);
//             break;
//         case 2:;
//             highscore += 100 * (level + 1);
//             break;
//         case 3:;
//             highscore += 300 * (level + 1);
//             break;
//         case 4:;
//             highscore += 1200 * (level + 1);
//             break;
//         default:;
//             break;
//         }
//         // 3.
//         // Create new block
//         replaceArray(CurrentPiece, nextPiece);
//         newBlock(Field, CurrentPiece, pos);
//         pickBlock(nextPiece);
//     }
// }

// // This will rotate the shape of the block clockwise 90 degrees
// void rotate(char Field[][COL], char block[3][3], int pos[])
// {
//     // remove the block:
//     removeBlock(Field, block, pos);
//     // alter rotation:
//     char newRotation[3][3];

//     int r, c;
//     for (int r = 0; r < 3; r++)
//     {
//         for (int c = 0; c < 3; c++)
//         {
//             newRotation[r][c] = block[2 - c][r];
//         }
//     }
//     // Obstruction checker:
//     int obstruct = 0;
//     for (int r = 0; r < 3; r++)
//     {
//         for (int c = 0; c < 3; c++)
//         {
//             if (newRotation[r][c] == '1' && Field[pos[0] + r - 1][pos[1] + c - 1] == '1')
//             {
//                 obstruct = 1;
//             }
//         }
//     }

//     if (obstruct == 0)
//     {
//         for (int r = 0; r < 3; r++)
//         {
//             for (int c = 0; c < 3; c++)
//             {
//                 block[r][c] = newRotation[r][c];
//             }
//         }
//     }

//     // place the block:
//     placeBlock(Field, block, pos);
// }

// // Following function is only for terminal testiing purpouses:
// void displayTest(char Field[][COL])
// {
//     int r, c;
//     for (r = 0; r < ROW; r++)
//     {
//         for (c = 0; c < COL; c++)
//         {
//             printf("%c", Field[r][c]);
//         }
//         printf("\n");
//     }
//     printf("----------\n");
// }

// void main()
// {
//     srand(TMR2);
//     char playField[ROW][COL];
//     int points = 0;
//     int position[] = {1, 1}; // This defines the central position of the figure
//     pickBlock(CurrentPiece);
//     pickBlock(nextPiece);

//     char testpiece[3][3] = {
//         {'0', '0', '0'},
//         {'0', '0', '0'},
//         {'0', '0', '0'}};
//     pickBlock(testpiece);

//     clearField(playField);
//     displayTest(playField);
//     newBlock(playField, testpiece, position);
//     displayTest(playField);
//     moveRight(playField, testpiece, position);
//     displayTest(playField);
//     moveDown(playField, testpiece, position);
//     displayTest(playField);
//     moveRight(playField, testpiece, position);
//     displayTest(playField);
//     rotate(playField, testpiece, position);
//     displayTest(playField);

//     pickBlock(testpiece);
//     newBlock(playField, testpiece, position);
//     displayTest(playField);
//     moveRight(playField, testpiece, position);
//     displayTest(playField);
//     moveRight(playField, testpiece, position);
//     displayTest(playField);

// }
>>>>>>> Stashed changes
