#include <iostream>
#include "Interfejs.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

void Merge1( int* pTab, int* pTabT, int l, int h, int r );
void Merge2( int* pTab, int l, int h, int r ,int size);
void UpDate( int* pTab, int l, int r );

int* createT( int size )
{
	int* pTab = ( int* )malloc( sizeof( int ) * size );
	memset( pTab, 0, sizeof( int ) * size );
	if( !pTab )
	{
		pTab = NULL;
		printf( "alloc error\n" );
	}
	return pTab;
}
void freeTab( int** pTab )
{
	free( *pTab );
	pTab = NULL;
}
void printTab( int* pTab, int size )
{
	for( int i = 0; i < size; i++ )
	{
		if( i % 20 == 0 )
			printf( "\n" );
		printf( "%d ", pTab[ i ] );
	}
}
void init( int* pTab, int size, int val )
{
	for( int i = 0; i < size; i++ )
		pTab[ i ] = val;
}
void randominit( int* pTab, int size )
{
	srand((unsigned int) time( NULL ) );
	for( int i = 0; i < size; i++ )
		pTab[ i ] = rand()%size;
}
void copyTab( int* pTabTo, int* pTabFrom, int size )
{
	//for( int i = 0; i < size; i++ )
		//pTabTo[ i ] = pTabFrom[ i ];
	memcpy( pTabTo, pTabFrom, sizeof(int)*size );
}
void BBlSort( int* pTab, int size )
{
	for( int i = 0; i < size; i++ )
		for( int j = size - 1; j > i; j-- )
			if( pTab[ j ] < pTab[ j - 1 ] )
			{
				int tmp = pTab[ j ];
				pTab[ j ] = pTab[ j - 1 ];
				pTab[ j - 1 ] = tmp;
			}
}
void MiwxedBBlSort( int* pTab, int size ) 
{
	/*	/*za kazdym razem najwiekszy laduje na ostatnim miejscu a najmnniejszy na pierwszym miejscu
	for( int i = 1; i < size; i++ )
	{
		//w prawo
		for( int j = i - 1; j < size - i; j++ )
			if( pTab[ j ] > pTab[ j + 1 ] )
			{
				int t = pTab[ j ];
				pTab[ j ] = pTab[ j + 1 ];
				pTab[ j + 1 ] = t;
			}
		// w lewo
		for( int j = size - i; j >= i; j-- )
			if( pTab[ j ] < pTab[ j - 1 ] )
			{
				int t = pTab[ j ];
				pTab[ j ] = pTab[ j - 1 ];
				pTab[ j - 1 ] = t;
			}
	}*/
	int l = 1;
	int p = size-1;
	int k = size-1;
	do
	{
		for( int j = p; j >= l; j-- )
			if( pTab[ j - 1 ] > pTab[ j ] )
			{
				int t = pTab[ j - 1 ];
				pTab[ j - 1 ] = pTab[ j ];
				pTab[ j ] = t;
				k = j;      
			}
		l = k + 1;
		
		for( int j = l; j <= p; j++ )
			if( pTab[ j - 1 ] > pTab[ j ] )
			{
				int t = pTab[ j - 1 ];
				pTab[ j - 1 ] = pTab[ j ];
				pTab[ j ] = t;
				k = j;
			}
		p = k - 1;
	}while( l < p );
}
void SelectionSort( int* pTab, int size )
{
	for( int i = 0; i < size - 1; i++ )
	{
		int min = pTab[ i ];
		int imin = i;
		for( int j = i + 1; j < size; j++ )
		{
			if( min > pTab[ j ] )
			{
				min = pTab[ j ];
				imin = j;
			}
		}
		pTab[ imin ] = pTab[ i ];
		pTab[ i ] = min;
	}
}
void Insertion( int* pTab, int size )
{
	for( int i = 1; i < size; i++ )
	{
		int x = pTab[ i ];
		int j = i - 1;
		while( j >= 0 && pTab[ j ] > x )
		{
			pTab[ j + 1 ] = pTab[ j-- ];
			
		}
		pTab[ j + 1 ] = x;
	}
}
void HalfInsertion( int* pTab, int size )
{
	for( int i = 1; i < size; i++ )
	{
		int x= pTab[ i ];
		int l = 0;
		int r = i - 1;
		 
		while( l <= r )
		{
			int h = ( l + r ) / 2;
			if( x < pTab[ h ] )
				r = h - 1;
			else
				l = h + 1;
		}

		for( int j = i - 1; j >= l; j-- )
			pTab[ j + 1 ] = pTab[ j ];
		pTab[ l ] = x;
	}
}
void QuickSort( int* pTab, int L, int R )
{
	int i = L;
	int j = R;
	int h = pTab[ ( L + R ) / 2 ];

	// przerzucam z lewej strony tablicy elementy wieksze od srodkowego i z prawej strony elementy mniejsze póki nie min¹ siê indeksy 
	while( i < j )
	{
		while( pTab[ i ] < h )i++;
		while( pTab[ j ] > h )j--;
		
		if( i <= j )
		{
			int t = pTab[ i ];
			pTab[ i++ ] = pTab[ j ];
			pTab[ j-- ] = t;
		}
	}
	//dziele tablice na dwie ktore sortuje jak poprzednio 
	if( L < j ) QuickSort( pTab, L, j );
	if( R > i ) QuickSort( pTab, i, R );
}
void MergeSort2(int* pTab, int l, int r,int size) 
{
	if (l < r)
	{
		int h = (l + r) / 2;
		MergeSort2(pTab, l, h,size);
		MergeSort2(pTab, h + 1, r,size);
		Merge2(pTab, l, h, r,size);
	}
}

