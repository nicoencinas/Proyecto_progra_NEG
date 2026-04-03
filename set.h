/**
 * @brief Define la interfaz para las acciones del juego
 *
 * @file game_actions.h
 * @author M.C. y M.A.
 * @version 1.0
 * @date 16-02-2026
 * @copyright GNU Public License
 */


#ifndef SET_H
#define SET_H

#include "types.h" 

typedef struct _Set Set;


Set *set_create();
Status set_destroy(Set *set);
Status set_add(Set *set, Id id);
void set_print(Set *set);
Bool set_find(Set *set, Id id);
Status set_del(Set *set, Id id);
#endif