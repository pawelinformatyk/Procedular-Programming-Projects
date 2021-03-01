#include <iostream>
#include "Interfejs.h"
#include "time.h"

typedef void ( *pTF1 )( int*, int );
typedef void ( *pTF2 )( int*, int,int );

int main( int argc, char* argv[] )
{

	if( argc != 2 )
	{
		printf( "\nError : wrong numbers of arguments , %s cant execute \n", argv[ 0 ] );
		return 1;
	}

#ifdef MX 
	int size = 10000;//atoi( argv[ 1 ] ); //40k 
#else 
	int size =atoi( argv[ 1 ] ); //40k 
#endif

	int* tab = createT( size );
	int* tabSort = createT( size );
	int* tabSort2x = createT( size * 2 );
	int* tabSortT = createT( size );

	randominit( tab, size );

	//void ( *tSort1[] )( int*, int ) = { BBlSort,MiwxedBBlSort,SelectionSort,Insertion,HalfInsertion,HeapSort };
	//void ( *tSort2[] )( int*, int, int ) = { QuickSort,MergeSort1,MergeSort2 };
	pTF1 T1[] = { BBlSort,MiwxedBBlSort,SelectionSort,Insertion,HalfInsertion,HeapSort };
	pTF2 T2[] = { QuickSort };

	const char* tabStr[] = {
	"bubble",
	"mixed bubble",
	"selection",
	"insertion",
	"halfinsertion",
	"heap",
	"quick",
	"merge with tmp array",
	"merge with 2x size array" };

	int j = 0;
	for( int i = 0; i < sizeof( T1 ) / sizeof( pTF1 ); i++ )
	{
		copyTab( tabSort, tab, size );
		clock_t start = clock();
		T1[ i ]( tabSort, size );
		clock_t stop = clock(); 
		printf( "%s :  %g s\n", tabStr[ j++ ], ( double )( stop - start ) / CLOCKS_PER_SEC );
	}

	//quick
	copyTab( tabSort, tab, size );
	clock_t start = clock();
	T2[ 0 ]( tabSort, 0, size - 1 );
	clock_t stop = clock();
	printf( "%s :  %g s\n", tabStr[ j++ ], (double)(stop - start) / CLOCKS_PER_SEC );

	//merge with tmp
	copyTab( tabSortT, tab, size );
	start = clock();
	MergeSort1( tabSort, tabSortT, 0, size - 1 );
	stop = clock();
	printf( "%s :  %g s\n", tabStr[ j++ ], (double)(stop - start) / CLOCKS_PER_SEC );

	//merge with 2x size array
	copyTab( tabSort2x, tab, size );
	start = clock();
	MergeSort2( tabSort2x, 0, size - 1, 2 * size );
	stop = clock(); 
	printf( "%s :  %g s\n", tabStr[ j++ ], (double)(stop - start) / CLOCKS_PER_SEC );

	freeTab( &tabSort2x );
	freeTab( &tab );
	freeTab( &tabSort );
	freeTab( &tabSortT );

	return 0;
}
