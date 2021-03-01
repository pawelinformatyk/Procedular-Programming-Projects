#include "Tree.h"
#include "data.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

int main( int argc, char* argv[] )
{
	if( argc != 3 )
	{
		printf( "2 arguments required\n\n" );
		return -1;
	}

	treeElem* tree = readData( argv[ 1 ] );
	if( !tree )
	{
		printf( "Couldnt load data from file\n\n" );
		return 2;
	}

	FILE* fout = fopen( argv[ 2 ], "w" );
	if( fout == NULL )
	{
		printf( "Couldnt load data from file\n\n" );
		return 0;
	}

	fprintf( fout, "Words Statistics\n\n" );
	fprintf( fout, "InOrder:\n\n" );
	inOrder( tree, fout );
	//preOrder( tree, fout );
	//postOrder( tree, fout );

	fclose( fout );
	tree = freeTree( tree );

	return 1;
}