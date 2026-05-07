/**
 * @brief Implementa las acciones del juego
 * @file game_actions.c
 */

#include "game_actions.h"
#include "game.h"
#include "graphic_engine.h"
#include "game_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "use.h"
#include "object.h"

Status game_actions_update(Game *game, Command *cmd)
{
  CommandCode code;
  if (game == NULL || cmd == NULL)
    return ERROR;

  code = command_get_code(cmd);

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
  else if (code == RECRUIT)
  {
    return game_actions_recruit(game);
  }
  else if (code == ABANDON)
  {
    return game_actions_abandon(game);
  }
  else if (code == USE)
  {
    return game_actions_use(game);
  }
  else if (code == LOAD)
  {
    game_actions_load(game);
    return OK;
  }
  else if (code == SAVE)
  {
    game_actions_save(game);
    return OK;
  }
  else if (code == COLAB)
  {
    return game_actions_colab(game);
  }
  return ERROR;
}

Status hit_party(Game *game, Player *pl, int total_members, int enemy_dmg)
{
  int target_index, i, current_count = 0;
  Character *ch = NULL;

  if (pl == NULL || game == NULL)
    return ERROR;
  target_index = rand() % total_members;

  if (target_index == 0)
  {
    player_set_health(pl, player_get_health(pl) - enemy_dmg);
    return OK;
  }
  for (i = 0; i < game_get_n_characters(game); i++)
  {
    ch = game_get_character_at(game, i);
    if (ch && character_get_following(ch) == player_get_id(pl))
    {
      current_count++;
      if (current_count == target_index)
      {
        character_set_health(ch, character_get_health(ch) - enemy_dmg);
        return OK;
      }
    }
  }
  return ERROR;
}

Status game_actions_take(Game *game)
{
  Space *current_space = NULL;
  Player *player = NULL, *teammate_ptr = NULL;
  Object *obj = NULL;
  Id player_loc = NO_ID, obj_id = NO_ID, teammate_id = NO_ID;
  const char *arg = NULL;
  int i;

  if (!game)
    return ERROR;

  arg = command_get_arg(game_get_last_command(game));
  if (arg == NULL || strlen(arg) == 0)
    return ERROR;

  player = game_get_player(game);
  player_loc = game_get_player_location(game);
  current_space = game_get_space(game, player_loc);
  teammate_id = player_get_teammate(player);

  for (i = 0; i < game_get_n_obj(game); i++)
  {
    obj = game_get_object_at(game, i);
    if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0)
    {
      obj_id = object_get_id(obj);

      if (space_has_object(current_space, obj_id))
      {
        if (object_get_movable(obj) == FALSE)
        {
          game_set_s(game, "That object is too heavy to move.");
          return ERROR;
        }
        space_remove_object(current_space, obj_id);
        player_add_object(player, obj_id);
        game_set_object_location(game, obj_id, WITH_PLAYER);
        game_set_s(game, "You took the object.");
        return OK;
      }
    }
  }

  if (teammate_id != NO_ID)
  {
    teammate_ptr = game_get_player_from_id(game, teammate_id);
    if (teammate_ptr != NULL && player_get_location(teammate_ptr) == player_loc)
    {
      for (i = 0; i < game_get_n_obj(game); i++)
      {
        obj = game_get_object_at(game, i);
        if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0)
        {
          obj_id = object_get_id(obj);
          if (player_has_object(teammate_ptr, obj_id))
          {
            player_remove_object(teammate_ptr, obj_id);
            player_add_object(player, obj_id);
            game_set_s(game, "You took the object from your teammate");
            return OK;
          }
        }
      }
    }
  }

  game_set_s(game, "There is no such object here.");
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
    return ERROR;

  arg = command_get_arg(game_get_last_command(game));
  if (arg == NULL || arg[0] == '\0')
    return ERROR;

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
  Id player_loc = NO_ID;
  Space *space_ptr = NULL;
  Character *ch = NULL;
  const char *arg = NULL;
  int i = 0;

  if (!game)
    return ERROR;

  arg = command_get_arg(game_get_last_command(game));
  if (arg == NULL)
  {
    game_set_s(game, "Who do you want to talk to?");
    return ERROR;
  }

  player_loc = game_get_player_location(game);
  space_ptr = game_get_space(game, player_loc);

  for (i = 0; i < game_get_n_characters(game); i++)
  {
    ch = game_get_character_at(game, i);
    if (ch && strcasecmp(character_get_name(ch), arg) == 0)
    {
      if (space_has_character(space_ptr, character_get_id(ch)))
      {
        game_set_s(game, (char *)character_get_message(ch));
        return OK;
      }
    }
  }
  game_set_s(game, "You can't talk to someone who isn't here.");
  return ERROR;
}

