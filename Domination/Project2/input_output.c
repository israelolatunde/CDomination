//Created by Israel Olatunde 19343116
//01/05/2020

#include <stdio.h>//defines various input output functions
#include <stdlib.h>//defines various standard functions
#include "input_output.h"//defines function used in input_output.c source file



void rules(){//rules function prints the rules of the game
    puts("\n\n\n\n\t*HELLO PLAYERS AND WELCOME TO FOCUS, THE ABSTRACT BOARD GAME*\n\n\nTHE RULES ARE AS FOLLOWS:\n\n");
    puts("EACH PLAYER HAS 18 TOKENS THAT ARE INITIALLY PLACED ON A\nCHECKBOARD WITH THE THREE CORNER SQUARES REMOVED,\nTHE TOP LEFT CORNER IS ROW 0 COLUMN 0,\n");
    puts("ON HIS/HER TURN A PLAYER:\n"
         "1. SELECTS A PIECE OR A STACK THEY WANT TO MOVE. OF THEIR OWN COLOUR OR A STACK \nTHAT HAS A TOP PIECE OF THEIR OWN COLOUR. IF A PLAYER \nCANNOT SELECT ANY PIECE/STACK TO MOVE, THE OTHER PLAYER WINS THE GAME.\n\n"
         "2. A STACK CAN BE MOVED TO A NUMBER OF POSITIONS DEPENDING \nON THE SIZE OF THE STACK. FOR EXAMPLE, IF THE SIZE OF THE STACK IS 4, THAT STACK CAN BE MOVED TO A POSITION COMPUTED BY MOVING THE STACK <UP, UP, LEFT, RIGHT> OR <DOWN, DOWN, DOWN, LEFT>.\n\n"
         "3. WHEN A STACK GROWS OVER FIVE PIECES, PIECES FROM THE BOTTOM OF THE STACK ARE REMOVED\n AND KEPT BY THE CURRENT PLAYER,IN ORDER TO BRING THE STACK SIZE BACK DOWN TO FIVE PIECES. PIECES\n OF A PLAYER'S OWN COLOR THAT ARE KEPT BY THAT PLAYER ARE RESERVED TO RE-ENTER THE GAME \nAT A LATER TIME, WHEN THE PLAYER CANNOT MOVE ANY OF HIS/HER PIECES OR ANY STACKS. \nPIECES OF THE OPPONENT'S COLOR ARE KEPT AS CAPTURED. RESERVED PIECES\nCAN BE ENTERED ON A TURN IN ANY SPACE ON THE BOARD IN PLACE OF MAKING\n A MOVE OF PIECES.\n\n");
    puts("_______________________________________________________________");
    printf("\nNOW THAT WE KNOW THE RULES LET US BEGIN!!\n\n\n");

}


void printBoard(square board[BOARD_SIZE][BOARD_SIZE]){//printBoard function prints the board
    printf("\t\t****** The Board ******\n");
    //The nested loops goes through each square n the board
    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
               // Valid empty squares are printed as |   |
                if(board[i][j].stack == NULL)
                    printf("|     ");
                else{
                    if (board[i][j].stack->pieceColor == GREEN) {
                        printf("|  %dG ",board[i][j].noPieces);
                    }

                    if(board[i][j].stack->pieceColor == RED){
                       // Valid squares with a RED piece are printed as | R |
                        printf("|  %dR ", board[i][j].noPieces);

                    }
                }
            }
            else
                printf("|  -  "); //Invalid Squares are printed as | - |
        }
        printf("|\n");
    }
}

moveStack(square * a,square * t){//moveStack function carries out functionality to move stacks from one square to another
//properties of the stack we are moving is given to top and the stack is set to null
struct piece * top = a->stack;
a->stack = NULL;
//properties of top is given to curr
struct piece * curr = top;
//curr goes through this loop and now points to the bottom of the stack we are moving
while(curr->next != NULL){
curr = curr->next;
}
//the bottom of the stack we are moving now points to the top of the stack we are moving to
//this joins the two stacks together
curr->next = t->stack;
t->stack = top;
t->noPieces += a->noPieces;//number of pieces of both stacks added together
a->noPieces=0;
}

//function removePiece implements functionality to remove pieces from the stack if they exceed the limit of 5
//and updates the pieces captured and reserved
removePiece(square * t, player players[PLAYERS_NUM], int playerMove){
int count = 1;//integer variable count initialized as 1
struct piece * curr ;
curr = t->stack;//curr given the properties of the stack
struct piece * last = NULL;
//the loop will stop after it reaches the fifth piece in the stack
while(curr != NULL){
if(count < 5){
curr = curr->next;
count++;
//the position the loop stops at is given to last
}else{
last = curr;
begin:
goto finish;
}
}
finish:

if(last!=NULL){
curr = curr->next;
//the following loop removes the excess pieces from the bottom of the stack
while(curr != NULL){
piece * toRemove = curr;
curr = curr->next;
color removedColor = toRemove->pieceColor;
free(toRemove);//free function frees up the allocated memory
t->noPieces--;//number of pieces in the stack is decremented
if(players[playerMove].playerColor == removedColor){//if the piece removed is the same color as the player...

players[playerMove].piecesReserved++;//it becomes a reserved piece
}
else players[playerMove].piecesCaptured++;//if the piece is not the same color as the player it becomes a captured piece

}
last->next = NULL;//last is set to null

}
}

