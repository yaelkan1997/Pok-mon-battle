//
// Created by ise on 12/14/21.
//
#include <malloc.h>
#include <string.h>
#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"

typedef struct battle_s{
    char* categories;
    int capacity;
    int numberOfCategories;
    list heaps;
    equalFunction eql;
    copyFunction copy;
    freeFunction free;
    getCategoryFunction getCategory;
    getAttackFunction getAttack;
    printFunction print;
    char** type_array;
}battle_s;


Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,
                              freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement){
    Battle new_battle = (Battle) malloc(sizeof(struct battle_s));
    if(new_battle == NULL){
        return NULL;
    }
    new_battle->heaps  = createLinkedList((printFunction) printHeap, (freeFunction) destroyHeap, (equalFunction) compareNameToHeap);
    new_battle->capacity = capacity;
    new_battle->numberOfCategories = numberOfCategories;
    new_battle->eql = equalElement;
    new_battle->copy = copyElement;
    new_battle->free = freeElement;
    new_battle->getCategory = getCategory;
    new_battle->getAttack = getAttack;
    new_battle->print = printElement;
    Max_Heap heap;
    new_battle->type_array=(char**)malloc(sizeof(char*)*numberOfCategories);
    char cat[strlen(categories)];
    strcpy(cat, categories);
    char* name;
    name = strtok (cat,",");
    int i=0;
    while(name != NULL){
        heap = CreateHeap(capacity,name,(freeFunction) freeElement,(printFunction) printElement,(copyFunction) copyElement,(compareFunc) equalElement);
        appendNode(new_battle->heaps, heap);
        heap = NULL;
        new_battle->type_array[i]=(char*)malloc(strlen(name)+1);
        strcpy(new_battle->type_array[i],name);
        i++;
        name = strtok (NULL,",");
    }

    return new_battle;
}
status destroyBattleByCategory(Battle b){
    if(b == NULL){
        return fail;
    }
    destroyList(b->heaps);

    for(int i=0; i<b->numberOfCategories;i++){
        free(b->type_array[i]);
    }
    free(b->type_array);
    free(b);
    return success;
}


status insertObject(Battle b, element elem){
    if(b==NULL || elem == NULL){
        return fail;
    }
    status st;
    element category = b->getCategory(elem);
    Max_Heap heap = searchByKeyInList(b->heaps, category);
    if(heap==NULL){
        destroyHeap(heap);
        return fail;
    }
    st=insertToHeap(elem,heap);
    return st;
}


void displayObjectsByCategories(Battle b){
    displayList(b->heaps);
}

element removeMaxByCategory(Battle b,char* category){
    Max_Heap heap = searchByKeyInList(b->heaps, category);
    if(heap != NULL){
        element elem = PopMaxHeap(heap);
        destroyNode(heap);
        return elem;

    }
    return NULL;
}

int getNumberOfObjectsInCategory(Battle b,char* category){
    element heap = searchByKeyInList(b->heaps, category);
    if(heap != NULL){
        return getHeapCurrentSize(heap);
    }
    return 0;
}

element fight(Battle b,element elem){
    if(b==NULL || elem == NULL){
        return NULL;
    }

    int attack1;
    int attack2;
    element elem_against = NULL;
    element elem_against_comp = NULL;
    Max_Heap heap = NULL;
    Max_Heap heap2 = NULL;
    heap= searchByKeyInList(b->heaps,b->type_array[0]);
    elem_against=TopMaxHeap(heap);
    int i =0;
    while(i < (b->numberOfCategories-1)){

        if(b->type_array[i+1]== NULL){
            break;
        }
        heap2 = searchByKeyInList(b->heaps,b->type_array[i+1]);
        if(getHeapCurrentSize(heap2) == 0){
            i++;
        }
        else{
            elem_against_comp = TopMaxHeap(heap2);
            b->getAttack(elem_against,elem_against_comp,&attack1,&attack2);
            if(attack1 - attack2<0){//elem_against < elem_against_comp
                elem_against = elem_against_comp;
            }
            i++;
        }

    }
    int Attack = b->getAttack(elem,elem_against,&attack1,&attack2);
    printf("The final battle between:\n");
    b->print(elem);
    printf("In this battle his attack is :%d\n\n",attack1);
    printf("against ");
    b->print(elem_against);
    printf("In this battle his attack is :%d\n\n",attack2);
    if(Attack>0){
        printf("THE WINNER IS:\n");
        b->print(elem);
        return elem;
    }
    if(Attack<0){
        printf("THE WINNER IS:\n");
        b->print(elem_against);
        return elem_against;
    }
    else{
        printf("IT IS A DRAW.\n");
        return NULL;
    }




}
