#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "set.h"
#include "types.h"
#include "inventory.h"
#define GDESC_SIZE 6

struct _Player
{
    Id id;
    char name[WORD_SIZE + 1];
    Id location;
    Inventory *inventory;
    char gdesc[GDESC_SIZE + 1];
    int health;
};

Player *player_create(Id id)
{
    Player *new_player = NULL;

    if (id == NO_ID)
        return NULL;

    new_player = (Player *)malloc(sizeof(Player));
    if (new_player == NULL)
        return NULL;

    new_player->id = id;
    new_player->name[0] = '\0';
    new_player->location = NO_ID;
    new_player->health = 10;
    new_player->inventory=inventory_create();
    if (new_player->inventory == NULL)
    {
        free(new_player);
        return NULL;
    }
    return new_player;
}

Status player_destroy(Player *player)
{
    if (!player)
        return ERROR;
    inventory_destroy(player->inventory);
    free(player);

    return OK;
}

Id player_get_id(Player *player)
{
    if (!player)
        return NO_ID;
    return player->id;
}

const char *player_get_name(Player *player)
{
    if (!player)
        return NULL;
    return player->name;
}

Id player_get_location(Player *player)
{
    if (!player)
        return NO_ID;
    return player->location;
}

Set *player_get_object(Player *player)
{
    if (!player)
        return NULL;
    return inventory_get_inventory(player->inventory);
}

int player_get_health(Player *player)
{
    if (!player)
        return -1;
    return player->health;
}
const char *player_get_gdesc(Player *player)
{
    if (!player)
        return NULL;
    return player->gdesc;
}
Inventory *player_get_inventory(Player *player)
{
    if (!player)
        return NULL;
    return player->inventory;
}

/* --- SETTERS --- */
Status player_set_name(Player *player, char *name)
{
    if (!player || !name)
        return ERROR;
    if (!strcpy(player->name, name))
        return ERROR;
    return OK;
}

Status player_set_location(Player *player, Id id)
{
    if (!player || id == NO_ID)
        return ERROR;
    player->location = id;
    return OK;
}

Status player_set_object(Player *player, Id id)
{
    if (!player)
        return ERROR;
    return set_add(inventory_get_inventory(player->inventory), id);
    return OK;
}
Status player_set_health(Player *player, int health)
{
    if (!player)
        return ERROR;
    player->health = health;
    return OK;
}
Status player_set_gdesc(Player *player, char *gdesc)
{
    if (!player || !gdesc)
        return ERROR;
    if (!strcpy(player->gdesc, gdesc))
        return ERROR;
    return OK;
}

Status player_print(Player *player)
{
    if (!player)
        return ERROR;

    fprintf(stdout, "--> Player (Id: %ld; Name: %s; Location: %ld)\n",
            player->id, player->name, player->location);
    set_print(inventory_get_inventory(player->inventory));
    if (player->inventory)
    {
        inventory_print(player->inventory);
    }
    return OK;
}
Status player_add_object(Player *player, Id id)
{
    if (!player || id == NO_ID)
        return ERROR;
    return inventory_add(player->inventory, id);
}

Status player_remove_object(Player *player, Id id)
{
    if (!player || id == NO_ID)
        return ERROR;
    return inventory_del(player->inventory, id);
}

Bool player_has_object(Player *player, Id id)
{
    if (!player || id == NO_ID)
        return FALSE;
    return inventory_find(player->inventory, id);
}