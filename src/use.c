/**
 * @brief Implementación de efectos específicos por objeto
 * @file use.c
 * @author MAR JOEL NICO MAT
 */

#include "use.h"
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "link.h"
#include "game.h"
#include "player.h"

Status use_execute(Game *game, Object *obj)
{
  const char *name = NULL;
  if (!game || !obj)
    return ERROR;

  name = object_get_name(obj);

  /* Selección de la función  según el nombre del objeto */
  if (strcasecmp(name, "Key") == 0 || strcasecmp(name, "Map Key") == 0)
    return use_key(game, obj);

  if (strcasecmp(name, "Potion") == 0 || strcasecmp(name, "Poison") == 0)
    return use_potion(game, obj);

  if (strcasecmp(name, "Campfire") == 0)
    return use_campfire(game, obj);

  if (strcasecmp(name, "W.Sword") == 0 || strcasecmp(name, "S.Sword") == 0)
    return use_sword(game, obj);
  if (strcasecmp(name, "W.Armor") == 0 || strcasecmp(name, "S.Armor") == 0)
    return use_armor(game, obj);
  if (strcasecmp(name, "Ring") == 0 || strcasecmp(name, "Ring") == 0)
    return use_ring(game, obj);

  game_set_s(game, "This object has no special effect.");
  return ERROR;
}

Status use_key(Game *game, Object *key)
{
  Id link_id_to_open = NO_ID;
  Link *link = NULL;
  Id player_loc = NO_ID;
  Id origin = NO_ID, destination = NO_ID;
  int i;

  if (!game || !key)
    return ERROR;

  link_id_to_open = object_get_open(key);
  if (link_id_to_open == NO_ID)
  {
    game_set_s(game, "This key doesn't seem to open anything.");
    return ERROR;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    link = game_get_link_at(game, i);
    if (link != NULL && link_get_id(link) == link_id_to_open)
    {
      break; /* Encontrado */
    }
    link = NULL;
  }

  if (link == NULL)
  {
    game_set_s(game, "The door this key opens does not exist.");
    return ERROR;
  }

  /*Origen y destino*/
  player_loc = game_get_player_location(game);
  origin = link_get_origin(link);
  destination = link_get_destination(link);

  if (player_loc != origin && player_loc != destination)
  {
    game_set_s(game, "You are not near the lock this key opens.");
    return ERROR;
  }
  if (link_set_open(link, TRUE) == OK)
  {
    game_set_s(game, "You insert the key and turn it. The path is now open!");
    return OK;
  }

  return ERROR;
}

Status use_potion(Game *game, Object *obj)
{
  Player *p = NULL;
  int health_mod;

  if (!game || !obj)
    return ERROR;

  p = game_get_player(game);
  health_mod = object_get_health(obj);

  player_set_health(p, player_get_health(p) + health_mod);

  if (health_mod > 0)
    game_set_s(game, "You feel refreshed after drinking the Potion.");
  else
    game_set_s(game, "It was poison! You feel terrible.");

  return OK;
}

Status use_campfire(Game *game, Object *obj)
{
  Player *p = NULL;
  if (!game || !obj)
    return ERROR;

  p = game_get_player(game);
  player_set_health(p, object_get_health(obj));

  game_set_s(game, "You rest by the campfire. Your HP has been restored.");
  return OK;
}

Status use_sword(Game *game, Object *obj)
{
  Player *p = NULL;
  if (!game || !obj)
    return ERROR;

  p = game_get_player(game);
  /* Sumamos el bono de daño del objeto al daño actual del jugador */
  player_set_damage(p, player_get_damage(p) + object_get_health(obj));

  game_set_s(game, "You equip the sword. Your attack power increases!");
  return OK;
}
Status use_armor(Game *game, Object *obj)
{
  Player *p = NULL;
  if (!game || !obj)
    return ERROR;

  p = game_get_player(game);

  player_set_max_health(p, object_get_health(obj) + player_get_max_health(p));
  game_set_s(game, "You equip the armor. Your HP increases!");
  return OK;
}

Status use_ring(Game *game, Object *obj)
{
  Player *p = NULL;
  if (!game || !obj)
    return ERROR;

  p = game_get_player(game);
  player_set_max_turn(p, player_get_max_turn(p) + 1);

  return OK;
}