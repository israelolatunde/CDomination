//Created by Israel Olatunde 19343116
//01/05/2020
// program that implements the Focus/Domination board game

//this source file simply calls the main functions from the other modules


#include "input_output.h"//defines function used in input_output.c source file


int main() {//main function begins program execution

    // declaration of the players
    player players[PLAYERS_NUM];
    //declaration of the board
    square board[BOARD_SIZE][BOARD_SIZE];

    rules();//calls the rules function
    initializePlayers(players);//calls the initialize_players function
    initializeBoard(board);//calls the initialize_board function
    printBoard(board);//calls the print_board function
    manageTurns(board,players);//calls the manageTurn function



    return 0;
}