void Merge2( int* pTab, int l, int h, int r, int size )
{
	for( int i = l, j = size / 2 + l; i <= r; i++, j++ )
		pTab[ j ] = pTab[ i ];

	int i = l + size / 2;
	int j = h + 1 + size / 2;
	int k = l;

	while( i <= h + size / 2 && j <= r + size / 2 )
	{
		if( pTab[ i ] < pTab[ j ] )
			pTab[ k++ ] = pTab[ i++ ];
		else
			pTab[ k++ ] = pTab[ j++ ];
	}
	while( i <= h + size / 2 )
		pTab[ k++ ] = pTab[ i++ ];
	while( j <= r + size / 2 )
		pTab[ k++ ] = pTab[ j++ ];
}
void MergeSort1( int* pTab, int* pTabT,int l, int r )
{
	if( l < r )
	{
		int h = ( l + r ) / 2;
		MergeSort1( pTab,pTabT ,l, h );
		MergeSort1( pTab, pTabT,h + 1, r );
		Merge1( pTab, pTabT, l, h, r );
		copyTab( pTabT, pTab, r+1 );
	}
}
void Merge1( int* pTab,int* pTabT, int l, int h, int r )
{
	int i = l;
	int j = h + 1;
	int k = l;
	
	while( i <= h && j <= r )
	{
		if( pTabT[ i ] > pTabT[ j ] )
			pTab[ k++ ] = pTabT[ j++ ];
		else
			pTab[ k++ ] = pTabT[ i++ ];
	}
	while( i <= h )
		pTab[ k++ ] = pTabT[ i++ ];

	while( j <= r )
		pTab[ k++ ] = pTabT[ j++ ];
}
void HeapSort(int* pTab, int size)
{
	for( int i = size / 2; i >= 0; i-- )
		UpDate( pTab, i, size - 1 );//ustawiam kopiec, kazdy potomek bedzie niewiekszy od rodzica ,na koniec na szczycie(0) bedzie min wart
	for( int i = size - 1; i >= 1; i-- )
	{
		//
		/*zamieniam ostatni z pierwszym i przywracam warunek kopca */
		int t = pTab[ 0 ];
		pTab[ 0 ] = pTab[ i ];
		pTab[ i ] = t;
		UpDate( pTab, 0, i - 1 );
	}
}
void UpDate( int* pTab, int l, int p )
{
	/*
	if( q == p )
		return;
	while( q <= p )
	{
		/* sprawdzam ile potomkow ma rodzic , sprawdzam ktory jest mniejszy  , wstawiam go za rodzica , ide glebiej
		int l = 2 * q;
		if( l > p ) return;//nie ma potomkow
		int r = l + 1;
		int min = l;
		if( r <= p ) //ma przynajmniej jednego
			if( pTab[ r ] > pTab[ l ] )
				min = r;
		if( pTab[ q ] > pTab[ min ] )
			break;

		int t = pTab[ q ];
		pTab[ q ] = pTab[ min ];
		pTab[ min ] = t;

		q = min;
	}*/
	if( l == p )return;
	int i = l;
	int j = 2 * i + 1;
	int x = pTab[ i ];//rodzic 
	while( j <= p )
	{
		if( j < p )
			if( pTab[ j ] < pTab[ j + 1 ] ) 
				j++;// right child
		if( x >= pTab[ j ] )break;  // jesli rodzic jest wiekszy warunek kopca jest zachowany wiev break 

		pTab[ i ] = pTab[ j ]; // zamieniam wiekszy potomek z rodzicem , 
		i = j;// nowy rodzic i dziecko 
		j = 2 * i + 1;
	}
	pTab[ i ] = x;
}
int isSorted( int* pTab, int size )
{
	for( int i = 0; i < size - 1; i++ )
		if( pTab[ i ] > pTab[ i + 1 ] )return 0;
	return 1;
}