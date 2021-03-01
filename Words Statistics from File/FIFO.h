#pragma once

typedef struct tagFQitem
{
	int key;
	tagFQitem* pNext;
}fqItem;

typedef struct
{
	fqItem* pHead;
	fqItem* pTail;
}fqueue;

fqueue* fqCreate();
int fqIsEmpty( fqueue* q );
void fqEnqueue( fqueue* q, int x );
int fqDequeue( fqueue* q );
void fqClear( fqueue* q );
void fqRemove( fqueue** q );
void fqDisplay( fqueue* q );