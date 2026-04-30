/**
 * @brief Define las reglas del juego y eventos no deterministas
 *
 * @file game_rules.h
 * @author MAR
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game.h"

/**
 * @brief Ejecuta la lógica de reglas del juego de forma no determinista
 * @author MAR
 * * @param game Puntero a la estructura del juego
 * @return Status OK si se ejecuta correctamente, ERROR de lo contrario
 */
Status game_rules_run(Game *game);

/**
 * @brief REGLA: Un enemigo ataca desde las sombras restando salud al jugador
 * @author MAR
 * * @param game Puntero a la estructura del juego
 */
void rule_enemy_ambush(Game *game);

/**
 * @brief REGLA: Una niebla teletransporta al jugador a una ubicación inicial
 * @author MAR
 * * @param game Puntero a la estructura del juego
 */
void rule_fog_teleport(Game *game);

/**
 * @brief REGLA: Un fantasma roba un objeto del inventario del jugador
 * @author MAR
 * * @param game Puntero a la estructura del juego
 */
void rule_ghost_steals_item(Game *game);

/**
 * @brief REGLA: Un terremoto que elimina a un aliado o hiere al jugador
 * @author MAR
 * * @param game Puntero a la estructura del juego
 */
void rule_earthquake_kill_ch(Game *game);

/**
 * @brief REGLA: Una lluvia mística que cura al jugador
 * @author MAR
 * * @param game Puntero a la estructura del juego
 */
void rule_healing_rain(Game *game);

/**
 * @brief REGLA: Una bendición que aumenta el daño del jugador
 * @author MAR
 * * @param game Puntero a la estructura del juego
 */
void rule_strength_buff(Game *game);

/**
 * @brief REGLA: Una bendición que aumenta la salud máxima del jugador
 * @author MAR
 * * @param game Puntero a la estructura del juego
 */
void rule_vitality_buff(Game *game);

/**
 * @brief REGLA: Una maldición que reduce el daño del jugador
 * @author MAR
 * * @param game Puntero a la estructura del juego
 */
void rule_strength_debuff(Game *game);

/**
 * @brief REGLA: Una maldición que reduce la salud máxima del jugador
 * @author MAR
 * * @param game Puntero a la estructura del juego
 */
void vitality_debuff(Game *game);

#endif /* GAME_RULES_H */