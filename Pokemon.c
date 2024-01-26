
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"



pok* init_pokemon(char* name, char* species, Type* type, double height , double weight ,int attack){
    if(name==NULL||species==NULL||type==NULL)
        return NULL;
    pok* newPok = (pok*) malloc(sizeof(struct Pokemon));
    if (newPok==NULL){
        return NULL;
    }
    newPok->name = (char *)malloc(sizeof(char)*(strlen(name)+1));
    if(newPok->name==NULL)
    {
        free(newPok);
        newPok=NULL;
        return NULL;
    }
    strcpy(newPok->name, name);
    newPok->species = (char *)malloc(sizeof(char)*(strlen(species)+1));
    if(newPok->species==NULL)
    {
        free(newPok->name);
        newPok->name=NULL;
        free(newPok);
        newPok=NULL;
        return NULL;
    }
    strcpy(newPok->species, species);
    newPok->myType = type;
    newPok->myBio = init_bio(height,weight,attack);
    return newPok;
}

status delete_poke(pok* p){
    if (p==NULL)
        return fail;
    free(p->myBio);
    p->myBio=NULL;
    free(p->name);
    p->name=NULL;
    free(p->species);
    p->species=NULL;
    free(p);
    p=NULL;
    return success;
}

Type* init_type(char* name){
    if (name==NULL)
        return NULL;
    Type* newType = (Type*) malloc(sizeof(Type));
    if(newType==NULL){
        printf("Memory Problem");
        return NULL;
    }
    newType->TypeName = (char *)malloc(sizeof(char)*(strlen(name)+1));
    if(newType->TypeName==NULL)
    {
        free(newType);
        newType=NULL;
        printf("Memory Problem");
        return NULL;
    }
    strcpy(newType->TypeName, name);
    newType->nunOfPokemon = 0;
    newType->effective_against_me_number =0; //size of effective_against_me
    newType->effective_against_others_number = 0; //size of effective_against_others
    newType->effective_against_me = NULL;
    newType->effective_against_others = NULL;
    return newType;
}

status delete_bio(bio* bio){
    if(bio == NULL){
        return fail;
    }
    free(bio);
    return success;
}
status delete_type(Type* type){
    if (type==NULL)
        return fail;
    free(type->TypeName);
    type->TypeName=NULL;
    free(type->effective_against_me);
    type->effective_against_me=NULL;
    free(type->effective_against_others);
    type->effective_against_others=NULL;
    free(type);
    type=NULL;
    return success;
}

bio* init_bio(double height, double weight, int attack){
    bio* newBio = (bio *) malloc(sizeof(struct BiologyPokemon));
    if(newBio==NULL){
        return NULL;
    }
    newBio->height = height;
    newBio->weight = weight;
    newBio->attack = attack;
    return newBio;
}

status add_effective_against_me(Type* me, Type* effective){
    if(me==NULL||effective==NULL) {
        return fail;
    }
    if(me->effective_against_me == NULL){
        me->effective_against_me = (Type**)malloc(sizeof (Type*));
        if(me->effective_against_me == NULL){
            printf("Memory Problem");
            return fail;
        }
        me->effective_against_me[0] = effective;
    }
    else{
        me->effective_against_me = (Type**) realloc (me->effective_against_me, (me->effective_against_me_number+1)*sizeof(Type*));
        if(me->effective_against_me == NULL){
            printf("Memory Problem");
            return fail;
        }
        me->effective_against_me[me->effective_against_me_number] = effective;
    }
    me->effective_against_me_number ++;
    return success;

}
status add_effective_against_others(Type* me_effective, Type* other){
    if(me_effective==NULL||other==NULL){
        return fail;
    }
    if(me_effective->effective_against_others == NULL){
        me_effective->effective_against_others = (Type**)malloc(sizeof (Type*));
        if(me_effective->effective_against_others == NULL){
            printf("Memory Problem");
            return fail;
        }
        me_effective->effective_against_others[0]=other;
    }
    else{
        me_effective->effective_against_others = (Type**) realloc(me_effective->effective_against_others,(me_effective->effective_against_others_number+1)*sizeof (Type*));
        if(me_effective->effective_against_others == NULL){
            printf("Memory Problem");
            return fail;
        }
        me_effective->effective_against_others[me_effective->effective_against_others_number] = other;
    }
    me_effective->effective_against_others_number ++;
    return success;
}

