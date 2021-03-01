#include "typconst.h"
#include "data.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

int setSex( player* p, char c );
int setDate( player* p, int d, int m, int y );
int setTime( player* p, int m, int h );
int addMemPlayers( player*** pTab, int curr_size );
int addMemBets( int*** pBets, int curr_size );


int readData( player*** pTab, const char* file_name )
{
	FILE* fin = fopen( file_name, "r" );
	if( !fin )
	{
		printf( "Couldnt find file\n\n" );
		return 0;
	}

	int i_pl = 0;
	int max_pl = 0;
	player** tab = *pTab;
	char c;
	while(  !feof(fin) )
	{
		if(( c = fgetc( fin ) ) != '*')break;

		if( i_pl == max_pl )
			max_pl += addMemPlayers( &tab, i_pl );
		if( i_pl == max_pl )
			break;
		
		player* p = tab[ i_pl ] = ( player* )calloc( 1, sizeof( player ) );
		if( !p )
		{
			printf( "Alloc error\n\n" );
			break;
		}

		char sex = 's';
		int hour = 0;
		int min = 0;
		int day = 0;
		int month = 0;
		int year = 0;
		
		fscanf( fin, "%s %s %c %4c%2c%2c%3c %2c%2c%8c%16c %d:%d %d/%d/%d %s\n", 
				p->name_last,
				p->name_first,
				&sex,
				p->bank_info.swift.bank,
				p->bank_info.swift.country,
				p->bank_info.swift.location,
				p->bank_info.swift.branch,
				p->bank_info.iban.country,
				p->bank_info.iban.control_sum,
				p->bank_info.iban.bank,
				p->bank_info.iban.client,
				&hour, &min, &day, &month, &year,
				p->PESEL );
		
		if( !setDate( p, day, month, year ) || !setSex( p, sex ) || !setTime( p, min, hour ) )
		{
			printf( "Player wrong data\n\n" );
			break;
		}

		//Bets
		int i_bets = 0;  
		int max_bets = 0;
		int** bets = p->bets;
		//char d;
		while( ( c = fgetc( fin) ) != '*' && !feof( fin ) )
		{
			ungetc( c, fin );
			if( i_bets == max_bets )
				max_bets += addMemBets( &bets, i_bets );
			if( i_bets == max_bets )
				break;//alokacja sie nie powiodla

			int* bet=bets[ i_bets ] = ( int* )calloc( MAX_BETS, sizeof( int ) ); 
			if( !bet )
			{
				printf( "Alloc error\n\n" );
				break;
			}
			
			for( int j = 0; j < MAX_BETS; j++, bet++ )
			{
				fscanf( fin, " %d", bet );
				if( *bet > MAX_VALUE_BETS || *bet < 1 )
				{
					printf( "Wrong data\n\n" );
					break;
				}
			}
			i_bets++;
			fscanf( fin, "\n" );
			c = fgetc( fin );
			if( c == '*' )
			{
				ungetc( c, fin );
				break;
			}
			else if( feof( fin ) )
				break;
			else	ungetc( c, fin );

		}
		tab[ i_pl ]->no_bets = i_bets;
		tab[ i_pl++ ]->bets = bets;

		//if( !feof( fin ) )
		//	ungetc( c, fin );
		//else break;

	}
	*pTab = tab;
	fclose( fin );
	return i_pl;
}

int addMemPlayers( player*** pTab, int curr_size )
{
	player** tmp = ( player** )realloc( *pTab, ( ALLOC_PLAYER + curr_size ) * sizeof( player* ) );
	if( !tmp )
	{
		printf( "Realloc error\n\n" );
		return 0;
	}
	memset( tmp +curr_size, 0, ALLOC_PLAYER * sizeof( player* ) );
	*pTab = tmp;

	return ALLOC_PLAYER;
}

int addMemBets( int*** pBets, int curr_size )
{
	int** tmp = ( int** )realloc( *pBets, ( ALLOC_BET + curr_size ) * sizeof( int* ) );
	if( !tmp )
	{
		printf( "Realloc error\n\n" );
		return 0;
	}
	memset( tmp+ curr_size , 0, ALLOC_BET * sizeof( int* ) );
	*pBets = tmp;

	return ALLOC_BET;
}

void freeMem( player*** pTab, int size )
{
	for( int i = 0; i < size; i++ )
	{
		player* p = ( *pTab )[ i ];
		for( int j = 0; j < p->no_bets; j++ )
			free( p->bets[ j ] ) ;
		free( p->bets );
		free( p );
	}
	free( *pTab );
	*pTab = NULL;
}

int setSex( player* p, char c )
{
	if( c != 'f' && c != 'F' && c != 'm' && c != 'M' )
		return 0;

	if( c == 'm' || c == 'M' )
		 p->sex = MALE;
	else p->sex = FEMALE;
	return 1;
}

int setDate( player* p, int d, int m, int y )
{
	if( d < 1 || d>31 || m < 1 || m>12 || y < 1900  )
		return 0;
	
	p->date.year = y;
	switch( m )
	{
		case 1:
			p->date.month = JAN;
			break;
		case 2:
			p->date.month = FEB;
			break;
		case 3:
			p->date.month = MAR;
			break;
		case 4:
			p->date.month = APR;
			break;
		case 5:
			p->date.month = MAY;
			break;
		case 6:
			p->date.month = JUN;
			break;
		case 7:
			p->date.month = JUL;
			break;
		case 8:
			p->date.month = AUG;
			break;
		case 9:
			p->date.month = SEP;
			break;
		case 10:
			p->date.month = OCT;
			break;
		case 11:
			p->date.month = NOV;
			break;
		case 12:
			p->date.month = DEC;
			break;
	}
	p->date.day = d;
	//p->date.week_day = (weekDay)( ( d += m < 3?y--:y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400 ) % 7);

	time_t T = time( NULL );
	struct tm* t_time = localtime( &T );
	t_time->tm_mday = d;
	t_time->tm_mon = m - 1;
	t_time->tm_year = y - 1900;
	T = mktime( t_time );
	t_time = localtime( &T );

	switch( t_time->tm_wday )
	{
		case 0:
			p->date.week_day = SUN;
			break;
		case 1:
			p->date.week_day = MON;
			break;
		case 2:
			p->date.week_day = TUE;
			break;
		case 3:
			p->date.week_day = WED;
			break;
		case 4:
			p->date.week_day = THU;
			break;
		case 5:
			p->date.week_day = FRI;
			break;
		case 6:
			p->date.week_day = SAT;
			break;
		default: return 0;
			}

	return 1;
}
int setTime( player* p, int m, int h )
{
	if( m < 0 || m > 59 || h > 24 || h < 0 )
		return 0;
	p->time.min = m;
	p->time.hour = h;
	return 1;
}