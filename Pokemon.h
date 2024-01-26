//
// Created by ise on 11/16/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

#ifndef ASS2YAEL_POKEMON_H
#define ASS2YAEL_POKEMON_H

typedef struct PokeType{
    char* TypeName;
    int nunOfPokemon;
    int effective_against_me_number;
    int effective_against_others_number;
    struct PokeType** effective_against_me;
    struct PokeType** effective_against_others;
    //Type** efe; incorrect
}Type;

typedef struct BiologyPokemon{
    double height; //meter
    double weight; //kilogram
    int attack;
}bio;

typedef struct Pokemon{
    char* name;
    char* species;
    Type* myType;
    bio* myBio;
}pok;

pok* init_pokemon(char* name, char* species, Type* type, double height , double weight ,int attack); //add Pokemon with all the information he needs,returns Pok*
Type* init_type(char* name); //add Type in to the Pokemon, return Type*
bio* init_bio(double height, double weight, int attack);//add bio in to the Pokemon, return bio*
status add_effective_against_me(Type* me_not_effective, Type* effective);//adding a Type to the add_effective_against_me list and connecting it to the the Type that is insert into the function by me_not_affective, returns status(success or fail)
status add_effective_against_others(Type* me_effective, Type* other);// adding a Type to the add_effective_against_me_others list and connecting it to the the Type that is insert into the function by me_affective, returns status(success or fail)
status print_pokemon(pok* p); //prints all the Pokemons by the txt that has given as, returns status(success or fail)
status print_Type(Type* t); //prints all the Types by the txt that has given as, returns status(success or fail)
status delete_type(Type* type); // delete the Type that I have given in the function, returns status(success or fail)
status delete_poke(pok* p); // delete the Pokemon that I have given in the function
status delete_bio(bio* bio);

//work 2
int getAttack(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond);
char* getCategoryPokemon(element elem);
element copyPok(element pokemon);
int comparePok(pok* pokemon_first, pok* pokemon_second);

#endif //ASS2YAEL_POKEMON_H
