//Created by Israel Olatunde 19343116
//01/05/2020

//this source file executes the initialization of te game(eg the board and the players)

#include <stdio.h>//defines various input output functions
#include <stdlib.h>//defines various standard functions
#include "game_init.h"//defines various functions from the header file

//initialize_players function gets the information of the two players eg. their desired name and colour
void initializePlayers(player players[PLAYERS_NUM]){
    unsigned int playerNum;//unsigned integer variable playerNum used to indicate which player is red and which player is greem

    //player one is given a name
    printf("Enter the name of Player 1:");//prompt
    fgets(players[0].playerName,15,stdin);//reads the characters inputted by the user into playerName

    //player two is given a name
    printf("Enter the name of Player 2:");//prompt
    fgets(players[1].playerName,15,stdin);//reads the characters inputted by the user into playerName

    //players are assigned colours
    back://label
    printf("Enter:\n'1' for %s to be RED and %s to be GREEN\n\n",players[0].playerName, players[1].playerName);//prompt
    printf("'2' for %s to be GREEN and %s to be RED\n", players[0].playerName, players[1].playerName);//prompt
    scanf("%u",&playerNum);//reads in an unsigned integer value to playerNum

    if(playerNum==1){//if playerNum is equal to 1
        players[0].playerColor = RED;//player 1 is red
        players[1].playerColor  = GREEN;//player 2 is green
        printf("%s is RED\n%s is GREEN\n\n",players[0].playerName, players[1].playerName);//prompt
    }
    if(playerNum==2){//if playerNum is equal to 2
        players[0].playerColor = GREEN;//player 1 is green
        players[1].playerColor = RED;//player 2 is red
        printf("%s is GREEN\n%s is RED\n\n",players[0].playerName, players[1].playerName);//prompt
    }
    if(playerNum!=1 && playerNum!=2){//if playerNum is not 1 or 2
        printf("Error:Please enter a valid number");//print error
        goto back;//jumps to the label back to give users another chance to enter a valid input
    }

    for(int i=0; i<2;i++){//for i equals 0;i less than 2; i increment
        //initializes pieces captured and reserved as 0
        players[i].piecesReserved=0;
        players[i].piecesCaptured=0;
    }
}

//Set Invalid Squares (where it is not possible to place stacks)
setInvalid(square * s){
s->type = INVALID;//square type set as invalid
s->stack = NULL;//stack is set as NULL
s->noPieces = 0;//number of pieces is set as 0
}

//Set Empty Squares (with no pieces/stacks)
setEmpty(square * s){
s->type = VALID;//square type is set as VALID
s->stack = NULL;//stack is set as NULL
s->noPieces = 0;//numnber of pieces in stack is set as 0
}

//Set squares  with a GREEN piece
setGreen(square * s){
s->type = VALID;//square type is set as VALID
s->stack = (piece *) malloc (sizeof(piece));//stack size is set as the size of the strcut piece
s->stack->pieceColor = GREEN;//color of stack is set as GREEN
s->stack->next = NULL;//stack points to nothing
s->noPieces = 1;//number of pieces is 1
}

//Set squares with a RED piece
setRed(square * s){
s->type = VALID;//square type is set as VALID
s->stack = (piece *) malloc (sizeof(piece));//stack size is set as the size of the strcut piece
s->stack->pieceColor = RED;//color of stack is set as RED
s->stack->next = NULL;//stack points to nothing
s->noPieces = 1;//number of pieces is 1
}

//initializes the board
void initializeBoard(square board [BOARD_SIZE][BOARD_SIZE]){
    //The following nested loops goes through each position on the board and initializes the squares to the according to the rules of the game
    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            //sets invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                setInvalid(&board[i][j]);

            else{
                //sets squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    setEmpty(&board[i][j]);
                else{
                    //sets squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4))) {
                        setRed(&board[i][j]);


                    }

                        //sets green squares
                    else setGreen(&board[i][j]);
                }
            }
        }
    }
}
