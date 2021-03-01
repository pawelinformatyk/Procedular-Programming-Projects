#pragma once
#include "Global.h"

typedef struct
{
	QPRIORINFO* pInfo;
	int nPrior;
} PQItem;

typedef struct
{
	PQItem** queue;
	int max_size; 
	int curr_size; 
} PQueue;

PQueue* PQInit( int x);
int PQisEmpty( PQueue* pq);
void PQEnqueue( PQueue* pq, QPRIORINFO* pInfo, int nPrior );
QPRIORINFO* PQDequeue( PQueue* pq);
void PQClearQueue( PQueue* pq);
void PQRealease( PQueue** pq); 
void PQPrint( PQueue* pq, int l, int r );
void DecreaseKey( PQueue* pq, QPRIORINFO* pInfo, int nPrior );
void IncreaseKey( PQueue* pq, QPRIORINFO* pInfo, int nPrior );
   void UpdateDown( PQueue* pq, int l, int p );
  void UpdateUp( PQueue* pq, int l, int p );

void drawTree( PQueue* pq );

