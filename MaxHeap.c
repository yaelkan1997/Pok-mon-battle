
#include <string.h>
#include "MaxHeap.h"
struct MaxHeap{
    char * Heap_name;
    int num_of_nodes_max;
    int num_of_nodes_current;
    NodeHeap* heap_array;
    freeFunction fr;
    printFunction prtElem;
    copyFunction copy;
    equalFunction comp;
};
struct Node_Heap{
    element elem;
    int index;
};
void destroyNode(Max_Heap maxHeap){
    free(maxHeap->heap_array[maxHeap->num_of_nodes_current]);
}
void heapify(Max_Heap maxHeap, int i){
    int right_child = 2*i+2;
    int left_child =2*i+1;
    int max_elem;
    NodeHeap node_1;

    if(left_child < maxHeap->num_of_nodes_current && (maxHeap->comp(maxHeap->heap_array[left_child]->elem,maxHeap->heap_array[i]->elem))==1){
        max_elem = left_child;
    }
    else {
        max_elem = i;
    }

    if(right_child < maxHeap->num_of_nodes_current && (maxHeap->comp(maxHeap->heap_array[right_child]->elem,maxHeap->heap_array[max_elem]->elem))==1){
        max_elem = right_child;
    }

    if(max_elem != i){
        node_1 = maxHeap->heap_array[i];
        maxHeap->heap_array[i] = maxHeap->heap_array[max_elem];
        maxHeap->heap_array[max_elem] = node_1;
        heapify(maxHeap,max_elem);
    }
}


Max_Heap CreateHeap(int max_num,char * name,freeFunction fr,printFunction prtElem,copyFunction copy,equalFunction comp){
    Max_Heap new_heap = (Max_Heap) malloc(sizeof(struct MaxHeap));
    if(new_heap == NULL){
        return NULL;
    }
    new_heap->heap_array = (NodeHeap *) malloc(sizeof(NodeHeap) * max_num);
    if(new_heap->heap_array == NULL){
        destroyHeap(new_heap);
        return NULL;
    }
    new_heap->Heap_name = (char *) malloc((strlen(name))+1);
    if(new_heap->Heap_name == NULL){
        destroyHeap(new_heap);
        return NULL;
    }
    strcpy(new_heap->Heap_name,name);
    new_heap->num_of_nodes_max = max_num;
    new_heap->num_of_nodes_current = 0;
    new_heap->fr = fr;
    new_heap->prtElem = prtElem;
    new_heap->copy = copy;
    new_heap->comp = comp;
    return new_heap;
}

void destroyHeap(Max_Heap heap){
    if(heap  == NULL){
        return;
    }
    else{
        for(int i =0;i<heap->num_of_nodes_current;i++) {
            heap->fr(heap->heap_array[i]->elem);
        }
        for(int i =0;i<heap->num_of_nodes_current;i++){
            free(heap->heap_array[i]);
        }
        free(heap->Heap_name);
        free(heap->heap_array);
        free(heap);
    }

}

status insertToHeap(element elem, Max_Heap maxHeap){
    if(maxHeap->num_of_nodes_current >= maxHeap->num_of_nodes_max){
        return fail;
    }
    if(maxHeap->num_of_nodes_current < maxHeap->num_of_nodes_max){
        NodeHeap new_node =(NodeHeap) malloc(sizeof (struct Node_Heap));
        if(new_node==NULL){
            maxHeap->fr(new_node);
            return fail;
        }
        new_node->elem = maxHeap->copy(elem);
        new_node->index = maxHeap->num_of_nodes_current;
        (maxHeap->num_of_nodes_current) ++;
        maxHeap->heap_array[new_node->index] = new_node;
        NodeHeap temp = NULL;
        int i = new_node->index;
        while(i>=0 && (maxHeap->comp(maxHeap->heap_array[i]->elem,maxHeap->heap_array[(int) (i-1)/2]->elem)==1)){
            temp =maxHeap->heap_array[(i-1)/2];
            maxHeap->heap_array[(i-1)/2] = maxHeap->heap_array[i];
            maxHeap->heap_array[i] = temp;
            maxHeap->heap_array[i/2]->index = i/2;
            maxHeap->heap_array[i]->index = i;
            i=i/2;
        }
    }
    return success;
}
void printHeap(Max_Heap maxHeap){
    if(maxHeap->num_of_nodes_current == 0){
        printf("%s:\nNo elements.\n\n",maxHeap->Heap_name);
    }
    else{
        Max_Heap temp_max_heap = CreateHeap(maxHeap->num_of_nodes_max,maxHeap->Heap_name,maxHeap->fr,maxHeap->prtElem,maxHeap->copy,maxHeap->comp);
        printf("%s:\n",temp_max_heap->Heap_name);
        for(int i = 0;i<maxHeap->num_of_nodes_current;i++){
            insertToHeap(maxHeap->heap_array[i]->elem,temp_max_heap);
        }
        for(int i = 0;i<maxHeap->num_of_nodes_current;i++){
            printf("%d. ",i+1);
            element elem_temp = PopMaxHeap(temp_max_heap);
            temp_max_heap->prtElem(elem_temp);
            temp_max_heap->fr(elem_temp);
            free(temp_max_heap->heap_array[temp_max_heap->num_of_nodes_current]);
        }

        free(temp_max_heap->Heap_name);
        free(temp_max_heap->heap_array);
        free(temp_max_heap);

    }
}
element PopMaxHeap(Max_Heap maxHeap) {
    if (maxHeap == NULL || maxHeap->num_of_nodes_current == 0) {
        return NULL;
    }
    element pop_element = maxHeap->copy(maxHeap->heap_array[0]->elem);
    maxHeap->fr(maxHeap->heap_array[0]->elem);
    if(maxHeap->num_of_nodes_current ==1 ){
        maxHeap->num_of_nodes_current--;
        return pop_element;
    }
    maxHeap->heap_array[0]->elem = maxHeap->copy(maxHeap->heap_array[maxHeap->num_of_nodes_current - 1]->elem);
    maxHeap->heap_array[0]->index = 0;
    maxHeap->fr(maxHeap->heap_array[maxHeap->num_of_nodes_current - 1]->elem);
    maxHeap->num_of_nodes_current--;
    if(maxHeap->num_of_nodes_current>1){
        heapify(maxHeap,0);
    }
    return pop_element;
}
element TopMaxHeap(Max_Heap maxHeap){
    if(maxHeap == NULL){
        return NULL;
    }
    return maxHeap->heap_array[0]->elem;
}

char * getHeapId(Max_Heap maxHeap){
    return maxHeap->Heap_name;
}
int getHeapCurrentSize(Max_Heap maxHeap){
    if(maxHeap == NULL){
        return 0;
    }
    return maxHeap->num_of_nodes_current;
}
int compareNameToHeap(Max_Heap heap,char* name){
    if(strcmp(heap->Heap_name,name)==0){
        return 0;
    }
    return 1;
}
