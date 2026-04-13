/**
 * @brief Define la interfaz para las acciones del juego
 *
 * @file game_actions.h
 * @author M.C. y M.A.
 * @version 1.0
 * @date 13-04-2026
 * @copyright GNU Public License
 */


#ifndef SET_H
#define SET_H

#include "types.h" 

typedef struct _Set Set;

/**
 * @brief Esta función crea un nuevo Set, reservando memoria e inicializando sus miembros
 * @author M.C.
 *
 * @return Un nuevo Set, inicializado
 */
Set *set_create();

/**
 * @brief Esta función destruye un Set, liberando toda la memoria reservada
 * @author M.A.
 *
 * @param set puntero al conjunto que debe ser destruido
 * @return OK (si todo va bien) o ERROR (si hay algún problema)
 */
Status set_destroy(Set *set);

/**
 * @brief Esta función añade un nuevo id al Set
 * @author M.C.
 *
 * @param set puntero al conjunto donde se añadirá el id
 * @param id el id que se va a añadir
 * @return OK (si todo va bien) o ERROR (si hay algún problema)
 */
Status set_add(Set *set, Id id);

/**
 * @brief Esta función imprime toda la información del Set
 * @author M.A.
 *
 * @param set puntero al conjunto
 * @return 
 */
void set_print(Set *set);

/**
 * @brief Esta función comprueba si un id existe en el Set
 * @author M.C.
 *
 * @param set puntero al conjunto
 * @param id el id a buscar
 * @return TRUE (si el id existe en el conjunto) o FALSE (si no existe)
 */
Bool set_find(Set *set, Id id);

/**
 * @brief Esta función elimina un id del Set, si existe
 * @author M.A.
 *
 * @param set puntero al conjunto del que se eliminará el id
 * @param id el id que se va a eliminar
 * @return OK (si todo va bien) o ERROR (si hay algún problema)
 */
Status set_del(Set *set, Id id);

#endif