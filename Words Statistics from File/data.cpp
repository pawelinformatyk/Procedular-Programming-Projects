#include "data.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

treeElem* readData( const char* file_name )
{
	FILE* fin = fopen( file_name, "r" );
	if( !fin )
	{
		printf( "Coudlnt open file\n" );
		return NULL;
	}

	treeElem* tree = NULL;
	char c;
	int line_number = 1;
	char word[ WORD_LENGTH ];

	while( !feof( fin ) )
	{
		int i = 0;
		while( ( c = fgetc( fin ) ) && i < WORD_LENGTH )
		{
			if( isChar( c ) )
				word[ i++ ] = c;
			else break;
		}

		if( i && notDigit( word[ 0 ] ) )
		{
			word[ i ] = '\0';														
			tree = findAndInsert( word, tree, line_number );
		}

		if( c == '\n' )
			line_number++;
	}

	fclose( fin );

	return tree;
}

int isChar( char c )
{
	return	( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || ( c == '_' ) || ( c >= '0' && c <= '9' ) );
}

int notDigit( char c )
{
	return !( c >= '0' && c <= '9' );
}

