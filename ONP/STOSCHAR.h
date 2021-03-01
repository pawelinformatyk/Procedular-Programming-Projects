#pragma once
#ifndef CSTACK_H
#define CSTACK_H

typedef struct tagStackItem {

	char fKey;
	tagStackItem* pNext;

} StackItem;

void makeEmptyStack(StackItem** pStack);
void push(StackItem** pStack, char x);
char pop(StackItem** pStack); // parametr we/wy
char top(StackItem* pStack); // parametr we
void del(StackItem** pStack);
int isEmpty(StackItem* pStack);

#endif


