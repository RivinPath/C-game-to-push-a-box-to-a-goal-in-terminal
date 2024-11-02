/*
 * FILE: box.c
 * AUTHOR: Rivin Pathirage
 * UNIT: Unix and C Programming
 * PURPOSE: Implenting the game
 * Referrences:
 */


#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "random.h"
#include "color.h"
#include "terminal.h"
#include <string.h>
#include "linkedlist.h"

#define MAX_LENGTH 50

int main(int argc, char *argv[])
{


   int i;
   int x;
   int boxRow;
   int boxCol;
   int playerRow;
   int playerCol;
   char **mapArray;
   char **blueArray;
   char playerInput;
   char direction;
   char filename[MAX_LENGTH];
   FILE* f;
   int count;
  	
   int mapRow;
   int mapCol;
   int tempCol;
   int tempRow;
   char tempChar;
   int nRead;
   int goalRow;
   int goalCol;
   int wallCount;
  	
   int **wallArray;
   int **undoTrailArray;
   int j;
   int tempBoxRow;
   int tempBoxCol;
   void *firstNode;
   LinkedList list;

   initRandom();
   count = 1;
   wallCount = 0;


    

   if (argc < 2)
   {
        printf("Please enter the reading file name argument excluding the program name\n Example:- ./box map.txt");
        return 0;
   }
   else
   {
        
	/*File reading*/
        strcpy(filename, argv[1]);

        printf("%s\n", filename);


        f = fopen(filename, "r");

	if (f == NULL)
        {
                printf("Error: could not open 'map.txt' \n");

        }
	else
        {


                do
                {
                        if (count == 1)
                        {

                                nRead = fscanf(f, "%d %d", &mapRow, &mapCol);
                                count++;
                                printf("%d %d\n", mapRow, mapCol);

                        }
                        else
                        {
                                nRead = fscanf(f, "%d %d %c", &tempRow, &tempCol, &tempChar);

                                if (tempChar == 'P')
                                {
                                        playerRow = tempRow + 1;
                                        playerCol = tempCol + 1;
                                }
                                else if (tempChar == 'B')
                                {
                                        boxRow = tempRow + 1;
                                        boxCol = tempCol + 1;
                                }
                                else if (tempChar == 'G')
                                {
                                        goalRow = tempRow + 1;
                                        goalCol = tempCol + 1;
                                }
                                else if (tempChar == 'O')
                                {
                                        wallCount++;
                                }

                                printf("%d %d %c\n", tempRow, tempCol, tempChar);
                        }
                } while (nRead >= 0);

                printf("\n \n \n wall count is %d\n", wallCount);




                /*Creating the wallArrya using malloc*/
                fclose(f);

		if (wallCount != 0)
                {
                        wallArray = (int**)malloc(wallCount * sizeof(int*));

                        for (i = 0; i < wallCount; i++)
                        {
                                wallArray[i] = (int*)malloc(2 * sizeof(int));
                        }
                }


                /*Populating the wallArray*/


                f = fopen(filename, "r");

                count = 1;
		i = 0;

                if (f == NULL)
                {
                        printf("Error: could not open 'map.txt' \n");

                }
                else
                {
                        do
                        {
                                if (count == 1)
                                {

                                        nRead = fscanf(f, "%d %d", &mapRow, &mapCol);
                                        count++;
                                        /*printf("%d %d\n", mapRow, mapCol);*/

                                }
                                else
                                {
                                        nRead = fscanf(f, "%d %d %c", &tempRow, &tempCol, &tempChar);


                                        if (tempChar == 'O')
                                        {
                                                /*for (i = 0; i < wallCount; i++)
                                                {
                                                        wallArray[i][0] = tempRow;
                                                        wallArray[i][1] = tempCol;
                                                        
                                                }*/






						wallArray[i][0] = tempRow + 1;
                                                wallArray[i][1] = tempCol + 1;

						i++;

                                                
                                                printf("%d %d %c\n", tempRow, tempCol, tempChar);
                                        }

				}
                        } while (nRead >= 0);


                }




	}

	for(i = 0; i < wallCount; i++)
	{
		for (j = 0; j < 2; j++)
		{
			printf("%d",wallArray[i][j]);
		}
		printf("\n");
	}


	printf("\n%d %d\n",wallArray[0][0], wallArray[0][1]);
	


        if (mapRow < 5  || mapCol < 5)
        {
            printf("The map rows and columns should be at least 5");
        }
        else if (playerRow < 1 || playerCol < 1 || goalRow < 1 || goalCol < 1)
        {
            printf("The player and goal cordinets should be higher than 0");
        }
	else if ((playerRow == goalRow)&&(playerCol == goalCol))
	{
		printf("Player and goal shouldn't have the same coordinates. Please change");
	}
        else
        {

            /*mallocing the mapArrays*/
            mapArray = (char**)malloc(mapRow * sizeof(char*));

            for (i = 0; i < mapRow; i++)
            {
                mapArray[i] = (char*)malloc(mapCol * sizeof(char));
            }

            mapArray = map(mapRow, mapCol);




	    /*mallocing the blueArrays*/
            blueArray = (char**)malloc(mapRow * sizeof(char*));

            for (i = 0; i < mapRow; i++)
            {
                blueArray[i] = (char*)malloc(mapCol * sizeof(char));
            }


	    /*mallocing the undoTrailArray*/
            undoTrailArray = (int**)malloc(mapRow * sizeof(int*));

            for (i = 0; i < mapRow; i++)
            {
                undoTrailArray[i] = (int*)malloc(mapCol * sizeof(int));
            }

            



	    /*Populating blueArray*/
	    for (i = 0; i < mapRow; i++)
	    {
        	for (j = 0; j < mapCol; j++)
        	{
            		
            		blueArray[i][j] = 'x';
            		
        	}
	    }


	    /*Populating undoTrailArray*/
            for (i = 0; i < mapRow; i++)
            {
                for (j = 0; j < mapCol; j++)
                {

                        blueArray[i][j] = 0;

                }
            }


	    /*Creating the Linked List*/
	    
	    initializeList(&list);

	    
            mapArray[playerRow][playerCol] = 'P';

            /*Printing the Goal*/
            mapArray[goalRow][goalCol] = 'G';



	    /*Printing the wall*/
	    for (j = 0; j < wallCount; j++)
	    {
		    mapArray[wallArray[j][0]][wallArray[j][1]] = 'O';
	    }

	    


           


            system("clear");

	    
            mapArray[boxRow][boxCol] = 'B';
	    blueArray[boxRow][boxCol] = 'y';

	    

	    displayMap(mapArray, mapRow, mapCol, goalRow, goalCol, boxRow, boxCol, blueArray);

	    mapArray[playerRow][playerCol] = ' ';

	    direction = nearBox(playerRow, playerCol, boxRow, boxCol);
	    /*printf(" %c", direction);*/

	    x = 2;

		while (x > gameState(boxRow, boxCol, goalRow, goalCol))
                {
            		printf("Move the box to the goal to win the game!\nPress w to move up\nPress s to move down\nPress a to move left\nPress d to move right\nPress u to undo\n");
            		disableBuffer();
            		scanf(" %c", &playerInput);
            		enableBuffer();

			system("clear");


			if (playerInput == 'w' || playerInput == 's')
			{
				playerRow = moveUpDown(playerInput, playerRow, playerCol, mapRow-1, goalRow-1, goalCol-1);
				boxRow = boxUpDown(playerInput, direction, boxRow, mapRow -1, boxCol, wallArray, wallCount);
				insertFirst(&list, playerRow, playerCol, boxRow, boxCol);
			}
			else if (playerInput == 'a' || playerInput == 'd')
			{
				playerCol = moveLeftRight(playerInput, playerCol, mapCol-1, direction, boxCol);
				boxCol = boxLeftRight(playerInput, direction, boxCol, mapCol -1);
				insertFirst(&list, playerRow, playerCol, boxRow, boxCol);
			}
			else if (playerInput == 'u')
			{

				tempBoxRow = boxRow;
				tempBoxCol = boxCol;



				deleteFirst(&list);

				firstNode = getFirst(&list);
				if (firstNode != NULL)
        			{

					/*firstNode = getFirst(&list);*/
					ListNode *node = (ListNode*)firstNode;
                			playerRow = (int)node->playerRow;
                			playerCol = (int)node->playerCol;
                			boxRow = (int)node->boxRow;
                			boxCol = (int)node->boxCol;

					
				}

				mapArray[tempBoxRow][tempBoxCol] = ' ';

				/*if (undoTrailArray[tempBoxRow][tempBoxCol] == 0)
				{
					blueArray[tempBoxRow][tempBoxCol] = 'x';
				}
				else
				{
					undoTrailArray[tempBoxRow][tempBoxCol]--;
				}*/

				blueArray[tempBoxRow][tempBoxCol] = 'x';



			}
            		

			mapArray[playerRow][playerCol] = ' ';

			mapArray[goalRow][goalCol] = 'G';

			mapArray[playerRow][playerCol] = 'P';

			mapArray[boxRow][boxCol] = 'B';

			if (blueArray[boxRow][boxCol]  == 'y' )
			{
				blueArray[boxRow][boxCol] = 'y';
				undoTrailArray[boxRow][boxCol]++;
			}
			else
			{
				blueArray[boxRow][boxCol] = 'y';
			}

	    		/*system("clear");*/

	    		displayMap(mapArray, mapRow, mapCol, goalRow, goalCol, boxRow, boxCol, blueArray);

			mapArray[playerRow][playerCol] = ' ';

			direction = nearBox(playerRow, playerCol, boxRow, boxCol);
			/*printf(" %c", direction);*/

	    		

		}

		system("clear");

		mapArray[playerRow][playerCol] = 'P';	

		displayWonMap(mapArray, mapRow, mapCol, goalRow, goalCol, blueArray);		


            /*Put the freeing of the mapArray here*/
            for (i = 0; i <mapRow; i++)
            {
                free(mapArray[i]);
            }
            free(mapArray);


	    /*Put at the bottom (freeing the wallArray)*/
            for (i = 0; i < wallCount; i++)
            {
                free(wallArray[i]);
            }
            free(wallArray);


	    /*Put the freeing of the blueArray here*/
            for (i = 0; i <mapRow; i++)
            {
                free(blueArray[i]);
            }
            free(blueArray);

	    /*Put the freeing of the undoTrailArray here*/
            for (i = 0; i <mapRow; i++)
            {
                free(undoTrailArray[i]);
            }
            free(undoTrailArray);



	    /*Free the memory*/
	    freeList(&list);


            printf("\nCongratulations!!!\n You WON!!\n");
        }

        
    }

    return 0;
}
