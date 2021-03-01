#pragma once

#define CHESSBOARD_SIZE 5
#define HORSE_MOVES 8

//typedef enum { FIRST = 0, SECOND, THIRD, FOURTH, FIFTH, SIXTH, SEVENTH, EIGHTH }mv;

typedef struct 
{
	int x;
	int y;
}point;

int canMove( int** chess_board, int dim, int i_move, int x, int y, int* px, int* py , point* offsets );
int move( int** chess_board, int dim, int nr_move, int x, int y, point* offsets );
int** createChessBoard(int dim);
void freeChessBoard( int*** tab,int dim);
void printChessBoard( int** tab,int dim );