//the function reserve carries out the functionality to add reserve pieces to the board
reserve(square * t, player players[PLAYERS_NUM], int playerMove){
//a new struct pointer called a is initialized
piece * a = (piece *) malloc (sizeof(piece));
a->pieceColor = players[playerMove].playerColor;//a is given the color of the current player
a->next = NULL;//a points to NULL

piece * curr = t->stack;//curr is given the properties of the stack we are placing the reserved piece on
t->stack = a;//the stack is now given the properties of the reserved piece
t->stack->next = curr;//the reserved piece now points to the stack we are moving it to, it is now the top piece od of the stack
t->noPieces ++;//number of pieces incremented
players[playerMove].piecesReserved--;//pieces reserved decremented
}

//winningFormula function checks if the winning condition has been met
int winningFormula(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM], int playerMove) {
    int decide = 0;//integer variable decide initalized as 0
    //nested loops go through each square on the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            //if the square is valid and not empty
            if (board[i][j].type == VALID && board[i][j].stack != NULL) {
                //if the player has a stack they can move or if they have reserved pieces
                if (board[i][j].stack->pieceColor == players[playerMove].playerColor ||
                    players[playerMove].piecesReserved > 0) {
                    decide = 1;//decide given value of 1
                    return decide;//value of decide returned
                }
            }
        }
    }
    return decide;//value of decide returned
}

//winnersMessage function prints the message for the winner once the game is over
void winnersMessage(player players[PLAYERS_NUM], int winner, int loser){
    printf("\t             Game Over.\n");
    printf("____________________________________________________");
    printf("\n\n!!Congratulations to %s  They have won the game!!\n\n\n", players[winner].playerName);
    printf("The loser is %sBetter luck next time :)\n", players[loser].playerName);
    exit(0);//once the winning message is printed the programmes is terminated
}


//I just wanted to be able to call the moveStack and removePieces fucntions in a single function so I made the manageMoves function
void manageMoves(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM], int playerMove, int row1,int column1,int row2,int column2) {
//printf("test\n");
    moveStack(&board[row1][column1], &board[row2][column2]);
    if(board[row2][column2].noPieces > 5) {
        removePiece(&board[row2][column2], players, playerMove);
    }

}

