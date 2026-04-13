
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

/**
 * @brief Lee los datos del fichero castle.dat y crea el juego
 * @author MAR
 * 
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief Lee los datos del fichero castle.dat y carga spaces
 * @author MAT y MAR
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_reader_load_spaces(Game *game, char *filename);

/**
 * @brief Lee los datos del fichero castle.dat y carga obj
 * @author MAR
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_reader_load_object(Game *game, char *filename);

/**
 * @brief Lee los datos del fichero castle.dat y carga players
 * @author MAT y MAR
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_reader_load_player(Game *game, char *filename);

/**
 * @brief Lee los datos acerca del fichero castle.dat y carga links
 * @author NICO y JOEL
 * 
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_reader_load_links(Game *game, char *filename);


#endif
