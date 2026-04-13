/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author MAR
 * @version 1
 * @date 07-04-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"
#include "game_reader.h"
#include <unistd.h>

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

int main(int argc, char *argv[])
{
  Game *game = NULL;
  Graphic_engine *gengine = NULL;
  int result;
  Command *last_cmd = NULL;
  FILE *log = NULL;
  Status status = ERROR;
  CommandCode code = NO_CMD;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  srand(time(NULL));

  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }
  if (argc >= 4 && strcmp(argv[2], "-l") == 0)
  {
    log = fopen(argv[3], "w");
    if (!log)
    {
      fprintf(stderr, "Error opening log file %s\n", argv[3]);
      return 1;
    }
  }

  result = game_loop_init(&game, &gengine, argv[1]);
  if (result != 0)
  {
    fprintf(stderr, "Error while initializing game or graphic engine.\n");
    return 1;
  }

  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE))
  {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);
    status = game_actions_update(game, last_cmd);
    code = command_get_code(last_cmd);

    if (log != NULL && code != NO_CMD && code != UNKNOWN)
    {
      const char *arg = command_get_arg(last_cmd);
      if (arg != NULL && strlen(arg) > 0)
      {
        fprintf(log, "Player: %d\n%s %s: %s\n", game_get_turn(game)+1, cmd_to_str[code - NO_CMD][CMDL], arg, (status == OK) ? "OK" : "ERROR");
      }
      else
      {
        fprintf(log, "Player: %d\n%s: %s\n",game_get_turn(game)+1, cmd_to_str[code - NO_CMD][CMDL], (status == OK) ? "OK" : "ERROR");
      }
    }

    if (status == OK && game_get_n_players(game) > 1)
    {
      graphic_engine_paint_game(gengine, game);
      sleep(2);
    }

    if (status == OK)
    {
      game_next_turn(game);
    }
    last_cmd = game_get_last_command(game);
  }

  if (log)
  {
    fclose(log);
  }
  game_loop_cleanup(game, gengine);

  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name)
{
  if ((*game = game_create()) == NULL)
  {
    return 1;
  }
  if (game_create_from_file(*game, file_name) == ERROR)
  {
    return 1;
  }
  if ((*gengine = graphic_engine_create()) == NULL)
  {
    game_destroy(*game);
    return 2;
  }
  return 0;
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);
}