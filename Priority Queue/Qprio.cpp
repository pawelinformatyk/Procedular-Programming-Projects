#include "Qprio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

PQueue* PQInit( int size )
{
	PQueue* pq = ( PQueue* )calloc( 1, sizeof( PQueue ) );
	if( !pq )
	{
		printf( "Alloc error\n\n" );
		return NULL;
	}
	pq->max_size = size;
	pq->queue = ( PQItem** )calloc( size, sizeof( PQItem* ) );
	if( !pq->queue )
	{
		free( pq );
		printf( "Alloc error\n\n" );
		return NULL;
	}
	return pq;
}

int PQisEmpty( PQueue* pq )
{
	return !pq->curr_size;
}

void PQClearQueue( PQueue* pq )
{
	for( int i = 0; i < pq->curr_size; i++ )
	{
		free( pq->queue[ i ]->pInfo );
		free( pq->queue[ i ] );
	}
	pq->curr_size = 0;
}

void PQRealease( PQueue** pq )
{
	PQClearQueue( *pq );
	free( ( *pq )->queue );
	free( *pq );
	*pq = NULL;
}

void PQEnqueue( PQueue* pq, QPRIORINFO* pInfo, int nPrior )
{
	if( pq->curr_size == pq->max_size )
	{
		printf( "Q is full\n\n" );
		return;
	}
	PQItem* item = ( PQItem* )malloc( sizeof( PQItem ) );
	if( !item )
	{
		printf( "Alloc error\n\n" );
		return;
	}
	item->nPrior = nPrior;
	item->pInfo = pInfo;

	pq->queue[ pq->curr_size ] = item;
	if(pq->curr_size>0)
		UpdateUp( pq, 0, pq->curr_size );
	pq->curr_size++;
}

void UpdateUp( PQueue* pq, int l, int p )
{
	if( l >= p )
		return;

	PQItem* tmp = pq->queue[ p ];
	int par = ( p - 1 ) / 2;
	while( par >= 0 && tmp->nPrior > pq->queue[ par ]->nPrior )
	{
		pq->queue[ p ] = pq->queue[ par ];
		p = par;
		par = ( par - 1 ) / 2;
	}
	pq->queue[ p ] = tmp;
}

void IncreaseKey( PQueue* pq, QPRIORINFO* pInfo, int nPrior )
{
	int i = 0;
	
	while( i < pq->curr_size && !compare( pq->queue[ i ]->pInfo, pInfo ) )i++; //szukanie elementu

	if( i >= pq->curr_size )
	{
		printf( "Couldnt find element\n" );
		return;
	}

	PQItem* tmp = pq->queue[ i ];
	if( tmp->nPrior > nPrior )
	{
		printf( "Can't change priority\n\n");
		return;
	}

	tmp->nPrior = nPrior;
	UpdateUp( pq, 0,i );
}

QPRIORINFO* PQDequeue( PQueue* pq )
{
	if( PQisEmpty( pq ) )
	{
		printf( "Q is empty\n\n" );
		return 0;
	}
	QPRIORINFO* dq = pq->queue[ 0 ]->pInfo;
	
	pq->queue[ 0 ] = pq->queue[ pq->curr_size - 1 ];
	pq->queue[ pq->curr_size - 1 ] = NULL;
	pq->curr_size--;
	if(pq->curr_size>1)
	  UpdateDown( pq, 0, pq->curr_size - 1 );
	
	return dq;
}

void UpdateDown( PQueue* pq, int l, int p )
{
	if( l >= p )
		return;
	
	int i = l;
	int j = 2 * i + 1;
	PQItem* temp = pq->queue[ i ]; 
	while( j <= p )
	{
		if( j < p )
			if( pq->queue[ j ]->nPrior < pq->queue[ j + 1 ]->nPrior ) 
				j++;  
		if( temp->nPrior >= pq->queue[ j ]->nPrior ) 
			break;
		
		pq->queue[ i ] = pq->queue[ j ];  
		i = j; 
		j = 2 * i + 1;
	}
	pq->queue[ i ] = temp;
}

void DecreaseKey( PQueue* pq, QPRIORINFO* pInfo, int nPrior )
{
	int i=0;
	
	while( i < pq->curr_size && !compare( pq->queue[ i ]->pInfo, pInfo ) )i++;

	if(  i>=pq->curr_size)
	{
		printf( "Couldnt find element" );
		return;
	}
	
	PQItem* tmp = pq->queue[ i ];
	if( tmp->nPrior < nPrior )
	{
		printf( "Can't change priority\n\n" );
		return;
	}

	tmp->nPrior = nPrior;
	UpdateDown( pq, i, pq->curr_size-1 );
}

int compare( QPRIORINFO* p1, QPRIORINFO* p2 )
{
	if( p1->key == p2->key )
		return 1;
	return 0;
}

void PQPrint( PQueue* pq, int l, int r )
{//inorder
	if( l >= pq->curr_size )return;

	PQPrint( pq, 2 * l + 1, pq->curr_size );
	printf( " %d |", pq->queue[ l ]->nPrior );
	PQPrint( pq, 2 * l + 2, pq->curr_size );
}

void drawTree( PQueue* pq )
{
	if( PQisEmpty( pq ) )
	{
		printf( "Q is empty\n\n");
		return;
	}

	printf( "               Tree \n\n Prio ");
	for( int i = 0; i < pq->curr_size; i++ )
		printf( " %d |", pq->queue[ i ]->nPrior );
	printf( "\n Index    " );
	for( int i = 0; i < pq->curr_size; i++ )
		printf( " %d |",i);
	printf( "\n\n" );

	int LINE_WIDTH = 100;
	int* print_pos = ( int* )calloc( pq->curr_size, sizeof( int ));
	if( !print_pos )
	{
		printf( "alloc error\n\n" );
		return;
	}
	int i, j, k, pos, x = 1, level = 0;

	print_pos[ 0 ] = 0;
	for( i = 0, j = 1; i < pq->curr_size; i++, j++ )
	{
		pos = print_pos[ (i-1)/2 ] + ( i % 2 ? -1 : 1 ) * ( LINE_WIDTH / ( (int)pow( 2, level + 1 ) ) + 1 );

		for( k = 0; k < pos - x; k++ ) 
			printf( "%c", i == 0 || i % 2 ? ' ' : '-' );
		printf( "%d", pq->queue[ i ]->nPrior );

		print_pos[ i ] = x = pos + 1;
		if( j == pow( 2, level ) )
		{
			printf( "\n" );
			level++;
			x = 1;
			j = 0;
		}
	}
	free( print_pos );
	printf( "\n\n" );
}

QPRIORINFO* copyElem( QPRIORINFO* pInfo )
{
	QPRIORINFO* tmp = ( QPRIORINFO* )malloc( sizeof( QPRIORINFO ) );
	if( !tmp )
	{
		printf( "Alloc error\n\n" );
	}
	memcpy( tmp, pInfo, sizeof( QPRIORINFO* ) );
	return tmp;
}