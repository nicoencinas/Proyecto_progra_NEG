
/**
 * @brief It defines the game_manegement interpreter interface
 *
 * @file game_management.h
 * @author  M.A, M.C, JOEL y NICO
 * @version 1
 * @date 27-04-2026
 * @copyright GNU Public License
 */

#include "stdio.h"
#include "types.h"
#include "space.h"
#include "game.h"
#include "stdlib.h"
#include "string.h"

#ifndef GAME_MANAGEMENT
#define GAME_MANAGEMENT

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
Status game_reader_load_objects(Game *game, char *filename);

/**
 * @brief Lee los datos del fichero castle.dat y carga players
 * @author MAT y MAR
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_reader_load_players(Game *game, char *filename);

/**
 * @brief Lee los datos acerca del fichero castle.dat y carga links
 * @author NICO y JOEL
 * 
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_reader_load_links(Game *game, char *filename);

/**
 * @brief Lee los datos acerca del fichero castle.dat y carga followers
 * @author NICO
 * 
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_reader_load_followers(Game *game, char *filename);

/**
 * @brief Guarda el estado actual de una partida para poder recuperarla más adelante
 * @author JOEL
 * 
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_management_save(Game *game, char *filename);

/**
 * @brief Carga el estado actual de una partida
 * @author JOEL
 * 
 * @param game Puntero al juego
 * @param filename Nombre del fichero de datos
 * @return OK o ERROR
 */
Status game_management_load(Game *game, char *filename);

Status game_reader_load_characters(Game *game, char *filename);

#endif
