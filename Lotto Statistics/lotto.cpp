#include <iostream>
#include "typconst.h"
#include "print.h"
#include "data.h"

void HeapCheck(); 
void CalcStat( int* pNum, player** tab, int size);
void sort( player** tab, int size );  

int main( int argc, char* argv[] )
{
	if( argc!=2)
	{
		printf("1 argument required\n\n");
		return -1;
	}

	player** players = NULL;
	int no_players = readData( &players, argv[ 1 ] );
	if( no_players == 0 )
	{
		printf( "Couldnt read players from file\n\n" );
		return 2;
	}

	int* stats_bets = ( int* )calloc( MAX_VALUE_BETS, sizeof( int ) );
	if( !stats_bets )
	{
		printf( "Alloc error\n\n" );
		return 0;
	}

	sort( players, no_players );
	CalcStat( stats_bets, players, no_players );
	printResults( stats_bets, players, no_players );
	freeMem( &players, no_players );
	free( stats_bets );
	HeapCheck();	

	return 1;
}

void HeapCheck()
{
	int heapstatus = _heapchk();
	switch( heapstatus )
	{
		case _HEAPOK:
			printf( " OK - heap is fine\n\n" );
			break;
		case _HEAPEMPTY:
			printf( " OK - heap is empty\n\n" );
			break;
		case _HEAPBADBEGIN:
			printf( "ERROR - bad start of heap\n\n" );
			break;
		case _HEAPBADNODE:
			printf( "ERROR - bad node in heap\n\n" );
			break;
	}
}

void CalcStat( int* pNum, player** tab, int size )
{
	for( int i = 0; i < size; i++ )
	{
		player* p = tab[ i ];
		for( int j = 0; j < p->no_bets; j++ )
		{
			int* bet = p->bets[ j ];
			for( int k = 0; k < MAX_BETS; k++, bet++ )
				pNum[ *bet - 1 ]++;
		}
	}
}

void sort( player** tab, int size )
{
	for( int i = 0; i < size - 1; i++ )
	{
		player* min = tab[ i ];
		int i_min = i;
		for( int j = i + 1; j < size; j++ )
		{
			int cmp = strcmp( min->name_last, tab[ j ]->name_last );
			if( cmp>0 )
			{
				min = tab[ j ];
				i_min = j;
			}
			else if( cmp == 0 )//sort by last_name,firstname
				if( strcmp( min->name_first, tab[ j ]->name_first ) > 0 )
				{
					min = tab[ j ];
					i_min = j;
				}
		}
		tab[ i_min ] = tab[ i ];
		tab[ i ] = min;
	}
}