/*
 * FILE: game.c
 * AUTHOR: Rivin Pathirage
 * UNIT: Unix and C Programming
 * PURPOSE: Implenting the methods for gameplay
 * Referrences:
 */


#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "random.h"
#include "color.h"
#include "terminal.h"
#include "linkedlist.h"


/*
 * METHOD: map
 * PURPOSE: making the map
 * IMPORTS: pRows, pCols
 * EXPORTS: pMap
 */
char** map(int pRows, int pCols)
{
    char **pMap;
    int i, j;

    /* Allocate memory for the map */
    pMap = (char**)malloc(pRows * sizeof(char*));
    for (i = 0; i < pRows; i++)
    {
        pMap[i] = (char*)malloc(pCols * sizeof(char));
    }

    /* Make the map */
    for (i = 0; i < pRows; i++)
    {
        for (j = 0; j < pCols; j++)
        {
            if (i == 0 || i == pRows-1 || j == 0 || j == pCols-1)
            {
                pMap[i][j] = '*';
            }
            else
            {
                pMap[i][j] = ' ';
            }
        }
    }

    return pMap;
}


/*
 * METHOD: displaymap
 * PURPOSE: displaying the map
 * IMPORTS: pMapRows, pMapCols, **pMap, pGoalCol, pGoalRow, boxRow, boxCol
 * EXPORTS: 
 */
void displayMap(char **pMap, int pMapRow, int pMapCol, int pGoalRow, int pGoalCol, int boxRow, int boxCol, char **blueArray)
{
    int j;
    int p;
    for (j = 0; j < pMapRow; j++)
    {
        for (p = 0; p < pMapCol; p++)
        {
            if (j == pGoalRow && p == pGoalCol)
            {
                setBackground("red");
                printf("%c",pMap[j][p]);
                setBackground("reset");
            }
	    else if (j == boxRow && p == boxCol)
	    {
		setBackground("blue");
                printf("%c",pMap[j][p]);
                setBackground("reset");
	    }
	    else if (blueArray[j][p] == 'y')
	    {
		setBackground("blue");
                printf("%c",pMap[j][p]);
                setBackground("reset");
	    }
            else
            {
                printf("%c",pMap[j][p]);
            }

            
        }
        printf("\n");
    }
}


/*
 * METHOD: moveUpDown
 * PURPOSE: moving the player up and down
 * IMPORTS: pPlayerRow, pPlayerCol, pInput, pMapRowHigh, pGoalRow, pGoalCol
 * EXPORTS: result
 */
int moveUpDown(char pInput, int pPlayerRow, int pPlayerCol, int pMapRowHigh, int pGoalRow, int pGoalCol)
{


	int result;
	
	if (pInput =='w')
	{
		if ((pPlayerRow -1  != 0) /*|| (( pPlayerRow - 1 != pGoalRow) && (pPlayerCol != pGoalCol))*/)
		{
			pPlayerRow--;
		}

		result = pPlayerRow;
	}
	else if (pInput == 's')
	{

		if ((pPlayerRow +1 != pMapRowHigh)/* || (( pPlayerRow +1 != pGoalRow) && (pPlayerCol != pGoalCol))*/)
                {
	
                        pPlayerRow++;
                }
		/*pPlayerRow++;*/

		result = pPlayerRow;
	}
	
	else
	{
		printf("\nInvalid Input\n");
	}

	return result;	

}

/*
 * METHOD: moveLeftRight
 * PURPOSE: moving the player left and right
 * IMPORTS: pPlayerRow, pPlayerCol, pInput, pMapRowHigh, pDirection, pBoxCol
 * EXPORTS: result
 */
int moveLeftRight(char pInput, int pPlayerCol, int pMapColHigh, char pDirection, int pBoxCol)
{


        int result;
        /*change to while loop later*/
        if (pInput =='a')
        {
		if (pPlayerCol - 1 != 0 /*&& ((pDirection != 'l')&& (pBoxCol -1 != 0))*/)
		{
			pPlayerCol--;
		}
        	/*pPlayerCol--;*/

                result = pPlayerCol;
        }
        else if (pInput == 'd')
        {

		if (pPlayerCol + 1 != pMapColHigh/* && ((pDirection != 'r') && (pBoxCol +1 != pMapColHigh))*/)
		{
			pPlayerCol++;
		}
                /*pPlayerCol++;*/

                result = pPlayerCol;
        }
        else
        {
                printf("\nInvalid Input\n");
        }

        return result;

}

/*
 * METHOD: nearBox
 * PURPOSE: checking if the box is next to the player
 * IMPORTS: pPlayerRow, pPlayerCol, pBoxRow, pBoxCol
 * EXPORTS: result
 */
