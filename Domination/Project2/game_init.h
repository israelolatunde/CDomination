//Created by Israel Olatunde 19343116
//01/05/2020

//Header file for the source file game_init.c

#ifndef GAME_INIT_H
#define GAME_INIT_H

#define BOARD_SIZE 8//defines the string BOARD_SIZE with the value 8
#define PLAYERS_NUM 2//define the string PLAYERS_NUM with the value 2

//defines an enumeration for colors that a piece can have
typedef enum color {
    RED,
    GREEN
}color;

// defines an enumeration for square types


typedef enum squareType {
    VALID,//VALID: squares where it is possible to place a piece or a stack
    INVALID//INVALID: squares that are on the sides and where no piece can be placed
}squareType;

// defines a struct to hold information of each piece
typedef struct piece {
    //the color associated with a piece
    color pieceColor;

    // This is a pointer to the next pieces to create a stack
    struct piece * next;

}piece;

//defines a struct to hold information of each player
typedef struct player{

    color playerColor; //the color associated with the player
    int  piecesReserved;//the amount of pieces reserved
    int  piecesCaptured;//the amount of pieces captured
    char playerName[25];//the players name
}player;



// defines a struct to hold information of each square of the board
typedef struct square {
    squareType type; // type of the square (VALID/INVALID)

    piece * stack;//the piece or the top piece on the stack

    int noPieces;//number of pieces on the square
}square;



//Function to create the players
void initializePlayers(player players[PLAYERS_NUM]);

//Function to create the board
void initializeBoard(square board[BOARD_SIZE][BOARD_SIZE]);

#endif


