//
// Created by ise on 12/11/21.
//

#ifndef POKEMON2_MAXHEAP_H
#define POKEMON2_MAXHEAP_H
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct MaxHeap* Max_Heap;
typedef struct Node_Heap* NodeHeap;

Max_Heap CreateHeap(int max_num,char * name,freeFunction fr,printFunction prtElem,copyFunction copy,compareFunc comp);
void destroyHeap(Max_Heap heap);
status insertToHeap(element elem,Max_Heap maxHeap);
void printHeap(Max_Heap maxHeap);
element PopMaxHeap(Max_Heap maxHeap);
element TopMaxHeap(Max_Heap maxHeap);
char * getHeapId(Max_Heap maxHeap);
int getHeapCurrentSize(Max_Heap maxHeap);
int compareNameToHeap(Max_Heap heap,char* name);
void destroyNode(Max_Heap maxHeap);// removes the last node
#endif //POKEMON2_MAXHEAP_H
