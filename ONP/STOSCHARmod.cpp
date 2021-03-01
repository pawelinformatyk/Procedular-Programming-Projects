#include "STOSCHAR.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void makeEmptyStack(StackItem** pStack)
{
	while (!isEmpty(*pStack))
		del(pStack);
	*pStack = NULL;
}
void push(StackItem** pStack, char x)
{
	StackItem* p = (StackItem*)malloc(sizeof(StackItem)); 
	if (p)   													
	{
		p->fKey = x;
		p->pNext = *pStack; 
		*pStack = p; 
	}
}
char pop(StackItem** pStack)
{
	char x = 0;
	if (!isEmpty(*pStack))
	{
		x = top(*pStack); 
		del(pStack); 
	}
	else
		cout << "\n\n *!* Stack underflow!! (dpop) \n\n";
	return x;
}
char top(StackItem* pStack)
{
	if (!isEmpty(pStack))
		return pStack->fKey;
	cout << "\n\n *!* Stack underflow!! (dtop) \n\n";
	return 0;
}
void del(StackItem** pStack)
{
	if (!isEmpty(*pStack))
	{
		StackItem* p = *pStack; 
		*pStack = p->pNext; 
		free(p); 
	}
	else
		cout << "\n *!* Stack underflow!! ( ddel )\n\n";
}
int isEmpty(StackItem* pStack)
{
	return !pStack;
}