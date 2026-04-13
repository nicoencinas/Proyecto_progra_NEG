/**
 * @brief Define la interfaz del módulo de inventario
 *
 * @file inventory.h
 * @author Profesores MAT Y MAR
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

typedef struct _Inventory Inventory;

/**
 * @brief Crea un nuevo inventario, reservando memoria e inicializándolo
 * @author MAtT y MAR
 *
 * @return Un nuevo inventario inicializado, o NULL en caso de error
 */
Inventory *inventory_create();

/**
 * @brief Destruye un inventario, liberando la memoria reservada y sus recursos
 * @author MAT Y MAR
 * @param i Puntero al inventario a destruir
 * @return OK si se libera con éxito, ERROR en caso contrario
 */
Status inventory_destroy(Inventory *i);

/**
 * @brief Añade un objeto al inventario
 * @author MAR y MAT
 * @param i Puntero al inventario
 * @param id ID del objeto que se desea añadir
 * @return OK si se añade con éxito o ERROR si no (ej. si el inventario está lleno)
 */
Status inventory_add(Inventory *i, Id id);

/**
 * @brief Elimina un objeto del inventario
 * @author MAT y MAR
 * @param i Puntero al inventario
 * @param id ID del objeto que se desea eliminar
 * @return OK si se elimina con éxito o ERROR en caso contrario
 */
Status inventory_del(Inventory *i, Id id);

/**
 * @brief Comprueba si un objeto específico está presente en el inventario
 * @author MAT y MAR
 * @param i Puntero al inventario
 * @param id ID del objeto a buscar
 * @return TRUE si el objeto está en el inventario, FALSE en caso contrario
 */
Bool inventory_find(Inventory *i, Id id);

/**
 * @brief Imprime la información del inventario por pantalla (útil para depuración)
 * @author MAT y MAR
 * @param i Puntero al inventario
 * @return OK si se imprime correctamente, ERROR en caso contrario
 */
Status inventory_print(Inventory *i);

/**
 * @brief Obtiene el conjunto (Set) que contiene los objetos del inventario
 * @author MAT y MAR
 * @param i Puntero al inventario
 * @return Puntero al objeto Set interno del inventario
 */
Set *inventory_get_inventory(Inventory *i);

#endif