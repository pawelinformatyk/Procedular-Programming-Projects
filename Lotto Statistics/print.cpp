#include "typconst.h"
#include "print.h"

void printSex( FILE* fout, player* p );
void printDate( FILE* fout, player* p );
void printBets( FILE* fout, int** bets, int no_bets );

void printResults( int* pNum, player** tab , int size )
{
	FILE* fout = fopen("wyniki.txt", "w" );
	if( !fout )
	{
		printf( "Couldnt create file\n\n" );
		return;
	}

	for( int i = 0; i<size; i++ )
	{
		fprintf( fout, "\n %s %s ", tab[ i ]->name_last, tab[ i ]->name_first );
		printSex( fout, tab[i] );
		fprintf( fout, "%s %s ",tab[ i ]->bank_info.iban.country, tab[ i ]->bank_info.iban.client );
		printDate( fout, tab[ i ] );
		fprintf( fout, "%s\n\n", tab[ i ]->PESEL );
		printBets( fout, tab[ i ]->bets ,tab[i]->no_bets);
		fprintf( fout, "\n--------------------------------------------------------------------------------------------------------------------------------------");
	}
	fprintf( fout,"\n Statistics\n" );
	for( int i = 0; i < MAX_VALUE_BETS; i++ )
	{
		fprintf( fout, " %d wyst = %d", i + 1, pNum[ i ] );
		if( ( i + 1 ) % 10==0 )
			fprintf( fout,"\n" );
	}

	fclose( fout );
}

void printSex( FILE* fout, player* p )
{
	fprintf( fout, "*%s* ", ( p->sex == MALE )?"Male":"Female" );
}

void printDate( FILE* fout, player* p )
{
	fprintf( fout, "%02d:%02d ", p->time.hour, p->time.min );

	switch( p->date.week_day )
	{
		case SUN:
			fprintf( fout, "Sunday " );
			break;
		case MON:
			fprintf( fout, "Monday " );
			break;
		case TUE:
			fprintf( fout, "Tuesday " );
			break;
		case WED:
			fprintf( fout, "Wednesday " );
			break;
		case THU:
			fprintf( fout, "Thursday " );
			break;
		case FRI:
			fprintf( fout, "Friday " );
			break;
		case SAT:
			fprintf( fout, "Saturday " );
			break;
		default: break;
	}
	
	fprintf( fout, "%d/", p->date.day );
	switch( p->date.month )
	{
		case JAN:
			fprintf( fout, "JAN/" );
			break;
		case FEB:
			fprintf( fout, "FEB/" );
			break;
		case MAR:
			fprintf( fout, "MAR/" );
			break;
		case APR:
			fprintf( fout, "APR/" );
			break;
		case MAY:
			fprintf( fout, "MAY/" );
			break;
		case JUN:
			fprintf( fout, "JUN/" );
			break;
		case JUL:
			fprintf( fout, "JUL/" );
			break;
		case AUG:
			fprintf( fout, "AUG/" );
			break;
		case SEP:
			fprintf( fout, "SEP/" );
			break;
		case OCT:
			fprintf( fout, "OCT/" );
			break;
		case NOV:
			fprintf( fout, "NOV/" );
			break;
		case DEC:
			fprintf( fout, "DEC/" );
			break;
	}
	fprintf( fout, "%d ", p->date.year );
}

void printBets( FILE* fout, int** bets,int no_bets )
{
	for( int i = 0; i < no_bets; i++ )
	{
		for( int j = 0; j < MAX_BETS; j++ )
			fprintf( fout, " %d", bets[ i ][ j ] );
		fprintf( fout, "\n" );
	}
}
