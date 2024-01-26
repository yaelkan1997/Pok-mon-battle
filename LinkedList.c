//
// Created by ise on 12/9/21.
//

#include "LinkedList.h"


struct LinkedList{
    struct MyNode *head ;
    struct MyNode *end;
    printFunction prtElem;
    freeFunction fr;
    compareFunc cmp;
};

struct MyNode{
    element elem;
    struct MyNode* next;
    struct MyNode* prev;
};



list createLinkedList(printFunction prt, freeFunction f, compareFunc cmp){
    list new = (list) malloc(sizeof (struct LinkedList));
    if(new == NULL){
        return NULL;
    }
    new->head = NULL;
    new->end = NULL;
    new->prtElem = prt;
    new->fr = f;
    new->cmp = cmp;
    return new;
}


status destroyList(list lst){
	node nodeHead=NULL;
	node tmp = NULL;
	nodeHead=lst->head;
	while(nodeHead!=NULL){
		tmp=nodeHead;
		nodeHead=nodeHead->next;
		lst->fr(tmp->elem);
		free(tmp);
	}
	free(lst);
	return success;
}


void appendNode(list lst, element elem){
    node newNode = (node) malloc(sizeof(struct MyNode));
    newNode->elem = elem;
    if(lst->head == NULL){
        lst->head = newNode;
        lst->end = newNode;
        newNode->prev = NULL;
    }
    else{
        lst->end->next = newNode;
        newNode->prev= lst->end;
        lst->end = newNode;


    }
    newNode->next = NULL;
}


status deleteNode(list lst, element elem){
    if(lst==NULL || elem == NULL || lst->head == NULL){
        return fail;
    }
    node current = lst->head;
    node tmp = NULL;
    if(lst->cmp(elem,current->elem)==0){
        lst->head=current->next;
        lst->head->prev=NULL;
        lst->fr(current->elem);
        free(current);
        return success;
    }
    while (current->next!= NULL){
        if(lst->cmp(elem,current->next->elem)==0){
            if(current->next==lst->end){
                lst->fr(current->next->elem);
                free(current->next);
                lst->end = current;
                return success;
            }
            tmp = current->next;
            current->next=tmp->next;
            tmp->next->prev= current;
            lst->fr(tmp->elem);
            free(tmp);
            return success;
        }
        else{
            current=current->next;
        }
    }
    return fail;
}


void displayList(list lst){
    if (lst->head ==NULL){
        return;
    }
    node tmp = lst->head;
    while(tmp != NULL){
        lst->prtElem(tmp->elem);
        tmp = tmp->next;
    }
}


element searchByKeyInList(list lst, element elem){
    node temp_node = lst->head;
    while (temp_node != NULL){
        if((lst->cmp(temp_node->elem,(char*) elem))==0){
            return temp_node->elem;
        }
        temp_node = temp_node->next;
    }
    return NULL;

}

