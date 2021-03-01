#pragma once

#include "FIFO.h"
#include <stdio.h>

typedef struct tagTreeElem
{
	int count;
	char* pWord;
	fqueue* lineList;
	tagTreeElem* pLeft;		
	tagTreeElem* pRight;
}treeElem;

treeElem* newTree( char* word, int nLine );
treeElem* findAndInsert( char* x, treeElem* p, int nLine );
treeElem* freeTree( treeElem* pRoot );
int compare( char* word1, char* word2 );
void addLine( fqueue** LineList, int nLine );

void preOrder( treeElem* p, FILE* fout );
void inOrder( treeElem* p, FILE* fout );
void postOrder( treeElem* p, FILE* fout );
void printElem( treeElem* p, FILE* fout );

