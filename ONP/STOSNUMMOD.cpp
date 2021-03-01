#include "STOSNUM.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void makeEmptyStackD(StackItemD** pStack)
{
	while (!isEmptyD(*pStack))
		delD(pStack);
	*pStack = NULL;
}
void pushD(StackItemD** pStack, double x)
{
	StackItemD* p = (StackItemD*)malloc(sizeof(StackItemD)); 
	if (p)   													
	{
		p->fKey = x;
		p->pNext = *pStack; 
		*pStack = p; 
	}
}
double popD(StackItemD** pStack) 
{
	double x = 0;
	if (!isEmptyD(*pStack))
	{
		x = topD(*pStack);
		delD(pStack); 
	}
	else
		cout << "\n\n *!* Stack underflow!! (dpop) \n\n";
	return x;
}
double topD(StackItemD* pStack)
{
	if (!isEmptyD(pStack))
		return pStack->fKey;
	cout << "\n\n *!* Stack underflow!! (dtop) \n\n";
	return 0;
}
void delD(StackItemD** pStack)
{
	if (!isEmptyD(*pStack))
	{
		StackItemD* p = *pStack; 
		*pStack = p->pNext; 
		free(p); 
	}
	else
		cout << "\n *!* Stack underflow!! ( ddel )\n\n";
}
int isEmptyD(StackItemD* pStack)
{
	return !pStack;
}