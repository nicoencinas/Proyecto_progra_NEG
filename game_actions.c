/**
 * @brief Implementa las acciones del juego
 * @file game_actions.c
 */

#include "game_actions.h"
#include "game.h"
#include "graphic_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

Status game_actions_update(Game *game, Command *cmd)
{
  CommandCode code;
  if (game == NULL || cmd == NULL)
    return ERROR;

  code = command_get_code(cmd);
  game_set_last_command(game, cmd);

  if (code == EXIT)
  {
    game_set_finished(game, TRUE);
    return OK;
  }
  else if (code == TAKE)
  {
    return game_actions_take(game);
  }
  else if (code == DROP)
  {
    return game_actions_drop(game);
  }
  else if (code == ATTACK)
  {
    return game_actions_attack(game);
  }
  else if (code == CHAT)
  {
    return game_actions_chat(game);
  }
  else if (code == INSPECT)
  {
    return game_actions_inspect(game);
  }
  else if (code == MOVE)
  {
    return game_actions_move(game);
  }

  return ERROR;
}

Status game_actions_take(Game *game)
{
  Space *current_space = NULL;
  Player *player = NULL;
  Object *obj = NULL;
  Id player_loc = NO_ID, obj_id = NO_ID;
  const char *arg = NULL;
  int i;

  if (!game)
  {
    return ERROR;
  }

  arg = command_get_arg(game_get_last_command(game));

  if (arg == NULL || strlen(arg) == 0)
  {
    printf("t missing arg\n");
    return ERROR;
  }

  player = game_get_player(game);
  player_loc = game_get_player_location(game);
  current_space = game_get_space(game, player_loc);

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    obj = game_get_object_from_id(game, i + 1);
    if (obj != NULL && strcmp(object_get_name(obj), arg) == 0)
    {
      obj_id = object_get_id(obj);

      if (space_has_object(current_space, obj_id))
      {
        space_remove_object(current_space, obj_id);
        player_add_object(player, obj_id);
        game_set_object_location(game, obj_id, WITH_PLAYER);
        return OK;
      }
    }
  }
  return ERROR;
}

Status game_actions_drop(Game *game)
{
  Space *current_space = NULL;
  Player *player = NULL;
  Object *obj = NULL;
  Id player_loc = NO_ID, obj_id = NO_ID;
  const char *arg = NULL;
  int i;

  if (!game)
  {
    return ERROR;
  }

  arg = command_get_arg(game_get_last_command(game));

  if (arg == NULL || arg[0] == '\0')
  {
    fprintf(stdout, "t missing arg\n");
    return ERROR;
  }

  player = game_get_player(game);
  player_loc = game_get_player_location(game);
  current_space = game_get_space(game, player_loc);

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    obj = game_get_object_from_id(game, i + 1);
    if (obj != NULL && strcmp(object_get_name(obj), arg) == 0)
    {
      obj_id = object_get_id(obj);

      if (player_has_object(player, obj_id))
      {
        player_remove_object(player, obj_id);
        space_add_object(current_space, obj_id);
        game_set_object_location(game, obj_id, player_loc);
        return OK;
      }
    }
  }
  return ERROR;
}

Status game_actions_chat(Game *game)
{
  Id player_loc = NO_ID, char_id = NO_ID;
  Space *space_ptr = NULL;
  Character *ch = NULL;
  int i = 0;

  if (!game)
    return ERROR;

  player_loc = game_get_player_location(game);
  space_ptr = game_get_space(game, player_loc);
  char_id = space_get_character(space_ptr);

  if (char_id != NO_ID)
  {
    for (i = 0; i < game_get_n_characters(game); i++)
    {
      ch = game_get_character_at(game, i);
      if (ch && character_get_id(ch) == char_id)
      {
        if (character_get_friendly(ch) == TRUE)
        {
          game_set_s(game, (char *)character_get_message(ch));
          return OK;
        }
        else
        {
          game_set_s(game, "...");
          return OK;
        }
      }
    }
  }
  game_set_s(game, "There's no one here.");
  return ERROR;
}

