/*#define _CRT_SECURE_NO_WARNINGS*/
#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H


#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef struct {
    char name[50];
    unsigned int health;
    unsigned int strength;
    unsigned int defence;
} minion_t;

typedef struct {
    unsigned int fire;
    unsigned int cold;
    unsigned int lightning;
} elemental_resistance_t;

typedef struct {
    char name[50];
    unsigned int level;
    unsigned int health;
    unsigned int mana;
    unsigned int strength;
    unsigned int dexterity;
    unsigned int intelligence;
    unsigned int armour;
    unsigned int evasion;
    unsigned int leadership;
    unsigned int minion_count;
    elemental_resistance_t elemental_resistance;
    minion_t minions[3];
} character_v3_t;

int get_character(const char* filename, character_v3_t* out_character);

void itoa_ft(int num, char* str, int base, int buf_size);

int atoi_ft(char* str);

int string_length_before_carriage_return(const char* str);

int count_token(const char* str, const char delim);


#endif /* CHARACTER_DESERIALIZER_H */
