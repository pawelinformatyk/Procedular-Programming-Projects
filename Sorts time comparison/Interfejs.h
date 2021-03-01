#ifndef _SORT_H_
#define _SORT_H_

int* createT(int size);
void freeTab(int** pTab);
void init(int* pTab, int size, int Val); 
void randominit(int* pTab, int size);
void copyTab(int* pTabTo, int* pTabFrom, int size);
void printTab(int* pTab, int size);

void SelectionSort(int* pTab, int size);
void Insertion(int* pTab, int size);
void HalfInsertion(int* pTab, int size); 
void BBlSort(int* pTab, int size);
void QuickSort(int* pTab, int L, int R);
void MiwxedBBlSort(int* pTab, int size); 
void MergeSort1(int* pTab,int* pTabT, int l, int r);
void MergeSort2( int* pTab, int l, int r,int size );
void HeapSort(int* pTab, int size);

int isSorted( int* pTab, int size );
#endif 