#ifndef DSTACK_H
#define DSTACK_H

typedef struct tagStackItemD{
	
	double fKey;
	tagStackItemD *pNext;

} StackItemD;

void makeEmptyStackD( StackItemD **pStack );
void pushD( StackItemD **pStack, double x );
double popD( StackItemD **pStack ); // parameter in/out
double topD( StackItemD *pStack ); // parameter in
void delD( StackItemD **pStack );
int isEmptyD( StackItemD *pStack );

#endif


