//Created by Israel Olatunde 19343116
//01/05/2020

#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H

#endif

#include "game_init.h"//defines functions used im game_init.c source file

//defines a struct to hold the coordinates of player moves
 struct position {
    int row;//row integer variable holds row coordinates
    int column;//column integer variable holds column coordinates
};


void printBoard(square board[BOARD_SIZE][BOARD_SIZE]);//calls printBoard function
//calls manageMoves function
void manageMoves(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM], int playerMove, int row1,int column1,int row2,int column2);
//calls manageTurns function
void manageTurns(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM]);
//calls winningFormula function
int winningFormula(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM], int playerMove);
void winnersMessage(player players[PLAYERS_NUM],int winner, int loser);//calls winnersMessage function
void rules();