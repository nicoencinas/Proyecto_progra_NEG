/**
 * @brief It implements the command interpreter
 *
 * @file character.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "types.h"

#define GDESC_SIZE 6
#define MESSAGE_SIZE 256

struct _Character {
    Id id;
    char name[WORD_SIZE + 1];
    char gdesc[GDESC_SIZE + 1];   
    Character* characters[MAX_CHARACTERS]; 
    Id location;                 
    int health;
    Bool friendly;
    char message[MESSAGE_SIZE];
};

Character* character_create(Id id) {
    Character *new_character = NULL;

    if (id == NO_ID) return NULL;

    new_character = (Character *) malloc(sizeof(Character));
    if (new_character == NULL) return NULL;

    new_character->id = id;
    new_character->name[0] = '\0';
    new_character->gdesc[0] = '\0';
    new_character->location = NO_ID;
    new_character->health = 0;
    new_character->friendly = FALSE;
    new_character->message[0] = '\0';

    return new_character;
}

Status character_destroy(Character* character) {
    if (!character) return ERROR;
    free(character);
    return OK;
}

Id character_get_id(Character* character) {
    if (!character) return NO_ID;
    return character->id;
}

const char* character_get_name(Character* character) {
    if (!character) return NULL;
    return character->name;
}

const char* character_get_gdesc(Character* character) {
    if (!character) return NULL;
    return character->gdesc;
}

Id character_get_location(Character* character) {
    if (!character) return NO_ID;
    return character->location;
}

int character_get_health(Character* character) {
    if (!character) return -1;
    return character->health;
}

Bool character_get_friendly(Character* character) {
    if (!character) return FALSE;
    return character->friendly;
}

const char* character_get_message(Character* character) {
    if (!character) return NULL;
    return character->message;
}

Status character_set_name(Character* character, char* name) {
    if (!character || !name) return ERROR;
    if (!strcpy(character->name, name)) return ERROR;
    return OK;
}

Status character_set_gdesc(Character* character, char* gdesc) {
    if (!character || !gdesc) return ERROR;
    if (!strcpy(character->gdesc, gdesc)) return ERROR;
    return OK;
}

Status character_set_location(Character* character, Id id) {
    if (!character || id == NO_ID) return ERROR;
    character->location = id;
    return OK;
}

Status character_set_health(Character* character, int health) {
    if (!character) return ERROR;
    if (health <= 0) return ERROR;
    character->health = health;
    return OK;
}

Status character_set_friendly(Character* character, Bool friendly) {
    if (!character) return ERROR;
    character->friendly = friendly;
    return OK;
}

Status character_set_message(Character* character, char* message) {
    if (!character || !message) return ERROR;
    if (!strcpy(character->message, message)) return ERROR;
    return OK;
}

Status character_print(Character* character) {
    if (!character) return ERROR;

    fprintf(stdout,
        "--> Character (Id: %ld; Name: %s; Location: %ld; Health: %d; Friendly: %d)\n",
        character->id,
        character->name,
        character->location,
        character->health,
        character->friendly
    );

    return OK;
}