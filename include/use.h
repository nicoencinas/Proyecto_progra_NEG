/**
 * @brief Declaraciones para el módulo de efectos de objetos (USE)
 * @file use.h
 * @author MAR
 */

#ifndef USE_H
#define USE_H

#include "game.h"

/**
 * @brief Función principal que distribuye el uso según el nombre del objeto
 */
Status use_execute(Game *game, Object *obj);

/*Añadir mas si se os ocurren*/
Status use_sword(Game *game, Object *ob);
Status use_ring(Game *game, Object *ob);
Status use_potion(Game *game, Object *obj);
Status use_key(Game *game, Object *key);
Status use_campfire(Game *game, Object *key);
Status use_armor(Game *game, Object *obj);
#endif