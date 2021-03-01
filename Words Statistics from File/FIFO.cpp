#include "FIFO.h"
#include <stdlib.h>
#include <stdio.h>

void fqDel( fqueue* q );
fqueue* fqCreate()
{
	fqueue* q = ( fqueue* )calloc( 1, sizeof( fqueue ) );
	if( !q )
	{
		printf( "\nAlloc error\n" );
		return NULL;
	}
	q->pHead = q->pTail = NULL;
	return q;
}
int fqIsEmpty( fqueue* q )
{
	return !q->pHead;
}
void fqEnqueue( fqueue* q, int x )
{
	fqItem* item = ( fqItem* )calloc( 1, sizeof( fqItem ) );
	if( !item )
	{
		printf( "\nAlloc error\n" );
		return;
	}
	item->key = x;

	if( !fqIsEmpty( q ) )
		q->pTail->pNext = item;
	else q->pHead = item;

	q->pTail = item;
}
int fqDequeue( fqueue* q )
{
	if( fqIsEmpty( q ) )
	{
		printf( "Q is empty\n\n" );
		return -1;
	}
	int x = q->pHead->key;
	fqDel( q );
	return x;
}
void fqClear( fqueue* q )
{
	while( q->pHead )
		fqDel( q );
}
void fqRemove( fqueue** q )
{
	fqClear( *q );
	free( *q );
	*q = NULL;
}
void fqDel( fqueue* q )
{
	fqItem* copy = q->pHead;
	q->pHead = copy->pNext;
	if( !q->pHead )q->pTail = NULL; //jesli jest pusta po usunieciu
	free( copy );
}
void fqDisplay( fqueue* q )
{
	if( fqIsEmpty( q ) )
	{
		printf( "Q is empty\n\n" );
		return;
	}
	fqItem* i = q->pHead;
	while( i )
	{
		printf( "%d, ", i->key );
		i = i->pNext;
	}
	printf( "\n" );
}