/**
 * @brief Define la interfaz del módulo de efectos de objetos (USE)
 *
 * @file use.h
 * @author MAR
 * @version 1.0
 * @date 05-05-2026
 * @copyright GNU Public License
 */

#ifndef USE_H
#define USE_H

#include "game.h"

/**
 * @brief Función principal que distribuye la ejecución según el nombre del objeto
 * @author MAR
 * @param game Puntero a la estructura del juego
 * @param obj Puntero al objeto que se va a utilizar
 * @return Status OK si la ejecución fue exitosa, o ERROR en caso contrario
 */
Status use_execute(Game *game, Object *obj);

/**
 * @brief Ejecuta el efecto de usar una espada
 * @author MAR
 * @param game Puntero a la estructura del juego
 * @param ob Puntero al objeto espada
 * @return Status OK o ERROR
 */
Status use_sword(Game *game, Object *ob);

/**
 * @brief Ejecuta el efecto de usar un anillo
 * @author MAR
 * @param game Puntero a la estructura del juego
 * @param ob Puntero al objeto anillo
 * @return Status OK o ERROR
 */
Status use_ring(Game *game, Object *ob);

/**
 * @brief Ejecuta el efecto de usar una poción
 * @author MAR
 * @param game Puntero a la estructura del juego
 * @param obj Puntero al objeto poción
 * @return Status OK o ERROR
 */
Status use_potion(Game *game, Object *obj);

/**
 * @brief Ejecuta el efecto de usar una llave
 * @author MAR
 * @param game Puntero a la estructura del juego
 * @param key Puntero al objeto llave
 * @return Status OK o ERROR
 */
Status use_key(Game *game, Object *key);

/**
 * @brief Ejecuta el efecto de usar una hoguera
 * @author MAR
 * @param game Puntero a la estructura del juego
 * @param key Puntero al objeto hoguera
 * @return Status OK o ERROR
 */
Status use_campfire(Game *game, Object *key);

/**
 * @brief Ejecuta el efecto de usar una armadura
 * @author MAR
 * @param game Puntero a la estructura del juego
 * @param obj Puntero al objeto armadura
 * @return Status OK o ERROR
 */
Status use_armor(Game *game, Object *obj);

#endif