Status game_actions_attack(Game *game)
{
  Id player_loc = NO_ID, char_id = NO_ID;
  Space *space_ptr = NULL;
  Character *ch = NULL;
  Player *player = NULL;
  int i = 0, roll = 0;

  if (!game)
    return ERROR;

  player = game_get_player(game);
  player_loc = game_get_player_location(game);
  space_ptr = game_get_space(game, player_loc);

  char_id = space_get_character(space_ptr);

  if (char_id != NO_ID)
  {
    for (i = 0; i < game_get_n_characters(game); i++)
    {
      ch = game_get_character_at(game, i);

      if (ch && character_get_id(ch) == char_id)
      {
        if (character_get_friendly(ch) == FALSE)
        {
          if (character_get_health(ch) > 0)
          {
            roll = rand() % 10;
            if (roll >= 0 && roll <= 4)
            {
              player_set_health(player, player_get_health(player) - 1);
              game_set_s(game, "The enemy hits you! You lose 1 HP.");
              if (player_get_health(player) <= 0)
              {
                game_set_finished(game, TRUE);
              }
              return OK;
            }
            else
            {
              character_set_health(ch, character_get_health(ch) - 1);
              if (character_get_health(ch) <= 0)
              {
                game_set_s(game, "Victory! You have killed the enemy.");
              }
              else
              {
                game_set_s(game, "You hit the enemy! It loses 1 HP.");
              }
              return OK;
            }
          }
          else
          {
            game_set_s(game, "The enemy is already dead.");
            return ERROR;
          }
        }
        else
        {
          game_set_s(game, "You cannot attack a friend!");
          return ERROR;
        }
      }
    }
  }
  game_set_s(game, "There is no one here to attack.");
  return ERROR;
}

Status game_actions_inspect(Game *game)
{
  Id player_loc = NO_ID, obj_id = NO_ID;
  Space *space_ptr = NULL;
  Player *player = NULL;
  Object *obj_ptr = NULL;
  const char *arg = NULL;
  int i;

  if (!game)
    return ERROR;
  arg = command_get_arg(game_get_last_command(game));
  if (arg == NULL || strlen(arg) == 0)
  {
    return ERROR;
  }

  player = game_get_player(game);
  player_loc = game_get_player_location(game);
  space_ptr = game_get_space(game, player_loc);

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    obj_ptr = game_get_object_from_id(game, i + 1);

    if (obj_ptr != NULL && strcmp(object_get_name(obj_ptr), arg) == 0)
    {
      obj_id = object_get_id(obj_ptr);

      if (space_has_object(space_ptr, obj_id) || player_has_object(player, obj_id))
      {
        game_set_s(game, (char *)object_get_desc(obj_ptr));
        return OK;
      }
    }
  }

  game_set_s(game, "There is nothing here");
  return ERROR;
}

Status game_actions_move(Game *game)
{
  Id player_loc = NO_ID, id_next = NO_ID;
  Direction dir = NO_DIR;
  const char *arg = NULL;

  if (!game)
    return ERROR;

  arg = command_get_arg(game_get_last_command(game));
  if (arg == NULL || strlen(arg) == 0)
    return ERROR;

  if (strcasecmp(arg, "north") == 0 || strcasecmp(arg, "n") == 0)
    dir = N;
  else if (strcasecmp(arg, "south") == 0 || strcasecmp(arg, "s") == 0)
    dir = S;
  else if (strcasecmp(arg, "east") == 0 || strcasecmp(arg, "e") == 0)
    dir = E;
  else if (strcasecmp(arg, "west") == 0 || strcasecmp(arg, "w") == 0)
    dir = W;

  if (dir == NO_DIR)
    return ERROR;

  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID)
    return ERROR;

  if (game_connection_is_open(game, player_loc, dir) == TRUE)
  {
    id_next = game_get_connection(game, player_loc, dir);

    if (id_next != NO_ID)
    {
      game_set_player_location(game, id_next);
      game_set_s(game, "Move (m).");
      return OK;
    }
  }
  else
  {
    game_set_s(game, "The way is blocked.");
    return ERROR;
  }
  return ERROR;
}