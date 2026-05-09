/**
 * @brief Define la interfaz para el módulo de objetos
 *
 * @file object.h
 * @author MAR Y JOEL
 * @version 3.0
 * @date 20-04-2026
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/**
 * @brief Estructura que almacena la información de un objeto
 */
typedef struct _Object Object;

/**
 * @brief Crea un nuevo objeto reservando memoria e inicializando sus campos
 * @author JOEL
 * @param id Identificador único para el nuevo objeto
 * @return Puntero al nuevo objeto o NULL en caso de error
 */
Object* object_create(Id id);

/**
 * @brief Destruye un objeto y libera la memoria asociada
 * @author MAR
 * @param object Puntero al objeto a destruir
 * @return OK si se libera con éxito, ERROR en caso contrario
 */
Status object_destroy(Object* object);

/**
 * @brief Obtiene el identificador de un objeto
 * @author MAR
 * @param object Puntero al objeto
 * @return El ID del objeto o NO_ID en caso de error
 */
Id object_get_id(Object* object);

/**
 * @brief Establece el nombre de un objeto
 * @author MAR
 * @param object Puntero al objeto
 * @param name Cadena con el nuevo nombre
 * @return OK si se realiza con éxito, ERROR en caso contrario
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief Obtiene el nombre de un objeto
 * @author MAR
 * @param object Puntero al objeto
 * @return Cadena con el nombre del objeto
 */
const char* object_get_name(Object* object);

/**
 * @brief Setea la descripcion de un objeto
 * @author MAR
 * @param object Puntero al objeto
 * @param description Cadena con la nueva descripcion
 * @return OK si se realiza con éxito, ERROR en caso contrario
 */
Status object_set_desc(Object* object, char* description);

/**
 * @brief Obtiene la descripcion de un objeto
 * @author MAR
 * @param object Puntero al objeto
 * @return Cadena con la descripcion del objeto
 */
char *object_get_desc(Object* object);

/**
 * @brief Setea la salud de un objeto
 * @author JOEL
 * @param object Puntero al objeto
 * @param health Entero con la nueva salud
 * @return OK si se realiza con éxito, ERROR en caso contrario
 */
Status object_set_health(Object *object, int health);

/**
 * @brief Obtiene los puntos de salud del objeto (pueden ser positivos o negativos y afectan al jugador)
 * @author JOEL
 * @param object Puntero al objeto
 * @return Entero con los puntos de salud del objeto
 */
int object_get_health(Object *object);

/**
 * @brief Setea la movilidad de un objeto
 * @author JOEL
 * @param object Puntero al objeto
 * @param movable Booleano con la nueva movilidad
 * @return OK si se realiza con éxito, ERROR en caso contrario
 */
Status object_set_movable(Object *object, Bool movable);

/**
 * @brief Comprueba si el objeto se puede mover de su ubicación
 * @author JOEL
 * @param object Puntero al objeto
 * @return TRUE si el objeto se puede mover, FALSE en caso contrario
 */
Bool object_get_movable(Object *object);

/**
 * @brief Setea la dependencia de un objeto
 * @author JOEL
 * @param object Puntero al objeto
 * @param object_id ID del objeto del que se va a crear la nueva dependencia
 * @return OK si se realiza con éxito, ERROR en caso contrario
 */
Status object_set_dependency(Object *object, Id object_id);

/**
 * @brief Obtiene el ID del objeto del que depende nuestro objecto
 * @author JOEL
 * @param object Puntero al objeto
 * @return El ID del objeto del que depende nuestro objecto en caso de éxito, NO_ID en caso contrario
 */
Id object_get_dependency(Object *object);

/**
 * @brief Setea la apertura de un objeto
 * @author JOEL
 * @param object Puntero al objeto
 * @param id ID del nuevo enlace que el objeto va a poder abrir
 * @return OK si se realiza con éxito, ERROR en caso contrario
 */
Status object_set_open(Object *object, Id id);

/**
 * @brief Obtiene el ID del enlace que puede abrir nuestro objecto
 * @author JOEL
 * @param object Puntero al objeto
 * @return El ID el ID del enlace que puede abrir nuestro objecto en caso de éxito, NO_ID en caso contrario
 */
Id object_get_open(Object *object);

/**
 * @brief Imprime la información del objeto por la salida estándar (stdout)
 * @author MAR
 * @param object Puntero al objeto
 * @return OK o ERROR
 */
Status object_print(Object* object);

#endif