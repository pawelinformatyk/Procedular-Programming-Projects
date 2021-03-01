#pragma once

typedef struct
{
	int key;
} PQInfo; 

#define QPRIORINFO PQInfo

QPRIORINFO* copyElem( QPRIORINFO* pInfo );
int compare( QPRIORINFO* p1, QPRIORINFO* p2 );
