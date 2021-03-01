#pragma once

#include "Tree.h"

#define WORD_LENGTH 128

treeElem* readData( const char* file_name );
int isChar( char c );
int notDigit( char c );