#include <iostream>
#include "chessBoard.h"

#define WAR

int main( int argc, char* argv[] )
{
	if( argc != 3 )
	{
		printf( "2 arguments required\n\n" );
		return -1;
	}

	//chessboard (wsp)
	//  y0
	//  5
	//	4
	//  3
	//  2
	//  1
	//	  1 2 3 4 5  x0 

	#ifndef WAR
	int x0 = atoi( argv[ 1 ] );//1
	int y0 = atoi( argv[ 2 ] );//5
	#else
	int x0 = 4;
	int y0 = 4;
	#endif
	
	if( x0 > CHESSBOARD_SIZE || x0 < 1 || y0 > CHESSBOARD_SIZE || y0 < 1 )
	{
		printf( "Wrong parameters\n\n" );
		return 0;
	}

	int** chess_board = createChessBoard( CHESSBOARD_SIZE );
	point offsets[ HORSE_MOVES ] = { {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1} };
									// 0	  1		  2		  3		  4		   5	   6	   7

	if( move( chess_board, CHESSBOARD_SIZE, 1, x0-1, y0-1, offsets ) )
		printChessBoard( chess_board, CHESSBOARD_SIZE );
	else
		printf( "Cou;dnt find tour\n\n" );

	freeChessBoard( &chess_board, CHESSBOARD_SIZE );

	return 1;
}
