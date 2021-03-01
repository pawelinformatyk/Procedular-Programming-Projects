#include <iostream>
#include "Qprio.h"
#include <time.h>

int main()
{
	printf( "Priority queue\n\n" );
	PQueue* pq = PQInit( 30);

	srand( ( unsigned int )time( NULL ) );
	for( int i = 0; i < pq->max_size-14; i++ )
	{
		QPRIORINFO* item = ( QPRIORINFO* )calloc( 1, sizeof( QPRIORINFO ) );
		if( !item )
		{
			printf( "Alloc error\n\n" );
			continue;
		}
		PQEnqueue( pq, item, rand() % 20 + 1 );
	}

	QPRIORINFO* item = ( QPRIORINFO* )calloc( 1, sizeof( QPRIORINFO ) );
	if( !item )
	{
		printf( "Alloc error\n\n" );
		return 0;
	}
	item->key = 4;
	PQEnqueue( pq, item, 4 );
	drawTree( pq );
	IncreaseKey( pq, item, 17 );
	drawTree( pq );
	DecreaseKey( pq, item, 7 );
	drawTree( pq );

	for( int i = 0; i < pq->max_size-26; i++ )
	{
		printf( "Delete %d \n", pq->queue[ 0 ]->nPrior );
		free( PQDequeue( pq ) );
	}
	drawTree( pq );
	PQPrint( pq, 0, pq->curr_size );
	
	printf( " \n\nClear Q\n\n" );
	PQClearQueue( pq );
	PQRealease( &pq );

	return 1;
}
