/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores, M.A, M.C
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "player.h"
#include "object.h"
#include "character.h"
#include "link.h"

#define MAX_SPACES 100

typedef struct _InterfaceData InterfaceData;
typedef struct _Game Game;

/**
 * @brief Crea una nueva interfaz de datos, reservando memoria e inicializando sus miembros
 * @author NICO
 * 
 * @return Puntero al nuevo personaje o NULL en caso de error
 */
InterfaceData *data_create();

/**
 * @brief Destruye una interfaz de datos y libera la memoria asociada
 * @author JOEL
 * @param data Puntero a la interfaz de datos a destruir
 * @return OK si se libera con éxito, ERROR en caso contrario
 */
Status data_destroy(InterfaceData *data);

/**
 * @brief Obtiene el último command
 * @author MAR
 * @param data Puntero a data
 * @return Número de personajes
 */
Command *data_get_last_command(InterfaceData *data);

/**
 * @brief Obtiene el msg
 * @author MAR
 * @param data Puntero a data
 * @return Número de personajes
 */
char *data_get_message(InterfaceData *data);

/**
 * @brief  Establece la cadena de texto para el sistema de chat/mensajes
 * @author MAR
 * @param data Puntero a data
 * @param m     mensaje
 * @return Número de personajes
 */
Status data_set_message(InterfaceData *data, char *m);

/**
 * @brief  Establece el último command
 * @author MAR
 * @param data Puntero a data
 * @param c Puntero command
 * @return Número de personajes
 */
Status data_set_last_command(InterfaceData *data, Command *c);



Game* game_create();

Status game_destroy(Game *game);

Space *game_get_space(Game *game, Id id);

Id game_get_player_location(Game *game);

Status game_set_player_location(Game *game, Id id);

Command* game_get_last_command(Game *game);

Status game_set_last_command(Game *game, Command *command);

Bool game_get_finished(Game *game);

Status game_set_finished(Game *game, Bool finished);

void game_print(Game *game);

/**
 * @brief Carga los espacios desde un archivo de datos
 * @author MAR
 * @param game Puntero al juego
 * @param filename Nombre del archivo de datos
 * @return OK si se carga con éxito, ERROR en caso contrario
 */
Status game_load_spaces(Game *game, char *filename);

/**
 * @brief Añade un nuevo espacio al juego
 * @author MAR
 * @param game Puntero al juego
 * @param space Puntero al espacio a añadir
 * @return OK o ERROR
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief Obtiene el ID de un espacio en una posición determinada del array
 * @author MAR
 * @param game Puntero al juego
 * @param position Índice del espacio en el array
 * @return El ID del espacio o NO_ID si hay error
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief Obtiene la localización de un objeto específico
 * @author MAR
 * @param game Puntero al juego
 * @param object_id ID del objeto
 * @return El ID del espacio donde está el objeto, WITH_PLAYER si lo lleva el jugador o NO_ID
 */
Id game_get_object_location(Game *game, Id object_id);

/**
 * @brief Cambia la localización de un objeto
 * @author MAR
 * @param game Puntero al juego
 * @param space_id ID del nuevo espacio (o WITH_PLAYER)
 * @param object_id ID del objeto a mover
 * @return OK o ERROR
 */
Status game_set_object_location(Game *game, Id space_id, Id object_id);

/**
 * @brief Obtiene los puntos de vida actuales del jugador
 * @author MAT
 * @param game Puntero al juego
 * @return Puntos de vida del jugador
 */
int game_get_player_HP(Game *game);

/**
 * @brief Añade un objeto al catálogo global del juego
 * @author MAR
 * @param game Puntero al juego
 * @param object Puntero al objeto a añadir
 * @return OK o ERROR
 */
Status game_add_object(Game *game, Object *object);

/**
 * @brief Obtiene el puntero a la estructura del jugador
 * @author Profesores PPROG
 * @param game Puntero al juego
 * @return Puntero al jugador
 */
Player *game_get_player(Game *game);

/**
 * @brief Busca un objeto en el catálogo global mediante su ID
 * @author MAR
 * @param game Puntero al juego
 * @param id ID del objeto a buscar
 * @return Puntero al objeto encontrado o NULL si no existe
 */
Object* game_get_object_from_id(Game *game, Id id);

/**
 * @brief Añade un personaje al juego
 * @author MAT
 * @param game Puntero al juego
 * @param character Puntero al personaje a añadir
 * @return OK o ERROR
 */
Status game_add_character(Game* game, Character* character);

/**
 * @brief Obtiene un personaje situado en una posición específica del array
 * @author MAT
 * @param game Puntero al juego
 * @param position Índice del personaje
 * @return Puntero al personaje o NULL en caso de error
 */
Character* game_get_character_at(Game* game, int position);

/**
 * @brief Obtiene el número total de personajes en el juego
 * @author MAT
 * @param game Puntero al juego
 * @return Número de personajes
 */
int game_get_n_characters(Game *game);

/**
 * @brief Obtiene la cadena de texto del último mensaje de chat
 * @author MAT
 * @param game Puntero al juego
 * @return Puntero a la cadena de texto (s) almacenada en el juego
 */
char *game_get_s(Game *game);

/**
 * @brief Establece la cadena de texto para el sistema de chat/mensajes
 * @author MAT
 * @param game Puntero al juego
 * @param s Cadena de texto con el mensaje
 * @return OK o ERROR
 */
Status game_set_s(Game *game, char *s);

/**
 * @brief Obtiene el identificador del espacio de destino
 * @author JOEL
 * @param game Puntero al juego
 * @param space_id Identificador del espacio actual
 * @param direction Direccion del enlace
 * @return El identificador del espacio de destino
 */
Id game_get_connection(Game *game, Id space_id, Direction direction);

/**
 * @brief Determina si la conexion entre dos espacios es posible o si no
 * @author NICO
 * @param game Puntero al juego
 * @param space_id Identificador del espacio actual
 * @param direction Direccion del enlace
 * @return Si la conexion es abierta o cerrada
 */
Bool game_connection_is_open(Game *game, Id actual, Direction direction);

/**
 * @brief Añade un enlace al juego
 * @author JOEL
 * @param game Puntero al juego
 * @param link Puntero al enlace a añadir
 * @return OK o ERROR
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief Obtiene el número total de objetos en el juego
 * @author MAR
 * @param game Puntero al juego
 * @return Número de personajes
 */
int game_get_n_obj(Game *game);

/**
 * @brief  devuelve el turno actual
 * @author MAR
 * @param game Puntero a game
 * @return turno actual
 */
int game_get_turn(Game *game);
/**
 * @brief  incrementa el turno
 * @author MAR
 * @param game Puntero a game
 * @return Status
 */
Status game_next_turn(Game *game);
int game_get_n_players(Game *game);
Status game_add_player(Game *game, Player *player);
#endif