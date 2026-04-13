/**
 * @brief Define la interfaz para el módulo de jugador
 *
 * @file player.h
 * @author MAR y MAT
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h" 
#include "set.h"

/**
 * @brief Estructura que almacena la información de un jugador
 */
typedef struct _Player Player;

/**
 * @brief Crea un nuevo jugador reservando memoria e inicializando sus campos
 * @author Profesores PPROG
 * @param id Identificador único para el nuevo jugador
 * @return Puntero al nuevo jugador o NULL en caso de error
 */
Player* player_create(Id id);

/**
 * @brief Destruye un jugador y libera la memoria asociada
 * @author Profesores PPROG
 * @param player Puntero al jugador a destruir
 * @return OK si se libera con éxito, ERROR en caso contrario
 */
Status player_destroy(Player* player);

/**
 * @brief Obtiene el identificador de un jugador
 * @author Profesores PPROG
 * @param player Puntero al jugador
 * @return El ID del jugador o NO_ID en caso de error
 */
Id player_get_id(Player* player);

/**
 * @brief Obtiene el nombre de un jugador
 * @author Profesores PPROG
 * @param player Puntero al jugador
 * @return Cadena con el nombre del jugador
 */
const char* player_get_name(Player* player);

/**
 * @brief Obtiene la localización actual del jugador
 * @author Profesores PPROG
 * @param player Puntero al jugador
 * @return El ID del espacio donde se encuentra el jugador
 */
Id player_get_location(Player* player);

/**
 * @brief Obtiene el conjunto de objetos que posee el jugador
 * @author MAR
 * @param player Puntero al jugador
 * @return Puntero al objeto Set que contiene los objetos del jugador
 */
Set* player_get_object(Player* player);

/**
 * @brief Obtiene los puntos de salud actuales del jugador
 * @author MAT
 * @param player Puntero al jugador
 * @return Entero con los puntos de salud
 */
int player_get_health(Player* player);

/**
 * @brief Obtiene la descripción gráfica (icono) del jugador
 * @author MAT
 * @param player Puntero al jugador
 * @return Cadena con la descripción gráfica
 */
const char* player_get_gdesc(Player* player);

/**
 * @brief Establece el nombre de un jugador
 * @author Profesores PPROG
 * @param player Puntero al jugador
 * @param name Cadena con el nuevo nombre
 * @return OK si se realiza con éxito, ERROR en caso contrario
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief Establece la localización de un jugador
 * @author Profesores PPROG
 * @param player Puntero al jugador
 * @param id ID del nuevo espacio para el jugador
 * @return OK o ERROR
 */
Status player_set_location(Player* player, Id id);

/**
 * @brief Establece la descripción gráfica del jugador
 * @author MAT
 * @param player Puntero al jugador
 * @param gdesc Cadena con la nueva descripción gráfica
 * @return OK o ERROR
 */
Status player_set_gdesc(Player* player, char* gdesc);

/**
 * @brief Establece los puntos de salud del jugador
 * @author MAT
 * @param player Puntero al jugador
 * @param health Nuevos puntos de salud
 * @return OK o ERROR
 */
Status player_set_health(Player* player, int health);

/**
 * @brief Asigna un objeto al jugador (sustituye el conjunto actual)
 * @author MAR
 * @param player Puntero al jugador
 * @param id ID del objeto
 * @return OK o ERROR
 */
Status player_set_object(Player* player, Id id);

/**
 * @brief Imprime la información del jugador por pantalla
 * @author Profesores PPROG
 * @param player Puntero al jugador
 * @return OK o ERROR
 */
Status player_print(Player* player);

/**
 * @brief Añade un objeto al inventario del jugador
 * @author MAR
 * @param player Puntero al jugador
 * @param id ID del objeto a añadir
 * @return OK si se añade con éxito, ERROR en caso contrario
 */
Status player_add_object(Player* player, Id id);

/**
 * @brief Elimina un objeto del inventario del jugador
 * @author MAR
 * @param player Puntero al jugador
 * @param id ID del objeto a eliminar
 * @return OK si se elimina con éxito, ERROR en caso contrario
 */
Status player_remove_object(Player* player, Id id);

/**
 * @brief Comprueba si el jugador posee un objeto específico
 * @author MAR
 * @param player Puntero al jugador
 * @param id ID del objeto a buscar
 * @return TRUE si lo posee, FALSE en caso contrario
 */
Bool player_has_object(Player* player, Id id);

#endif