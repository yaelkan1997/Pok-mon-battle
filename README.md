# Pokémon Battle System

## Introduction

This program is a simple Pokémon battle system implemented in C. It allows users to create and manage Pokémon battles, including adding Pokémon to a training camp, removing the strongest Pokémon of a specific type, and engaging in battles.

## Features

- **Dynamic Memory Management**: The program dynamically allocates and manages memory for Pokémon and their types.
  
- **Type Effectiveness**: Pokémon types are considered, and effectiveness against other types is taken into account during battles.

- **File Input**: The program reads data from an input file to initialize Pokémon types and individual Pokémon for battles.

- **Command Line Interface (CLI)**: The program provides a user-friendly CLI for interacting with the Pokémon battle system.

## How to Use

1. **Compilation**: Compile the program using a C compiler (e.g., gcc).

    ```bash
    gcc -o pokemon_battle_system main.c BattleByCategory.c LinkedList.c MaxHeap.c Pokemon.c -Wall
    ```

2. **Execution**: Run the compiled program, providing the required command-line arguments.

    ```bash
    ./pokemon_battle_system [BATTLE_CAPACITY] [TYPE_CAPACITY] [INPUT_FILE]
    ```

    - `BATTLE_CAPACITY`: Maximum number of Pokémon allowed in the battle.
    - `TYPE_CAPACITY`: Maximum number of Pokémon types.
    - `INPUT_FILE`: Path to the input file containing Pokémon and type data.

3. **Interacting with the Program**: Follow the on-screen instructions to perform various actions, such as displaying Pokémon, adding Pokémon to the training camp, removing the strongest Pokémon, and engaging in battles.

4. **Exiting**: Choose option `6` to exit the program. All memory will be freed, and the program will close safely.

## Input File Format

The input file should have the following format:
<Initial Configuration>
<Type_1, Type_2, ..., Type_n>
<Type_1 Against_Type_1:effective-against-me,effective-against-others, ..., Type_1 Against_Type_n:effective-against-me,effective-against-others>
<Type_2 Against_Type_1:effective-against-me,effective-against-others, ..., Type_2 Against_Type_n:effective-against-me,effective-against-others>
...
<Pokémon Data>
<Pokemon_1_Name, Pokemon_1_Species, Pokemon_1_Type, Pokemon_1_Height, Pokemon_1_Weight, Pokemon_1_Attack>
<Pokemon_2_Name, Pokemon_2_Species, Pokemon_2_Type, Pokemon_2_Height, Pokemon_2_Weight, Pokemon_2_Attack>
...