char nearBox(int pPlayerRow, int pPlayerCol, int pBoxRow, int pBoxCol)
{

	char result;

	if (pPlayerCol == pBoxCol && pPlayerRow == pBoxRow - 1)
	{
		result = 'd';
	}
	else if (pPlayerCol == pBoxCol && pPlayerRow == pBoxRow + 1)
        {
                result = 'u';
        }
	else if (pPlayerRow == pBoxRow && pPlayerCol == pBoxCol - 1)
        {
                result = 'r';
        }
	else if (pPlayerRow == pBoxRow && pPlayerCol == pBoxCol + 1)
        {
                result = 'l';
        }
	else
	{
		result = 'n';
	}

	return result;
}

/*
 * METHOD: boxUpDown
 * PURPOSE: moving the box up and down
 * IMPORTS: pBoxRow, pBoxCol, pInput, pMapRowHigh, **wallArray, wallCount, pDirection
 * EXPORTS: result
 */
int boxUpDown(char pInput, char pDirection, int pBoxRow, int pMapRowHigh, int boxCol, int **wallArray, int wallCount)
{


        int result;
	int i;
	char go = 'g';


	for (i = 0; i < wallCount; i++)
	{
		/*Can't go up*/
		if ((wallArray[i][0] == boxCol) && (wallArray[i][1] == pBoxRow -1))
		{
		

			/*Can't go down*/
			if ((wallArray[i][0] == boxCol) && (wallArray[i][1] == pBoxRow +1))
			{
                        	go = 'n';
                	}
			else
			{
				go = 'D';
			}
		}
		
		
		/*can't go down*/
		if ((wallArray[i][0] == boxCol) && (wallArray[i][1] == pBoxRow +1))
		{
		
			/*Can't go up*/
			if ((wallArray[i][0] == boxCol) && (wallArray[i][1] == pBoxRow -1))
                	{
				/**/
			}
			else
			{
		
				go = 'U';
			}
		}
	}


        if ((pInput =='w' && pDirection == 'u') && ((go == 'g') || (go == 'U')  )) 
     	{

		if (pBoxRow -1 != 0)
                {
                        pBoxRow--;
                }

		result = pBoxRow;
	
		/*pBoxRow--;*/

                result = pBoxRow;
        }
        else if ((pInput == 's' && pDirection == 'd')&& ((go == 'g') || (go == 'D')  ))
        {

		if (pBoxRow + 1 != pMapRowHigh)
		{
			pBoxRow++;
		}

				
		

	
			
                /*pBoxRow++;*/

                result = pBoxRow;
        }
        else
        {
                result = pBoxRow;
        }

        return result;

}


/*
 * METHOD: boxLeftRight
 * PURPOSE: moving the box right and left
 * IMPORTS: pDirection, pBoxCol, pInput, pMapColHigh, pBoxRow
 * EXPORTS: result
 */
int boxLeftRight(char pInput, char pDirection, int pBoxCol, int pMapColHigh)
{


        int result;

        if (pInput =='a' && pDirection == 'l')
        {
		if (pBoxCol -1 != 0)
		{
			pBoxCol--;
		}
                /*pBoxCol--;*/

                result = pBoxCol;
        }
        else if (pInput == 'd' && pDirection == 'r')
        {

		if (pBoxCol + 1 != pMapColHigh)
		{
			pBoxCol++;
		}
                /*pBoxCol++;*/

                result = pBoxCol;
        }
        else
        {
                result = pBoxCol;
        }

        return result;

}

/*
 * METHOD: gamestate
 * PURPOSE: determining whether the game is won or not
 * IMPORTS: pBoxRow, pBoxCol pGoalRow, pGoalCol
 * EXPORTS: pState
 */
int gameState(int pBoxRow, int pBoxCol, int pGoalRow, int pGoalCol)
{
	int pState = 1;

	if ((pGoalRow == pBoxRow) && (pGoalCol == pBoxCol))
	{
		pState = 3;
	}

	return pState;
}

/*
 * METHOD: displayWonMap
 * PURPOSE: displaying the map after winning
 * IMPORTS: **pMap, pMapCol, pInput, pMapRow, pGoalRow, pGoalCol, **blueArray
 * EXPORTS:
 */
void displayWonMap(char **pMap, int pMapRow, int pMapCol, int pGoalRow, int pGoalCol, char **blueArray)
{
    int j;
    int p;
    for (j = 0; j < pMapRow; j++)
    {
        for (p = 0; p < pMapCol; p++)
        {
            if (j == pGoalRow && p == pGoalCol)
            {
                setBackground("green");
                printf("%c",pMap[j][p]);
                setBackground("reset");
            }
	    else if (blueArray[j][p] == 'y')
            {
                setBackground("blue");
                printf("%c",pMap[j][p]);
                setBackground("reset");
            }
            else
            {
                printf("%c",pMap[j][p]);
            }


        }
        printf("\n");
    }
}
