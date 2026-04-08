#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

struct _InterfaceData
{
  Command *last_cmd;
  char s[MESSAGE_SIZE];
};

struct _Game
{
  Player *players[MAX_PLAYERS];
  Object *objects[MAX_OBJECTS];
  Character *characters[MAX_CHARACTERS];
  Space *spaces[MAX_SPACES];
  Link *links[MAX_LINKS];
  int n_spaces;
  int n_objects;
  int n_characters;
  int n_links;
  int n_players;
  int turn;
  InterfaceData *Data[MAX_PLAYERS];
  Bool finished;
};


/* DATA IMPLEMENTATION */
InterfaceData *data_create()
{
  InterfaceData *inDat = NULL;
  int i;
  
  inDat = (InterfaceData *)malloc(sizeof(struct _InterfaceData));
  if (inDat == NULL)
  {
    return NULL;
  }
  
  inDat->last_cmd = command_create();
  if (inDat->last_cmd == NULL)
  {
    free(inDat);
    return NULL;
  }
  
  for (i = 0; i < MESSAGE_SIZE; i++) 
  {
    inDat->s[i] = '\0';
  }

  return inDat; 
}

Status data_destroy(InterfaceData *data) 
{
  if (data == NULL)
  {
    return ERROR;
  }
  
  if (data->last_cmd != NULL)
  {
    command_destroy(data->last_cmd);
    data->last_cmd = NULL;
  }

  free(data);

  return OK;
}

Command *data_get_last_command(InterfaceData *data)
{
  if (!data)
  {
    return NULL;
  }
  return data->last_cmd;
}

char *data_get_message(InterfaceData *data)
{
  if (!data)
  {
    return NULL;
  }
  return data->s;
}

Status data_set_message(InterfaceData *data, char *m)
{
  if (!data || !m)
  {
    return ERROR;
  }
  strcpy(data->s, m); 
  return OK;
}

Status data_set_last_command(InterfaceData *data, Command *c)
{
  if (!data || !c)
  {
    return ERROR;
  }
  data->last_cmd = c;
  return OK;
}

/*TURN IMPLEMENTATION*/
int game_get_turn(Game *game)
{
  if (!game)
  {
    return -1;
  }
  return game->turn;
}

Status game_next_turn(Game *game)
{
  if (!game)
  {
    return ERROR;
  }
  game->turn++;
  if (game->turn >= game->n_players)
  {
    game->turn = 0;
  }
  
  return OK;
}


/* GAME IMPLEMENTATION */
Game *game_create()
{
  Game *game = NULL;
  int i, j;

  game = (Game *)malloc(sizeof(struct _Game));
  if (game == NULL)
  {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }
  game->n_spaces = 0;

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    game->objects[i] = NULL;
  }
  game->n_objects = 0;

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    game->characters[i] = NULL;
  }
  game->n_characters = 0;

  for (i = 0; i < MAX_LINKS; i++)
  {
    game->links[i] = NULL;
  }
  game->n_links = 0;

  for (i = 0; i < MAX_PLAYERS; i++)
  {
    game->players[i] = NULL;
  }
  game->n_players = 0;

  game->turn = 0;

  for (i = 0; i < MAX_PLAYERS; i++)
  {
    game->Data[i] = data_create();
    if (game->Data[i] == NULL)
    {
      for (j = 0; j < i; j++)
      {
        data_destroy(game->Data[j]);
      }
      free(game);
      return NULL;
    }
  }

  game->finished = FALSE;
  
  return game;
}

Status game_destroy(Game *game)
{
  int i;

  if (game == NULL)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES; i++)
  {
    if (game->spaces[i] != NULL)
    {
      space_destroy(game->spaces[i]);
    }
  }

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    if (game->objects[i] != NULL)
    {
      object_destroy(game->objects[i]);
    }
  }

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    if (game->characters[i] != NULL)
    {
      character_destroy(game->characters[i]);
    }
  }

  for (i = 0; i < MAX_LINKS; i++) 
  {
    if (game->links[i] != NULL) 
    {
      link_destroy(game->links[i]);
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) 
  {
    if (game->players[i] != NULL) 
    {
      player_destroy(game->players[i]);
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) 
  {
    if (game->Data[i] != NULL) 
    {
      data_destroy(game->Data[i]);
      game->Data[i] = NULL;
    }
  }

  free(game);

  return OK;
}

Status game_add_space(Game *game, Space *space)
{
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES))
  {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID || game == NULL)
  {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game)
{
  if (!game)
    return NO_ID;
  return player_get_location(game->players[game->turn]);
}

Status game_set_player_location(Game *game, Id id)
{
  if (!game)
    return ERROR;
  return player_set_location(game->players[game->turn], id);
}

