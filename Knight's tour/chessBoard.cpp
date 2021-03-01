#include "chessBoard.h"
#include <stdlib.h>
#include <stdio.h>

int canMove( int** chess_board, int dim, int i_move, int x, int y, int* px, int* py, point* offsets )
{
	*px = x + offsets[ i_move ].x;
	*py = y + offsets[ i_move ].y;

	if( *px < 0 || *px >= dim || *py < 0 || *py >= dim || chess_board[ *px ][ *py ] != 0 )
		return 0;
	return 1;
}

int move( int** chess_board, int dim, int nr_move, int x, int y, point* offsets )
{
	chess_board[ x ][ y ] = nr_move;

	if( nr_move == dim * dim )
		return 1;
	
	int nx, ny;
	for( int i = 0; i < HORSE_MOVES; i++ )
		if( canMove( chess_board, dim, i, x, y, &nx, &ny, offsets ) )
			if( move( chess_board, dim, nr_move + 1, nx, ny, offsets ) )
				return 1;
	chess_board[ x ][ y ] = 0;

	return 0;
}

int** createChessBoard(int dim)
{
	int** tab = ( int** )calloc( dim, sizeof( int* ) );
	if( !tab )
	{
		printf( " BLAD : alokacji pamieci\n\n" );
		return NULL;
	}
	
	*tab = ( int* )calloc( dim * dim, sizeof( int ) );
	if( !(*tab) )
	{
		free( tab );
		printf( " BLAD : alokacji pamieci\n\n" );
		return NULL;
	}

	for( int i = 0; i < dim; i++ )
		tab[ i ] = *tab + i*dim;//przewiazanie do wierszy

	return tab;
}

void freeChessBoard( int*** pTab,int dim)
{
	free( **pTab );
	free( *pTab );
	*pTab = NULL;
}

void printChessBoard( int** tab ,int dim)
{
	for( int i = 0; i < dim; i++ )
	{
		printf( " %d\t", dim - i );
		for( int j = 0; j < dim; j++ )
			printf( "%2d ", tab[ j ][ dim-1-i ] );
		printf( "\n\n" );
	}
	printf( "\n\t" );
	for( int i = 0; i < dim; i++ )
		printf( "%2d ", i+1 );
}
