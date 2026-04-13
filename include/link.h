/**
 * @brief Define la interfaz del módulo de espacios
 *
 * @file link.h
 * @author JOEL y NICO
 * @version 1.0
 * @date 23-03-2026
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef struct _Link Link;

/**
 * @brief Crea un nuevo espacio, reservando memoria e inicializando sus miembros
 * @author JOEL
 *
 * @param id El número de identificación para el nuevo espacio
 * @return Un nuevo espacio inicializado, o NULL en caso de error
 */
Link* link_create(Id id);

/**
 * @brief Destruye un espacio, liberando la memoria reservada
 * @author JOEL
 *
 * @param space Puntero al espacio que debe ser destruido
 * @return OK si todo va bien o ERROR si hubo algún problema
 */
Status link_destroy(Link* link);

/**
 * @brief Obtiene el id de el enlace
 * @author JOEL
 * @param link Puntero al enlace
 * @return Id del enlace
 */
Id link_get_id(Link* link);

/**
 * @brief Obtiene el nombre de un enlace
 * @author JOEL
 * @param link Puntero al enlace
 * @return Cadena con el nombre del enlace
 */
const char* link_get_name(Link* link);

/**
 * @brief Obtiene el id de origen del enlace
 * @author JOEL
 * @param link Puntero al enlace
 * @return Id de origen del enlace
 */
Id link_get_origin(Link* link);

/**
 * @brief Obtiene el id de destino del enlace
 * @author JOEL
 * @param link Puntero al enlace
 * @return Id de destino del enlace
 */
Id link_get_destination(Link* link);

/**
 * @brief Obtiene la dirección del enlace
 * @author JOEL
 * @param link Puntero al enlace
 * @return Dirección del enlace
 */
Direction link_get_direction(Link* link);

/**
 * @brief Obtiene el id de destino del enlace
 * @author JOEL
 * @param link Puntero al enlace
 * @return TRUE si el espacio está abierto, FALSE si el espacio está cerrado
 */
Bool link_get_open(Link* link);

/**
 * @brief Establece el nombre de un enlace
 * @author NICO
 * @param link Puntero al enlace
 * @param name Cadena con el nuevo nombre
 * @return OK o ERROR
 */
Status link_set_name(Link* link, char *name);

/**
 * @brief Establece el id de origen de un enlace
 * @author NICO
 * @param link Puntero al enlace
 * @param id Id del nuevo origen
 * @return OK o ERROR
 */
Status link_set_origin(Link* link, Id id);

/**
 * @brief Establece el id de destino de un enlace
 * @author NICO
 * @param link Puntero al enlace
 * @param id Id del nuevo destino
 * @return OK o ERROR
 */
Status link_set_destination(Link* link, Id id);

/**
 * @brief Establece la dirección de un enlace
 * @author NICO
 * @param link Puntero al enlace
 * @param direction Direction de la nueva dirección
 * @return OK o ERROR
 */
Status link_set_direction(Link* link, Direction direction);

/**
 * @brief Establece el estado de un enlace (abierto o cerrado)
 * @author NICO
 * @param link Puntero al enlace
 * @param bool Estado nuevo del enlace
 * @return OK o ERROR
 */
Status link_set_open(Link* link, Bool bool);

/**
 * @brief Enseña por pantalla todos los datos del TAD Link para su depuración
 * @author NICO
 * 
 * @param link Puntero al TAD Link
 * @return OK o ERROR (dependiendo de si ha habido algún fallo)
 */
Status link_print(Link *link);

#endif