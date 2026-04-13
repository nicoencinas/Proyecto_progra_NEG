/**
 * @brief Define la interfaz para las acciones del juego
 *
 * @file game_actions.h
 * @author M.C. y M.A.
 * @version 1.0
 * @date 16-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "game.h"
#include "command.h"

/**
 * @brief Actualiza el estado del juego ejecutando una acción determinada por un comando
 * @author M.C. y M.A.
 *
 * Esta función procesa el código del comando recibido y delega la ejecución en la 
 * función específica correspondiente (take, drop, next, back, etc.).
 * * @param game puntero a la estructura del juego que se debe actualizar
 * @param cmd puntero al comando que contiene la orden del usuario
 * @return OK si la acción se ejecutó correctamente, ERROR si los parámetros son nulos
 */
Status game_actions_update(Game *game, Command *cmd);

/**
 * @brief Permite al jugador recoger un objeto de la sala actual
 * @author MAR
 * * Busca el objeto por nombre en la sala actual; si lo encuentra, lo elimina del 
 * espacio y lo añade al inventario del jugador.
 * @param game Puntero a la estructura del juego
 */
Status game_actions_take(Game *game);

/**
 * @brief Permite al jugador soltar un objeto en la sala actual
 * @author MAR
 * * Busca el objeto por nombre en el inventario del jugador; si lo encuentra, lo 
 * elimina del jugador y lo añade al espacio actual.
 * @param game Puntero a la estructura del juego
 */
Status game_actions_drop(Game *game);

/**
 * @brief Gestiona la comunicación con personajes amistosos
 * @author MAT
 * * Si hay un personaje amistoso en la sala, obtiene su mensaje y lo guarda en 
 * el sistema de feedback del juego para ser mostrado.
 * @param game Puntero a la estructura del juego
 */
Status game_actions_chat(Game *game);

/**
 * @brief Gestiona el combate entre el jugador y un enemigo
 * @author MAT
 * * Implementa una lógica de azar para determinar si el jugador o el enemigo 
 * pierden puntos de salud durante el enfrentamiento.
 * @param game Puntero a la estructura del juego
 */
Status game_actions_attack(Game *game);

/**
 * @brief Ejecuta la acción de inspeccionar un objeto para ver su descripción
 * @author MAR
 * * Busca un objeto en la sala o el inventario y muestra su descripción detallada 
 * en el área de mensajes del juego.
 * @param game Puntero a la estructura del juego
 */
Status game_actions_inspect(Game *game);

/**
 * @brief Se mueve havia una direccion recibida como argumento
 * @author MAR NIC JOEL
 * * Busca un objeto en la sala o el inventario y muestra su descripción detallada 
 * en el área de mensajes del juego.
 * @param game Puntero a la estructura del juego
 */
Status game_actions_move(Game *game);

#endif