Status game_actions_attack(Game *game)
{
  Id player_loc = NO_ID, player_id = NO_ID;
  Space *space_ptr = NULL;
  Character *ch = NULL, *enemy = NULL;
  Player *player = NULL;
  int i = 0, roll = 0, num_followers = 0;
  int damage_to_deal = 1;
  int enemy_dmg;
  int current_hp;
  char msg[100];

  if (!game)
    return ERROR;

  player = game_get_player(game);
  player_id = player_get_id(player);
  player_loc = game_get_player_location(game);
  space_ptr = game_get_space(game, player_loc);

  if (!space_ptr)
    return ERROR;

  for (i = 0; i < game_get_n_characters(game); i++)
  {
    ch = game_get_character_at(game, i);
    if (ch && character_get_following(ch) == player_id)
    {
      num_followers++;
    }
  }
  damage_to_deal += num_followers + player_get_damage(player);

  for (i = 0; i < game_get_n_characters(game); i++)
  {
    ch = game_get_character_at(game, i);
    if (ch && character_get_location(ch) == player_loc && character_get_friendly(ch) == FALSE)
    {
      if (character_get_health(ch) > 0)
      {
        enemy = ch;
        break;
      }
    }
  }

  if (enemy == NULL)
  {
    game_set_s(game, "There is no enemy here to attack.");
    return ERROR;
  }

  roll = rand() % 10;
  if (roll <= 4)
  {
    enemy_dmg = character_get_damage(enemy);
    hit_party(game, player, num_followers + 1, enemy_dmg);
    game_set_s(game, "The enemy hits your team!");
    if (player_get_health(player) <= 0)
      game_set_finished(game, TRUE);
  }
  else
  {
    current_hp = character_get_health(enemy);
    character_set_health(enemy, current_hp - damage_to_deal);

    if (character_get_health(enemy) <= 0)
    {
      character_set_location(enemy, NO_ID);
      space_remove_character(space_ptr, character_get_id(enemy));

      game_set_s(game, "Victory! Your team has killed the enemy.");
    }
    else
    {
      sprintf(msg, "You and your allies deal %d damage to the enemy!", damage_to_deal);
      game_set_s(game, msg);
    }
  }
  return OK;
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
    return ERROR;

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
  Player *player = NULL;
  Id player_loc = NO_ID, id_next = NO_ID, player_id = NO_ID;
  Direction dir = NO_DIR;
  const char *arg = NULL;
  Character *ch = NULL;
  int i;

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
  else if (strcasecmp(arg, "up") == 0 || strcasecmp(arg, "u") == 0)
    dir = U;
  else if (strcasecmp(arg, "down") == 0 || strcasecmp(arg, "d") == 0)
    dir = D;

  if (dir == NO_DIR)
    return ERROR;

  player_loc = game_get_player_location(game);
  if (player_loc == NO_ID)
    return ERROR;
  player = game_get_player(game);
  if (player == NULL)
    return ERROR;

  player_id = player_get_id(player);

  if (game_connection_is_open(game, player_loc, dir) == TRUE)
  {
    id_next = game_get_connection(game, player_loc, dir);
    if (id_next != NO_ID)
    {
      for (i = 0; i < game_get_n_characters(game); i++)
      {
        Space *old_space = NULL, *new_space = NULL;
        ch = game_get_character_at(game, i);
        if (ch && character_get_following(ch) == player_id)
        {
          old_space = game_get_space(game, character_get_location(ch));
          if (old_space)
            space_remove_character(old_space, character_get_id(ch));

          character_set_location(ch, id_next);

          new_space = game_get_space(game, id_next);
          if (new_space)
            space_add_character(new_space, character_get_id(ch));
        }
      }
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

Status game_actions_recruit(Game *game)
{
  Id player_loc = NO_ID, player_id = NO_ID;
  Space *space_ptr = NULL;
  Character *ch = NULL;
  const char *arg = NULL;
  int i = 0;

  if (!game)
    return ERROR;

  arg = command_get_arg(game_get_last_command(game));
  if (arg == NULL)
  {
    game_set_s(game, "Who sall be recruited?");
    return ERROR;
  }

  player_id = player_get_id(game_get_player(game));
  player_loc = game_get_player_location(game);
  space_ptr = game_get_space(game, player_loc);

  for (i = 0; i < game_get_n_characters(game); i++)
  {
    ch = game_get_character_at(game, i);
    if (ch && strcasecmp(character_get_name(ch), arg) == 0)
    {
      if (space_has_character(space_ptr, character_get_id(ch)))
      {
        if (character_get_friendly(ch) == TRUE)
        {
          character_set_following(ch, player_id);
          game_set_s(game, "Character recruited.");
          return OK;
        }
      }
    }
  }
  game_set_s(game, "That character is not here or cannot be recruited.");
  return ERROR;
}

Status game_actions_abandon(Game *game)
{
  Id player_loc = NO_ID, player_id = NO_ID;
  Space *space_ptr = NULL;
  Character *ch = NULL;
  const char *arg = NULL;
  int i;

  if (!game)
    return ERROR;

  arg = command_get_arg(game_get_last_command(game));
  if (arg == NULL)
  {
    game_set_s(game, "Who sall be abandonded?");
    return ERROR;
  }

  player_id = player_get_id(game_get_player(game));
  player_loc = game_get_player_location(game);
  space_ptr = game_get_space(game, player_loc);

  for (i = 0; i < game_get_n_characters(game); i++)
  {
    ch = game_get_character_at(game, i);
    if (ch && strcasecmp(character_get_name(ch), arg) == 0)
    {
      if (character_get_following(ch) == player_id)
      {
        character_set_following(ch, NO_ID);
        character_set_location(ch, player_loc);
        space_add_character(space_ptr, character_get_id(ch));
        game_set_s(game, "You have abandoned your friend.");
        return OK;
      }
    }
  }
  game_set_s(game, "That person is not following you.");
  return ERROR;
}

Status game_actions_use(Game *game)
{
  const char *arg = command_get_arg(game_get_last_command(game));
  Player *p = game_get_player(game);
  Object *obj = NULL;
  Id obj_id = NO_ID;
  int i;

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    obj = game_get_object_from_id(game, i + 1);
    if (obj && strcasecmp(object_get_name(obj), arg) == 0)
    {
      obj_id = object_get_id(obj);
      if (player_has_object(p, obj_id))
        break;
    }
    obj = NULL;
  }

  if (!obj)
  {
    game_set_s(game, "You don't have that object.");
    return ERROR;
  }

  if (use_execute(game, obj) == OK)
  {
    {
      player_remove_object(p, obj_id);
    }
    if (player_get_health(p) <= 0)
    {
      game_set_finished(game, TRUE);
    }

    return OK;
  }
  return ERROR;
}

void game_actions_load(Game *game)
{

  char path[MESSAGE_SIZE];
  const char *arg = NULL;
  if (!game)
  {
    game_set_s(game, "ERROR: while loading Save file");
    return;
  }

  arg = command_get_arg(game_get_last_command(game));
  if (arg == NULL || strlen(arg) == 0)
  {
    game_set_s(game, "ERROR: Which Save do you want to load?");
    return;
  }
  sprintf(path, "save/%s.dat", arg);
  if (game_management_load(game, path) == ERROR)
  {
    game_set_s(game, "ERROR: while loading Save file");
    return;
  }
  game_set_s(game, "Game loaded succesfully");
}

void game_actions_save(Game *game)
{
  const char *arg = NULL;
  char path[MESSAGE_SIZE];

  if (!game)
    return;

  arg = command_get_arg(game_get_last_command(game));

  if (arg == NULL || strlen(arg) == 0)
  {
    game_set_s(game, "ERROR: You must provide a filename.");
    return;
  }

  sprintf(path, "save/%s.dat", arg);

  if (game_management_save(game, path) == OK)
  {
    game_set_s(game, "Game saved successfully.");
  }
  else
  {
    game_set_s(game, "ERROR: Could not save the game.");
    return;
  }
}

Status game_actions_colab(Game *game)
{
  Id player_loc = NO_ID;
  Player *player = NULL, *player_teammate = NULL, *player_aux = NULL;
  const char *arg = NULL;
  char msg[MESSAGE_SIZE];
  int i;

  if (!game)
  {
    return ERROR;
  }

  if (game_get_multiplayer(game) == FALSE)
  {
    game_set_s(game, "You are in solo mode, you cannot collaborate with anyone");
    return ERROR;
  }

  player = game_get_player(game);
  if (!player)
  {
    return ERROR;
  }

  player_loc = player_get_location(player);

  arg = command_get_arg(game_get_last_command(game));
  if (!arg)
  {
    game_set_s(game, "Specify the name of the teammate to collaborate with.");
    return ERROR;
  }

  if (player_get_teammate(player) != NO_ID)
  {
    game_set_s(game, "You already have a teammate assigned.");
    return ERROR;
  }

  for (i = 0; i < game_get_n_players(game); i++)
  {
    player_aux = game_get_player_at(game, i);
    if (player_aux && strcasecmp(player_get_name(player_aux), arg) == 0)
    {
      player_teammate = player_aux;
      break;
    }
  }

  if (!player_teammate)
  {
    game_set_s(game, "No such player exists.");
    return ERROR;
  }

  if (player_get_location(player_teammate) != player_loc)
  {
    game_set_s(game, "That player is not in the same location as you.");
    return ERROR;
  }

  if (player_get_teammate(player_teammate) != NO_ID)
  {
    game_set_s(game, "That player already has a teammate.");
    return ERROR;
  }

  player_set_teammate(player, player_get_id(player_teammate));
  player_set_teammate(player_teammate, player_get_id(player));

  sprintf(msg, "You are now collaborating with %s.", player_get_name(player_teammate));
  game_set_s(game, msg);

  return OK;
}