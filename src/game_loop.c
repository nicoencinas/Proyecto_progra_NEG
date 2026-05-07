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
#include "player.h"
#include "game_actions.h"
#include "graphic_engine.h"
#include "game_management.h"
#include <unistd.h>
#include "game_rules.h"

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

int main(int argc, char *argv[])
{
  Game *game = NULL;
  Game *temp_game = NULL;
  Player *pl = NULL;
  Graphic_engine *gengine = NULL;
  int i, choice = 0;
  char save_name[WORD_SIZE];
  char save_path[WORD_SIZE + 100];
  Command *last_cmd = NULL;
  FILE *log = NULL;
  Status status = ERROR;
  CommandCode code = NO_CMD;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Bool is_det = FALSE;
  Bool loaded_from_save = FALSE;
  const char *arg = NULL;
  char save_path_loop[WORD_SIZE];

  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  srand(time(NULL));

  printf("\033[1;31m");

  printf("         I_I              I_I                                                                                                       I_I              I_I         \n");
  printf("       _|_|_|_          _|_|_|_                                                                                                   _|_|_|_          _|_|_|_       \n");
  printf("      [_______]        [_______]                                                                                                 [_______]        [_______]      \n");
  printf("       |     |          |     |                                                                                                   |     |          |     |       \n");
  printf("       |     |__________|     |                                                                                                   |     |__________|     |       \n");
  printf("       |                      |                                                                                                   |                      |       \n");
  printf("       |      _ _    _ _      |                                                                                                   |      _ _    _ _      |       \n");
  printf("       |     |_|_|  |_|_|     |                                                                                                   |     |_|_|  |_|_|     |       \n");
  printf("       |                      |                ____________________________________________________________________               |                      |       \n");
  printf("       |      _ _    _ _      |               /                                                                    \\              |      _ _    _ _      |       \n");
  printf("       |     |_|_|  |_|_|     |              /           \033[1;37m      T H E      D A R K      C A S T L E          \033[1;31m        \\             |     |_|_|  |_|_|     |       \n");
  printf("       |                      |             /________________________________________________________________________\\            |                      |       \n");
  printf("       |      _ _    _ _      |             |                                                                       |             |      _ _    _ _      |       \n");
  printf("       |     |_|_|  |_|_|     |             |          __________________________________________                   |             |     |_|_|  |_|_|     |       \n");
  printf("       |                      |_____________|_________|__________________________________________|__________________|_____________|                      |       \n");
  printf("       |                      |             |         |                                          |                  |             |                      |       \n");
  printf("       |      _ _    _ _      |             |         |                                          |                  |             |      _ _    _ _      |       \n");
  printf("       |     |_|_|  |_|_|     |             |         |                                          |                  |             |     |_|_|  |_|_|     |       \n");
  printf("       |                      |_____________|_________|__________________________________________|__________________|_____________|                      |       \n");
  printf("       |                                                                                                                                                 |       \n");
  printf("       |                    [1] N E W   G A M E (S O L O)  |  [2]  N E W   G A M E (M U L T I P L A Y E R)  |  [3]  L O A D   G A M E                    |       \n");
  printf("       |_________________________________________________________________________________________________________________________________________________|       \n");

  printf("\033[0m");

  printf("\n\n                                           >> COME IF YOU DARE: ");

  if (scanf("%d", &choice) != 1)
  {
    choice = 1;
  }

  while (getchar() != '\n');

  /* ========================================== */
  /* INICIALIZACION DEL JUEGO                   */
  /* ========================================== */

  if (game_loop_init(&game, &gengine, argv[1]) != 0)
  {
    fprintf(stderr, "Error while initializing game or graphic engine.\n");
    return 1;
  }

  if (choice == 1)
  {
    game_set_multiplayer(game, FALSE);
  }

  if (choice == 3)
  {
    printf("  Introduce el nombre de la partida (ej: save1): ");
    if (scanf("%s", save_name) == 1)
    {
      sprintf(save_path, "save/%s.dat", save_name);
      printf("  Loading game '%s'...\n", save_path);

      temp_game = game_create();
      if (temp_game != NULL && game_management_load(temp_game, save_path) == OK)
      {
        game_destroy(game);
        game = temp_game;
        temp_game = NULL;
        loaded_from_save = TRUE;
        printf("Game loaded succesfully");
      }
      else
      {
        if (temp_game != NULL)
        {
          game_destroy(temp_game);
        }
        printf("ERROR: Unable to load previous game. Starting a new game...");
      }
    }
    while (getchar() != '\n');
  }

  if (choice == 2)
  {
    game_set_multiplayer(game, TRUE);
  }

  if (loaded_from_save == FALSE)
  {
    printf("   Iniciating a new adventure...\n");
  }

  printf("\n  Press enter to discover the darkness...");
  getchar();

  /* ========================================== */
  /* PARAMETROS DE LINEA DE COMANDOS            */
  /* ========================================== */
  if (argc >= 4 && strcmp(argv[2], "-l") == 0)
  {
    log = fopen(argv[3], "w");
    if (!log)
    {
      fprintf(stderr, "Error opening log file %s\n", argv[3]);
      game_loop_cleanup(game, gengine);
      return 1;
    }
  }

  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-d") == 0)
      is_det = TRUE;
  }

  if (is_det)
    srand(1);
  else
    srand(time(NULL));

  /* ========================================== */
  /* INICIO DEL BUCLE GRAFICO                   */
  /* ========================================== */
  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE))
  {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);

    code = command_get_code(last_cmd);

    if (code == LOAD)
    {
      arg = command_get_arg(last_cmd);

      if (arg != NULL && strlen(arg) > 0)
      {
        sprintf(save_path_loop, "save/%s.dat", arg);

        /* Creamos un juego temporal totalmente limpio */
        temp_game = game_create();

        /* Intentamos cargar el archivo en el juego limpio */
        if (temp_game != NULL && game_management_load(temp_game, save_path_loop) == OK)
        {
          /* Destruimos el juego actual */
          game_destroy(game);

          /* Sustituimos el puntero principal por la nueva partida cargada */
          game = temp_game;
          temp_game = NULL;
          status = OK;

          /* Actualizamos last_cmd porque el antiguo se destruyo con game_destroy */
          last_cmd = game_get_last_command(game);
        }
        else
        {
          /* Si falla, destruimos la copia temporal y no tocamos la partida actual */
          if (temp_game)
          {
            game_destroy(temp_game);
            temp_game = NULL;
          }
          status = ERROR;
        }
      }
      else
      {
        status = ERROR;
      }
    }
    else
    {
      status = game_actions_update(game, last_cmd);
    }

    if (status == OK && code != LOAD)
    {
      game_rules_run(game);
    }

    code = command_get_code(last_cmd);

    if (log != NULL && code != NO_CMD && code != UNKNOWN)
    {
      arg = command_get_arg(last_cmd);
      if (arg != NULL && strlen(arg) > 0)
      {
        fprintf(log, "Player: %d\n%s %s: %s\n", game_get_turn(game) + 1,
                cmd_to_str[code - NO_CMD][CMDL], arg,
                (status == OK) ? "OK" : "ERROR");
      }
      else
      {
        fprintf(log, "Player: %d\n%s: %s\n", game_get_turn(game) + 1,
                cmd_to_str[code - NO_CMD][CMDL],
                (status == OK) ? "OK" : "ERROR");
      }
    }

    if (status == OK && game_get_n_players(game) > 1)
    {
      graphic_engine_paint_game(gengine, game);
    }

    pl = game_get_player(game);

    if (status == OK && pl != NULL)
    {
      if (player_get_n_turn(pl) < player_get_max_turn(pl))
      {
        player_set_n_turn(pl, player_get_n_turn(pl) + 1);
      }
      else
      {
        player_set_n_turn(pl, 1);
        game_next_turn(game);
      }
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
    game_destroy(*game);
    *game = NULL;
    return 1;
  }
  if ((*gengine = graphic_engine_create()) == NULL)
  {
    game_destroy(*game);
    *game = NULL;
    return 2;
  }
  return 0;
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);
}