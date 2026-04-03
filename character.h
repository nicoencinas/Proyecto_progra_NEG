/**
 * @brief Define la interfaz para el módulo de personajes
 *
 * @file character.h
 * @author MAT
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

/**
 * @brief Estructura que almacena la información de un personaje
 */
typedef struct _Character Character;

/**
 * @brief Crea un nuevo personaje reservando memoria e inicializando sus campos
 * @author MAT
 * @param id Identificador único para el nuevo personaje
 * @return Puntero al nuevo personaje o NULL en caso de error
 */
Character* character_create(Id id);

/**
 * @brief Destruye un personaje y libera la memoria asociada
 * @author MAT
 * @param character Puntero al personaje a destruir
 * @return OK si se libera con éxito, ERROR en caso contrario
 */
Status character_destroy(Character* character);

/**
 * @brief Obtiene el identificador de un personaje
 * @author MAT
 * @param character Puntero al personaje
 * @return El ID del personaje o NO_ID en caso de error
 */
Id character_get_id(Character* character);

/**
 * @brief Obtiene el nombre de un personaje
 * @author MAT
 * @param character Puntero al personaje
 * @return Cadena con el nombre del personaje
 */
const char* character_get_name(Character* character);

/**
 * @brief Obtiene la descripción gráfica (icono ASCII) del personaje
 * @author MAT
 * @param character Puntero al personaje
 * @return Cadena con la representación gráfica del personaje
 */
const char* character_get_gdesc(Character* character);

/**
 * @brief Obtiene la localización actual del personaje
 * @author MAT
 * @param character Puntero al personaje
 * @return El ID del espacio donde se encuentra el personaje
 */
Id character_get_location(Character* character);

/**
 * @brief Obtiene los puntos de salud actuales del personaje
 * @author MAT
 * @param character Puntero al personaje
 * @return Entero con los puntos de salud
 */
int character_get_health(Character* character);

/**
 * @brief Comprueba si el personaje es amistoso u hostil
 * @author MAT
 * @param character Puntero al personaje
 * @return TRUE si es amistoso (para chat), FALSE si es hostil (para ataque)
 */
Bool character_get_friendly(Character* character);

/**
 * @brief Obtiene el mensaje que el personaje dice al chatear
 * @author MAT
 * @param character Puntero al personaje
 * @return Cadena con el mensaje del personaje
 */
const char* character_get_message(Character* character);

/**
 * @brief Establece el nombre de un personaje
 * @author MAT
 * @param character Puntero al personaje
 * @param name Cadena con el nuevo nombre
 * @return OK si se realiza con éxito, ERROR en caso contrario
 */
Status character_set_name(Character* character, char* name);

/**
 * @brief Establece la descripción gráfica del personaje
 * @author MAT
 * @param character Puntero al personaje
 * @param gdesc Cadena con la nueva descripción gráfica
 * @return OK o ERROR
 */
Status character_set_gdesc(Character* character, char* gdesc);

/**
 * @brief Establece la localización de un personaje
 * @author MAT
 * @param character Puntero al personaje
 * @param id ID del nuevo espacio para el personaje
 * @return OK o ERROR
 */
Status character_set_location(Character* character, Id id);

/**
 * @brief Establece los puntos de salud del personaje
 * @author MAT
 * @param character Puntero al personaje
 * @param health Nuevos puntos de salud
 * @return OK o ERROR
 */
Status character_set_health(Character* character, int health);

/**
 * @brief Establece si el personaje es amistoso o no
 * @author MAT
 * @param character Puntero al personaje
 * @param friendly Booleano (TRUE para amistoso, FALSE para hostil)
 * @return OK o ERROR
 */
Status character_set_friendly(Character* character, Bool friendly);

/**
 * @brief Establece el mensaje de chat del personaje
 * @author MAT
 * @param character Puntero al personaje
 * @param message Cadena con el mensaje a guardar
 * @return OK o ERROR
 */
Status character_set_message(Character* character, char* message);

/**
 * @brief Imprime la información del personaje por la salida estándar
 * @author MAT
 * @param character Puntero al personaje
 * @return OK o ERROR
 */
Status character_print(Character* character);

#endif