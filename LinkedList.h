//
// Created by ise on 12/9/21.
//

#ifndef POKEMON2_LINKEDLIST_H
#define POKEMON2_LINKEDLIST_H
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct LinkedList* list;
typedef struct MyNode* node;

list createLinkedList(printFunction prt, freeFunction f, compareFunc cmp);
status destroyList(list lst);
void appendNode(list lst, element elem);
status deleteNode(list lst, element elem);
void displayList(list lst);
element searchByKeyInList(list lst, element elem);



#endif //POKEMON2_LINKEDLIST_H
