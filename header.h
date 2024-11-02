#ifndef HEADER_H
#define HEADER_H

char** map(int pRows, int pCols);
void displayMap(char **pMap, int pMapRow, int pMapCol, int pGoalRow, int pGoalCol, int boxRow, int boxCol, char **blueArray);
int moveUpDown(char pInput, int pPlayerRow, int pPlayerCol, int pMapRowHigh, int pGoalRow, int pGoalCol);
int moveLeftRight(char pInput, int pPlayerCol, int pMapColHigh, char pDirection, int pBoxCol);
char nearBox(int pPlayerRow, int pPlayerCol, int pBoxRow, int pBoxCol);
int boxUpDown(char pInput, char pDirection, int pBoxRow, int pMapRowHigh, int boxCol, int **wallArray, int wallCount);
int boxLeftRight(char pInput, char pDirection, int pBoxCol, int pMapColHigh);
int gameState(int pBoxRow, int pBoxCol, int pGoalRow, int pGoalCol);
void displayWonMap(char **pMap, int pMapRow, int pMapCol, int pGoalRow, int pGoalCol, char **blueArray);

#endif
