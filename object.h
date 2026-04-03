/**
 * @brief Define la interfaz para el módulo de objetos
 *
 * @file object.h
 * @author MAR
 * @version 2.0
 * @date 16-03-2026
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
 * @author MAR
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
 * @brief Imprime la información del objeto por la salida estándar (stdout)
 * @author MAR
 * @param object Puntero al objeto
 * @return OK o ERROR
 */
Status object_print(Object* object);

/**
 * @brief Setea la descripcion de un objeto
 * @author MAR
 * @param object Puntero al objeto
 * @return Cadena con el nombre del objeto
 */
Status object_set_desc(Object* obj, char* description);
/**
 * @brief Obtiene la descripcion de un objeto
 * @author MAR
 * @param object Puntero al objeto
 * @return Cadena con el nombre del objeto
 */
char *object_get_desc(Object* obj);

#endif