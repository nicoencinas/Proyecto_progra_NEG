/**
 * @brief It implements a textual graphic engine
 * @file graphic_engine.c
 */

#include "graphic_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "game.h"
#include "player.h"
#include "character.h"

#define WIDTH_MAP 96
#define WIDTH_DES 58
#define WIDTH_BAN 50
#define HEIGHT_MAP 32
#define HEIGHT_BAN 1
#define HEIGHT_HLP 4
#define HEIGHT_FDB 6

struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback;
};

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;
  if (ge)
    return ge;
  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL)
    return NULL;
  ge->map      = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner   = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help     = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);
  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_right = NO_ID, id_left = NO_ID, id_char = NO_ID;
  Space *space_act = NULL, *space_back = NULL, *space_next = NULL, *space_left = NULL, *space_right = NULL;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, n_chars;
  Object *temp_obj = NULL;
  Character *temp_char = NULL;

  char p_c_icon[16] = "               ";
  char obj_names[16] = "               ";
  char p_icon[6]  = "     ";
  char c_icon[7]  = "      ";

  if (!ge || !game)
    return;

  sprintf(str, " The haunted castle  -  Player %d's turn", game_get_turn(game) + 1);
  screen_area_puts(ge->banner, str);

  screen_area_clear(ge->map);

  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act  = game_get_space(game, id_act);
    id_back    = game_get_connection(game, id_act, N);
    id_next    = game_get_connection(game, id_act, S);
    id_left    = game_get_connection(game, id_act, W);
    id_right   = game_get_connection(game, id_act, E);

    space_back  = game_get_space(game, id_back);
    space_next  = game_get_space(game, id_next);
    space_left  = game_get_space(game, id_left);
    space_right = game_get_space(game, id_right);
    
    sprintf(p_icon, "%.3s", player_get_gdesc(game_get_player(game)));

    id_char = space_get_character(space_act);
    if (id_char != NO_ID)
    {
      for (i = 0; i < game_get_n_characters(game); i++)
      {
        temp_char = game_get_character_at(game, i);
        if (temp_char && character_get_id(temp_char) == id_char)
        {
          sprintf(c_icon, "%.6s", character_get_gdesc(temp_char));
          break;
        }
      }
    }
    
    if (temp_char != NULL && character_get_health(temp_char) > 0)
    {
      sprintf(p_c_icon, "%-3s    %-6s", p_icon, c_icon);
    } 
    else
    {
      sprintf(p_c_icon, "%-3s    ", p_icon);
    }
    
    /* Object name in current space */
    for (i = 0; i < MAX_OBJECTS; i++)
    {
      temp_obj = game_get_object_from_id(game, i);
      if (temp_obj && game_get_object_location(game, object_get_id(temp_obj)) == id_act)
      {
        sprintf(obj_names, "%-13.13s", object_get_name(temp_obj));
        break;
      }
    }
    
    if (id_back != NO_ID && space_back != NULL)
    {
      sprintf(str, "                                      +---------------+ %d", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "                                      |               |");
      screen_area_puts(ge->map, str);
      for (i = 0; i < 5; i++)
      {
        sprintf(str, "                                      | %-13.13s |", space_get_gdesc_at(space_back, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                                      |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                      +-------^-------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                                      ");
      screen_area_puts(ge->map, str);
    }
    
    if (id_left != NO_ID && id_right != NO_ID)
    {
      sprintf(str, "           +---------------+          +---------------+ %d           +---------------+", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "           |               |          | %-13.13s |             |               |", p_c_icon);
    }
    else if (id_left != NO_ID)
    {
      sprintf(str, "           +---------------+          +---------------+ %d", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "           |               |          | %-13.13s |", p_c_icon);
    }
    else if (id_right != NO_ID)
    {
      sprintf(str, "                                      +---------------+ %d           +---------------+", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "                                      | %-13.13s |             |               |", p_c_icon);
    }
    else
    {
      sprintf(str, "                                      +---------------+ %d", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "                                      | %-13.13s |", p_c_icon);
    }
    screen_area_puts(ge->map, str);
    
    for (i = 0; i < 5; i++)
    {
      if (id_left != NO_ID && id_right != NO_ID && space_left != NULL && space_right != NULL)
      {
        sprintf(str, (i == 2)
        ? "           | %-13.13s |         <| %-13.13s |>            | %-13.13s |"
        : "           | %-13.13s |          | %-13.13s |             | %-13.13s |",
        space_get_gdesc_at(space_left, i), space_get_gdesc_at(space_act, i), space_get_gdesc_at(space_right, i));
      }
      else if (id_left != NO_ID && space_left != NULL)
      {
        sprintf(str, (i == 2)
        ? "           | %-13.13s |         <| %-13.13s |"
        : "           | %-13.13s |          | %-13.13s |",
        space_get_gdesc_at(space_left, i), space_get_gdesc_at(space_act, i));
      }
      else if (id_right != NO_ID && space_right != NULL)
      {
        sprintf(str, (i == 2)
        ? "                                      | %-13.13s |>            | %-13.13s |"
        : "                                      | %-13.13s |             | %-13.13s |",
        space_get_gdesc_at(space_act, i), space_get_gdesc_at(space_right, i));
      }
      else
      {
        sprintf(str, "                                      | %-13.13s |", space_get_gdesc_at(space_act, i));
      }
      screen_area_puts(ge->map, str);
    }
    
    if (id_left != NO_ID && id_right != NO_ID)
    {
      sprintf(str, "           |               |          | %-13.13s |             |               |", obj_names);
      screen_area_puts(ge->map, str);
      sprintf(str, "           +---------------+          +---------------+             +---------------+");
    }
    else if (id_left != NO_ID)
    {
      sprintf(str, "           |               |          | %-13.13s |", obj_names);
      screen_area_puts(ge->map, str);
      sprintf(str, "           +---------------+          +---------------+");
    }
    else if (id_right != NO_ID)
    {
      sprintf(str, "                                      | %-13.13s |             |               |", obj_names);
      screen_area_puts(ge->map, str);
      sprintf(str, "                                      +---------------+             +---------------+");
    }
    else
    {
      sprintf(str, "                                      | %-13.13s |", obj_names);
      screen_area_puts(ge->map, str);
      sprintf(str, "                                      +---------------+");
    }
    screen_area_puts(ge->map, str);

    if (id_next != NO_ID && space_next != NULL)
    {
      sprintf(str, "                                               v       ");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                      +---------------+ %d", (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "                                      |               |");
      screen_area_puts(ge->map, str);
      for (i = 0; i < 5; i++)
      {
        sprintf(str, "                                      | %-13.13s |", space_get_gdesc_at(space_next, i));
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                                      |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                                      +---------------+");
      screen_area_puts(ge->map, str);
    }
  }
  screen_area_clear(ge->descript);

  screen_area_puts(ge->descript, "   Objects:");
  for (i = 0; i < MAX_OBJECTS; i++)
  {
    temp_obj = game_get_object_from_id(game, i);
    if (temp_obj)
    {
      Id loc = game_get_object_location(game, object_get_id(temp_obj));
      if (loc != NO_ID && loc != WITH_PLAYER)
      {
        sprintf(str, "      %s: %ld", object_get_name(temp_obj), (long)loc);
        screen_area_puts(ge->descript, str);
      }
    }
  }

  screen_area_puts(ge->descript, " ");
  screen_area_puts(ge->descript, " ");

  screen_area_puts(ge->descript, "   Characters:");
  n_chars = game_get_n_characters(game);
  for (i = 0; i < n_chars; i++)
  {
    Character *ch = game_get_character_at(game, i);
    if (ch)
    {
      sprintf(str, "      %-6s: %ld (%d)",
              character_get_gdesc(ch),
              (long)character_get_location(ch),
              character_get_health(ch));
      screen_area_puts(ge->descript, str);
    }
  }

  screen_area_puts(ge->descript, " ");
  screen_area_puts(ge->descript, " ");

  sprintf(str, "   Player %d: space %ld  HP:%d",
          game_get_turn(game) + 1,
          (long)id_act,
          (game_get_player(game) ? player_get_health(game_get_player(game)) : 0));
  screen_area_puts(ge->descript, str);

  screen_area_puts(ge->descript, "   Inventory:");
  for (i = 0; i < MAX_OBJECTS; i++)
  {
    temp_obj = game_get_object_from_id(game, i);
    if (temp_obj)
    {
      Id loc = game_get_object_location(game, object_get_id(temp_obj));
      if (loc == WITH_PLAYER)
      {
        sprintf(str, "      %s", object_get_name(temp_obj));
        screen_area_puts(ge->descript, str);
      }
    }
  }

  screen_area_clear(ge->help);
  screen_area_puts(ge->help, " The commands you can use are:");
  screen_area_puts(ge->help, " move/m  take/t  drop/d  chat/c  attack/a  inspect/i  exit/e");

  last_cmd = command_get_code(game_get_last_command(game));

  if (last_cmd == CHAT || last_cmd == ATTACK || last_cmd == INSPECT || last_cmd == MOVE)
  {
    char *msg = game_get_s(game);
    if (msg != NULL && msg[0] != '\0')
    {
      sprintf(str, " Action result: %-60.60s", msg);
    }
    else
    {
      sprintf(str, " Action result: (none)");
    }
    screen_area_puts(ge->feedback, str);
  }
  else if (last_cmd != NO_CMD && last_cmd != UNKNOWN)
  {
    sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
    screen_area_puts(ge->feedback, str);
  }

  screen_paint(game_get_turn(game));
  printf("prompt:> ");
}