Id game_get_object_location(Game *game, Id object_id)
{
  int i;
  if (player_has_object(game_get_player(game), object_id))
  {
    return WITH_PLAYER;
  }
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (space_has_object(game->spaces[i], object_id))
    {
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

Status game_set_object_location(Game *game, Id object_id, Id space_id)
{
  int i;
  if (!game || object_id == NO_ID)
    return ERROR;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (space_has_object(game->spaces[i], object_id))
    {
      space_remove_object(game->spaces[i], object_id);
    }
  }

  if (space_id != NO_ID && space_id != WITH_PLAYER)
  {
    space_add_object(game_get_space(game, space_id), object_id);
  }
  return OK;
}

Status game_add_object(Game *game, Object *object)
{
  if (!game || !object || game->n_objects >= MAX_OBJECTS)
  {
    return ERROR;
  }

  game->objects[game->n_objects] = object;
  game->n_objects++;

  return OK;
}

Object *game_get_object_from_id(Game *game, Id id)
{
  int i;
  if (game == NULL || id == NO_ID)
  {
    return NULL;
  }
  for (i = 0; i < game->n_objects; i++)
  {
    if (object_get_id(game->objects[i]) == id)
    {
      return game->objects[i];
    }
  }
  return NULL;
}

Id game_get_space_id_at(Game *game, int position)
{
  if (game == NULL || position < 0 || position >= game->n_spaces)
  {
    return NO_ID;
  }
  return space_get_id(game->spaces[position]);
}

Bool game_get_finished(Game *game)
{
  if (!game)
    return TRUE;
  return game->finished;
}

Status game_set_finished(Game *game, Bool finished)
{
  if (!game)
    return ERROR;
  game->finished = finished;
  return OK;
}

Player *game_get_player(Game *game)
{
  if (!game)
    return NULL;
  return game->players[game->turn];
}

void game_print(Game *game)
{
  int i = 0;
  if (!game)
    return;

  printf("\n\n-------------\n\n");
  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++)
  {
    space_print(game->spaces[i]);
  }
  printf("=> Player location: %ld\n", player_get_location(game->players[game->turn]));
}

int game_get_player_HP(Game *game)
{
  if (!game)
  {
    return 0;
  }
  return player_get_health(game_get_player(game));
}

Status game_add_character(Game *game, Character *character)
{
  if (game == NULL || character == NULL || game->n_characters >= MAX_CHARACTERS)
  {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;

  return OK;
}

Character *game_get_character_at(Game *game, int position)
{
  if (game == NULL || position < 0 || position >= MAX_CHARACTERS)
  {
    return NULL;
  }

  return game->characters[position];
}

int game_get_n_characters(Game *game)
{
  if (!game)
  {
    return 0;
  }
  return game->n_characters;
}

Id game_get_connection(Game *game, Id space_id, Direction direction)
{
  int i; 
  
  if (!game || space_id == NO_ID || direction == NO_DIR) 
  {
    return NO_ID;
  }

  for (i = 0; i < game->n_links; i++)
  {
    if (link_get_origin(game->links[i]) == space_id && link_get_direction(game->links[i]) == direction)
    {
      return link_get_destination(game->links[i]);
    }
  }
  
  return NO_ID;
}

Bool game_connection_is_open(Game *game, Id actual, Direction direction) 
{
  int i;

  if (!game || actual == NO_ID || direction == NO_DIR)
  {
    return FALSE;
  }

  for (i = 0; i < game->n_links; i++) 
  {
    if ((link_get_origin(game->links[i]) == actual) && (link_get_direction(game->links[i]) == direction))
    {
      return link_get_open(game->links[i]);
    }
  }

  return FALSE; 
}

Status game_add_link(Game *game, Link *link)
{
  if (!game || !link || game->n_links >= MAX_LINKS)
  {
    return ERROR;
  }

  game->links[game->n_links] = link;
  game->n_links++;

  return OK;
}

int game_get_n_obj(Game *game)
{
  if (!game)
  {
    return 0;
  }
  return game->n_objects;
}

Command *game_get_last_command(Game *game)
{
  if (!game || !game->Data[game->turn])
  {
    return NULL;
  }
  return data_get_last_command(game->Data[game->turn]);
}

Status game_set_last_command(Game *game, Command *command)
{
  if (!game || !game->Data[game->turn])
  {
    return ERROR;
  }
  return data_set_last_command(game->Data[game->turn], command);
}

char *game_get_s(Game *game)
{
  if (!game || !game->Data[game->turn])
  {
    return NULL;
  }
  return data_get_message(game->Data[game->turn]);
}

Status game_set_s(Game *game, char *message)
{
  if (!game || !game->Data[game->turn])
  {
    return ERROR;
  }
  return data_set_message(game->Data[game->turn], message);
}

int game_get_n_players(Game *game)
{
  if (!game)
  {
    return 0;
  }
  return game->n_players;
}

Status game_add_player(Game *game, Player *player)
{
  if (!game || !player || game->n_players >= MAX_PLAYERS)
  {
    return ERROR;
  }
  game->players[game->n_players] = player;
  game->n_players++;
  return OK;
}