status print_pokemon(pok* p){
    if(p==NULL){
        return fail;
    }
    printf("%s :\n%s, %s Type.\nHeight: %.2f m    Weight: %.2f kg    Attack: %d\n\n",p->name,p->species,p->myType->TypeName,p->myBio->height,p->myBio->weight,p->myBio->attack);
    return success;
}
status print_Type(Type* t){
    if(t==NULL){
        return fail;
    }
    printf("Type %s -- %d pokemons\n", t->TypeName, t->nunOfPokemon);
    if(t->effective_against_me_number>0)
    {
        printf("\tThese types are super-effective against %s:", t->TypeName);
        for(int i = 0; i< t->effective_against_me_number-1; i++){
            printf("%s ,",t->effective_against_me[i]->TypeName);
        }
        printf("%s",t->effective_against_me[t->effective_against_me_number-1]->TypeName);
        printf("\n");
    }
    if(t->effective_against_others_number>0)
    {
        printf("\t%s moves are super-effective against:",t->TypeName);
        for(int i = 0; i< t->effective_against_others_number-1; i++){
            printf("%s ,",t->effective_against_others[i]->TypeName);
        }
        printf("%s",t->effective_against_others[t->effective_against_others_number-1]->TypeName);
        printf("\n");
    }
    return success;


}

int getAttack(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond){
    pok* first = (pok*) firstElem;
    pok* second = (pok*) secondElem;
    int num1=0;
    int num2=0;
    *attackFirst = first->myBio->attack -num1;
    *attackSecond = second->myBio->attack -num2;
    if(strcmp(first->myType->TypeName,second->myType->TypeName)==0){
        return *attackFirst - *attackSecond;
    }
    else{
        for(int i = 0;i<first->myType->effective_against_me_number;i++){
            if(strcmp(first->myType->effective_against_me[i]->TypeName,second->myType->TypeName)==0){
                num1 = 10;
                break;
            }
        }
        for(int i = 0;i<first->myType->effective_against_others_number;i++){
            if(strcmp(first->myType->effective_against_others[i]->TypeName,second->myType->TypeName)==0){
                num2 = 10;
                break;
            }
        }
        for(int i = 0;i<second->myType->effective_against_me_number;i++){
            if(strcmp(second->myType->effective_against_me[i]->TypeName,first->myType->TypeName)==0){
                num2 = 10;
                break;
            }
        }
        for(int i = 0;i<second->myType->effective_against_others_number;i++){
            if(strcmp(second->myType->effective_against_others[i]->TypeName,first->myType->TypeName)==0){
                num1 = 10;
                break;
            }
        }

    }
    *attackFirst = first->myBio->attack -num1;
    *attackSecond = second->myBio->attack -num2;
    return *attackFirst - *attackSecond;
}

char* getCategoryPokemon(element elem){
    pok* pokemon = (pok*) elem;
    return pokemon->myType->TypeName;
}



element copyPok(element pokemon){
    pok * pok_copy = (pok*) pokemon;
    pok * new_pokemon;
    new_pokemon = init_pokemon(pok_copy->name,pok_copy->species,pok_copy->myType,pok_copy->myBio->height,pok_copy->myBio->weight,pok_copy->myBio->attack);
    return new_pokemon;
}
int comparePok(pok* pokemon_first, pok* pokemon_second){
    if(pokemon_first->myBio->attack > pokemon_second->myBio->attack){
        return 1;
    }
    else if(pokemon_first->myBio->attack < pokemon_second->myBio->attack){
        return -1;
    }
    return 0;
}