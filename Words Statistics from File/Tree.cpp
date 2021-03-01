#include "Tree.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

treeElem* newTree( char* word, int nLine )
{
	treeElem* tree = ( treeElem* )calloc( 1, sizeof( treeElem ) );
	if( !tree )
	{
		printf( "\nAlloc error\n" );
		return NULL;
	}
	
	tree->pWord = ( char* )malloc( strlen( word ) + 1 );
	if( !tree->pWord )
	{
		free( tree );
		printf( "\nAlloc error\n" );
		return NULL;
	}

	strcpy( tree->pWord, word );
	tree->count = 1;
	tree->lineList = fqCreate();
	fqEnqueue( tree->lineList, nLine );

	return tree;
}

treeElem* findAndInsert( char* word, treeElem* p, int nLine )
{
	if( p == NULL )
		return newTree( word, nLine );

	switch( compare( word, p->pWord ) )
	{
		case -1:
			p->pLeft = findAndInsert( word, p->pLeft, nLine );
			break;
		case 1:
			p->pRight = findAndInsert( word, p->pRight, nLine );
			break;
		case 0:
			addLine( &( p->lineList ), nLine );
			p->count++;
			break;
		default:
			printf( " ERROR : findandinsert\n\n" );
			break;
	}

	return p;
}

int compare( char* word1, char* word2 )
{
	char* w1 = ( char* )malloc( strlen( word1 ) + 1 );
	char* w2 = ( char* )malloc( strlen( word2 ) + 1 );
	int res;

	if( w1 && w2 )
	{
		strcpy( w1, word1 );
		strcpy( w2, word2 );
		_strlwr( w1 );
		_strlwr( w2 );

		res = strcmp( w1, w2 );											
	}
	else
	{
		printf( "\nAlloc error\n" );
		res = 2;
	}

	free( w1 );
	free( w2 );
	return res;
}

void addLine( fqueue** LineList, int nLine )
{
	if( nLine == ( *LineList )->pTail->key )
		return;						             
	fqEnqueue( *LineList, nLine );
}

void preOrder( treeElem* p, FILE* fout )
{
	if( p == NULL )
		return;

	printElem( p, fout );
	preOrder( p->pLeft, fout );
	preOrder( p->pRight, fout );
}

void inOrder( treeElem* p, FILE* fout )
{
	if( !p )
		return;

	inOrder( p->pLeft, fout );
	printElem( p, fout );
	inOrder( p->pRight, fout );
}

void postOrder( treeElem* p, FILE* fout )
{
	if( p == NULL )
		return;

	postOrder( p->pLeft, fout );
	postOrder( p->pRight, fout );
	printElem( p, fout );
}

void printElem( treeElem* p, FILE* fout )
{
	treeElem* tmp = p;
	fprintf( fout, "%-16s %-2d       line: ", tmp->pWord, tmp->count );

	fqItem* i = tmp->lineList->pHead;
	while( i )
	{
		fprintf( fout, "%2d, ", i->key );
		i = i->pNext;
	}
	fprintf( fout, "\n" );
}

treeElem* freeTree( treeElem* pRoot )
{
	if( pRoot )
	{
		freeTree( pRoot->pLeft );
		freeTree( pRoot->pRight );
		fqRemove( &( pRoot->lineList ) );
		free( pRoot->pWord );
		free( pRoot );
	}
	return NULL;
}
