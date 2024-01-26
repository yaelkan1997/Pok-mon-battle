//
// Created by ise on 11/28/21.
//

#ifndef ASSIGNMENT2_1_DEFS_H
#define ASSIGNMENT2_1_DEFS_H
typedef enum e_status{fail, success} status;
typedef enum e_bool{false,true} bool;
typedef void* element;

typedef int (*compareFunc)(element, element);
typedef element (*copyFunction)(element);
typedef void (*freeFunction)(element);
typedef status (*printFunction)(element);
typedef int(*equalFunction) (element, element);//1 first bigger, 0 - same, -1 second bigger
typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond); // return the first attack - second attack . also produce the attack of each element, The function transmits the information through the pointers received in the function.





#endif //ASSIGNMENT2_1_DEFS_H
