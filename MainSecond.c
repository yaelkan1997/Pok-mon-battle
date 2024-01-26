#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "Pokemon.h"

Type* Find_Type(Type** all_the_type , char* name_of_type, int numOfTypes){
    for(int i=0; i<numOfTypes; i++){
        if(strcmp(all_the_type[i]->TypeName, name_of_type)==0){
            return all_the_type[i];
        }
    }
    return NULL;
}
status Delete_all_the_Types(Type ** Types, int num){
    if(Types == NULL){
        return fail;
    }
    for(int i = 0; i< num;i++){
        delete_type(Types[i]);
        Types[i]=NULL;
    }
    if(Types!=NULL){
        free(Types);
        Types = NULL;
    }
    return success;

}


int main(int args, char* argv[]){
    int capcityInType=atoi(argv[2]);
    FILE *file;
    char line[300];
    char *type;
    Type  ** All_The_Types =NULL;
    int numOfTypes = 0;
    char *type2;
    char *against_who;
    Type *main_type = NULL;
    Type *type_2 = NULL;

    file = fopen(argv[3], "r");

    fgets(line, 300, file); //row 1
    fgets(line, 300, file); //row 2
    type = strtok(line, "\r\n");

    Battle battle = createBattleByCategory(atoi(argv[1]), atoi(argv[2]), type, (equalFunction) comparePok,
                                           (copyFunction) copyPok, (freeFunction) delete_poke,
                                           (getCategoryFunction) getCategoryPokemon, (getAttackFunction) getAttack,
                                           (printFunction) print_pokemon);
    if(battle == NULL)
    {
        destroyBattleByCategory(battle);
        Delete_all_the_Types(All_The_Types,numOfTypes);
        printf("No memory available.\n");
        exit(1);
    }

    type = strtok(type, ",");
    while (type!= NULL) {
        if (strstr(type, "Pokemons")!=NULL)
            break;
        if (All_The_Types == NULL) {
            All_The_Types = (Type **) malloc(sizeof(Type*));
            if(All_The_Types == NULL){
                exit(0);
            }
            All_The_Types[0] = init_type(type);
            if(All_The_Types[0]== NULL){
                Delete_all_the_Types(All_The_Types,numOfTypes);
                destroyBattleByCategory(battle);
                printf("No memory available.\n");
                exit(0);
            }
            numOfTypes++;
        } else {
            All_The_Types = (Type **) realloc(All_The_Types, (numOfTypes + 1) * (sizeof(Type*)));
            if(All_The_Types == NULL){
                destroyBattleByCategory(battle);
                printf("No memory available.\n");
                exit(0);
            }
            All_The_Types[numOfTypes] = init_type(type);
            if(All_The_Types[numOfTypes]== NULL){
                Delete_all_the_Types(All_The_Types,numOfTypes);
                destroyBattleByCategory(battle);
                printf("No memory available.\n");
                exit(0);
            }
            numOfTypes++;
        }
        type = strtok(NULL, "\r\n");
        type = strtok(type, ",");
    }
    status st=success;
    while(!strstr(line,"Pokemons")) {
        fgets(line, 300, file);
        type = strtok(line, "\t");
        type = strtok(type, " ");
        against_who = strtok(NULL, ":");
        type2 = type;
        main_type = Find_Type(All_The_Types, type2, numOfTypes);
        type = strtok(NULL, "\r\n");
        type = strtok(type, ",");
        while (type != NULL) {

            if (strcmp(against_who, "effective-against-me") == 0) {
                type_2 = Find_Type(All_The_Types, type, numOfTypes);
                st=add_effective_against_me(main_type,type_2);
                if(st == fail){
                    Delete_all_the_Types(All_The_Types,numOfTypes);
                    destroyBattleByCategory(battle);
                    printf("No memory available.\n");
                    exit(0);
                }
            }
            else{
                type_2 = Find_Type(All_The_Types, type, numOfTypes);
                st = add_effective_against_others(main_type,type_2);
                if(st == fail){
                    Delete_all_the_Types(All_The_Types,numOfTypes);
                    destroyBattleByCategory(battle);
                    printf("No memory available.\n");
                    exit(0);
                }
            }
            type = strtok(NULL, "\r\n");
            type = strtok(type, ",");
        }
    }

    char *pokimon;
    char *species;
    char *string_weight;
    char *string_height;
    char *string_attack;
    char *pok_type;
    float weight, height;
    int attack;
    pok* new_pokemon;
    while (fgets(line, 300, file) != NULL){

        pokimon = strtok(line, ",");


        species = strtok(NULL, ",");

        string_height = strtok(NULL, ",");
        height = atof(string_height); //convert string to float

        string_weight = strtok(NULL, ",");
        weight = atof(string_weight); //convert string to float

        string_attack = strtok(NULL, ",");
        attack = atoi(string_attack); //convert string to int


        pok_type = strtok(NULL, ",\r\n");
        int i=0;
        while(strcmp(All_The_Types[i]->TypeName,pok_type)!=0){
            i++;
        }
        new_pokemon= init_pokemon(pokimon, species, All_The_Types[i], height,weight,attack);
        All_The_Types[i]->nunOfPokemon++;
        st = insertObject(battle,new_pokemon);
        if(st == fail){
            destroyBattleByCategory(battle);
            printf("No memory available.\n");
            exit(0);
        }
        delete_poke(new_pokemon);

    }
    fclose(file);


    char chose = '1';
    char TypeName[50];
    char Pokname[50];
    char speciesname[50];
    Type *Type_Name;
    double Height;
    double Weight;
    int Attack;
    while (chose != '6') {
        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons by types\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Insert Pokemon to battles training camp\n");
        printf("4 : Remove strongest Pokemon by type\n");
        printf("5 : Fight\n");
        printf("6 : Exit\n");
        scanf(" %c", &chose);
        switch (chose){
            case '1':
                displayObjectsByCategories(battle);
                break;
            case '2':
                for (int i=0; i<numOfTypes;i++){
                    print_Type(All_The_Types[i]);
                    printf("\n");
                }
                break;
            case '3':
                printf("Please enter Pokemon type name:\n");
                scanf("%s", TypeName);
                Type_Name = Find_Type(All_The_Types, TypeName, numOfTypes);
                if (Type_Name == NULL) {
                    printf("Type name doesn't exist.\n");
                    break;
                }
                int num_max = getNumberOfObjectsInCategory(battle,TypeName);
                if(num_max == capcityInType){
                    printf("Type at full capacity.\n");
                    break;

                }
                printf("Please enter Pokemon name:\n");
                scanf("%s",Pokname);
                printf("Please enter Pokemon species:\n");
                scanf("%s",speciesname);
                printf("Please enter Pokemon height:\n");
                scanf("%lf",&Height);
                printf("Please enter Pokemon weight:\n");
                scanf("%lf",&Weight);
                printf("Please enter Pokemon attack:\n");
                scanf("%d",&Attack);

                pok * new_pok = init_pokemon(Pokname,speciesname,Type_Name,Height,Weight,Attack);
                status st=insertObject(battle, new_pok);
                if(st==success){
                    printf("The Pokemon was successfully added.\n");
                    print_pokemon(new_pok);
                    Type_Name->nunOfPokemon++;
                }
                else{
                    destroyBattleByCategory(battle);
                    printf("No memory available.\n");
                    exit(0);
                }
                delete_poke(new_pok);
                break;
            case '4':
                printf("Please enter type name:\n");
                scanf("%s", TypeName);
                int num_0 = getNumberOfObjectsInCategory(battle,TypeName);
                Type_Name = Find_Type(All_The_Types, TypeName, numOfTypes);
                if(num_0 == 0 && Type_Name != NULL){
                    printf("There is no Pokemon to remove.\n");
                    break;

                }
                if (Type_Name == NULL) {
                    printf("Type name doesn't exist.\n");
                    break;
                }
                new_pok = NULL;
                new_pok= removeMaxByCategory(battle,TypeName);
                printf("The strongest Pokemon was removed:\n");
                print_pokemon(new_pok);
                delete_poke(new_pok);
                Type_Name->nunOfPokemon--;
                break;
            case '5':
                printf("Please enter Pokemon type name:\n");
                scanf("%s", TypeName);
                Type_Name = Find_Type(All_The_Types, TypeName, numOfTypes);
                if (Type_Name == NULL) {
                    printf("Type name doesn't exist.\n");
                    break;
                }
                printf("Please enter Pokemon name:\n");
                scanf("%s",Pokname);
                printf("Please enter Pokemon species:\n");
                scanf("%s",speciesname);
                printf("Please enter Pokemon height:\n");
                scanf("%lf",&Height);
                printf("Please enter Pokemon weight:\n");
                scanf("%lf",&Weight);
                printf("Please enter Pokemon attack:\n");
                scanf("%d",&Attack);
                new_pok= init_pokemon(Pokname,speciesname,Type_Name,Height,Weight,Attack);
                if(new_pok == NULL){
                    destroyBattleByCategory(battle);
                    printf("No memory available.\n");
                    exit(0);
                }
                printf("You choose to fight with:\n");
                print_pokemon(new_pok);
                int count = 0;
                for (int i=0;i<numOfTypes;i++){
                    if(getNumberOfObjectsInCategory(battle,All_The_Types[i]->TypeName)==0){
                        count++;
                    }
                }
                if(count == numOfTypes){
                    printf("There are no Pokemons to fight against you.\n");
                    delete_poke(new_pok);
                    break;
                }
                fight(battle,new_pok);
                delete_poke(new_pok);
                break;

            case '6':
                destroyBattleByCategory(battle);
                Delete_all_the_Types(All_The_Types,numOfTypes);
                printf("All the memory cleaned and the program is safely closed.\n\n");
                break;

            default:
                printf("Please choose a valid number.\n");
        }
    }
    return 0;
}