//manageTurns function handles the turns of each player
void manageTurns(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM]){

    int move = 0;//integer variable move initialized as 0, move will be used as indexing for the the turns
    int nomoves;//integer variable nomoves declared, nomoves will be used as indexing for the number of moves
    int user = 1;//integer variable user initialized as 1

    //struct variable currPos and nextPos declared to hold the current stack postion and where we are moving it to
    struct position currPos;
    struct position nextPos;

    int moveChoice;//integer variable moveChoice declared
    int gameOver= 0;//integr variable gameOver initialized


    for (nomoves = 0; 1<2; nomoves++) {//for nomoves equals zero; infinity; nomoves increment
        for (move = 0; move < 2; move++) {//for move equals zero; move les than 2;mov e increment

            gameOver = winningFormula(board, players, move);//calls winningFormula to check if a player has won before every move and the value is given to gameOver

            if (gameOver == 0) {//if gameOver is equal to 0 then someone has won the game
                int loser = move;//int variable loser is given the current move
                int winner;//integer variable winner is declared
                //if the loser is 0 then the winner is 1 and vice versa
                //winners message is called
                if (loser == 0) {
                    winner = 1;
                    winnersMessage(players, winner, loser);

                } else if (loser == 1) {
                    winner = 0;
                    winnersMessage(players, winner, loser);
                }

            } else{//if no winner is found then the layer can take their move

                //start label is used to return to start of the statement if player makes an error while making a move
                start:




                user = !user;
                printf("Turn number %d. Player: %s\n", nomoves + 1, players[move].playerName);//prompt
                //only if the player has a reserved piece i will give them the option to use it
                if (players[move].piecesReserved >= 1) {
                    printf("Enter:\n '1' to move a stack on the board\n'2' to use one of your reserved pieces.\n");//prompt
                    scanf("%d", &moveChoice);//the players choice is read into moveChoice
                    if (moveChoice != 1 && moveChoice != 2) {//if the player makes a mistake
                        printf("Please enter a valid choice\n");
                        goto start;//goto start label

                    }
                } else moveChoice = 1;//if the player doesnt have a reserved piece their choice will be fixed to 1 and they will be forced to move an existing stack


                if (moveChoice == 1) {//if moveChoice is 1

                    printf("Enter the row and column coordinates of the stack you would like to move\n");//prompt
                    scanf("%d%d", &currPos.row, &currPos.column);//reads in row and column coordinates of the stack you want to move
                    printf("Enter the row and columns coordinates of where you want to move this stack to\n");//prompt
                    scanf("%d%d", &nextPos.row, &nextPos.column);//reads in row and column coordinates of where you want to move to
                    int difference1, difference2;//integer variables difference 1 & 2 declared
                    //this is used to check the amount of squares between the two coordinates the user inputted
                    difference1 = (currPos.row - nextPos.row) * (currPos.row - nextPos.row);
                    difference2 = (currPos.column - nextPos.column) * (currPos.column - nextPos.column);

                    //the following if statements implement the rules of the game
                    //if a rule is broken then a message will be printed and the code will go back to the start label
                    //if the coordinates entered exist on the board
                    if ((nextPos.row < BOARD_SIZE && nextPos.column < BOARD_SIZE) && (currPos.row < BOARD_SIZE && currPos.column < BOARD_SIZE)) {
                        //if the stack you want to move isn't an empty square
                        if(board[currPos.row][currPos.column].stack != NULL) {
                            //if the stack you want to move is the same color as you and it is valid
                            if ((players[move].playerColor == board[currPos.row][currPos.column].stack->pieceColor)
                                && (board[currPos.row][currPos.column].type == VALID)
                                && (board[nextPos.row][nextPos.column].type == VALID)) {
                                //if the amount of squares you want to move is less than or equal to the number of pieces in the stack you are moving
                                //earlier in the code i squared the value of the difference1 and the value of difference2
                                //here i have squared the number of pieces in the stack
                                //i did this so the values are always positive, i tried using an unisgned integer but that did not work for me
                                if ((difference1 <= board[currPos.row][currPos.column].noPieces *
                                                    board[currPos.row][currPos.column].noPieces) && (
                                            difference2 <= board[currPos.row][currPos.column].noPieces *
                                                           board[currPos.row][currPos.column].noPieces)) {
                                    //if the two coordinates you are moving to are different
                                    if (currPos.row != nextPos.row || currPos.column != nextPos.column) {
                                        //manageMoves function called
                                        manageMoves(board, players, move, currPos.row, currPos.column, nextPos.row, nextPos.column);
                                        printBoard(board);//updated board printed
                                        //number of reserved and captured pieces printed
                                        printf("\n%shas captured %d pieces\n", players[move].playerName, players[move].piecesCaptured);
                                        printf("and has %d reserved pieces\n\n", players[move].piecesReserved);

                                        //the following statements tell the users the rule they have broken and it returns to the label start, giving them another chance to move
                                    } else {
                                        printf("The position you want to move to must be different to the original stack position\nPlease try again.\n\n");
                                        goto start;

                                    }


                                } else {
                                    printf("You can only move a stack up, down, left or right based on the amount of pieces in the stack.\nPlease try again.\n\n");
                                    goto start;

                                }
                            } else {
                                printf("You can only move a stack that shares the same colour as you.\nPlease try again.\n\n");
                                goto start;


                            }

                        } else {
                            printf("You can only move to a valid coordinate that is on the board.\nPlease try again.\n\n");
                            goto start;

                        }
                    } else {
                        printf("You can only enter a valid coordinate that is on the board.\nPlease try again.\n\n");
                        goto start;

                    }

                    //if moveChoice equals 2 eg. player wants to use a reserved piece
                } else if (moveChoice == 2) {
                    start2://start label to allow player to try again if they make an error
                    printf("Enter the row and column coordinates of where you want to place your reserve piece\n");//prompt
                    scanf("%d%d", &nextPos.row, &nextPos.column);//reads in coordinate player wants to add their reserved piece to

                    //if the coordinate exists on the board and the square is valid
                    if (nextPos.row < BOARD_SIZE && nextPos.column < BOARD_SIZE &&
                        (board[nextPos.row][nextPos.column].type == VALID)) {
                        reserve(&board[nextPos.row][nextPos.column], players, move);//calls reserve function
                        printBoard(board);//prints updated board

                        //prints number of pieces captured and reserved by the player
                        printf("\n%shas captured %d pieces\n", players[move].playerName, players[move].piecesCaptured);
                        printf("and has %d reserved pieces\n\n", players[move].piecesReserved);

                    } else {//prints error message and returns to start2
                        printf("You can only enter a coordinate that is on the board.\nnPlease try again.\n\n");
                        goto start2;

                    }
                }
            }
        }
    }
}