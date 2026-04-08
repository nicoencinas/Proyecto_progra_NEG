
/**
 * @brief It defines the game_reader interpreter interface
 *
 * @file command.h
 * @author  M.A y M.C
 * @version 0
 * @date 10-02-2026
 * @copyright GNU Public License
 */

#include "stdio.h"
#include "types.h"
#include "space.h"
#include "game.h"
#include "stdlib.h"
#include "string.h"

#ifndef GAME_READER
#define GAME_READER

Status game_create_from_file(Game *game, char *filename);
Status game_reader_load_spaces(Game *game, char *filename);
Status game_reader_load_object(Game *game, char *filename);
Status game_reader_load_player(Game *game, char *filename);

#endif
