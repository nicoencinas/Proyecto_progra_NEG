/**
 * @brief Define la interfaz del módulo de espacios
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

#define GDESC_LINES 5

typedef struct _Space Space;

/**
 * @brief Crea un nuevo espacio, reservando memoria e inicializando sus miembros
 * @author Profesores PPROG
 *
 * @param id El número de identificación para el nuevo espacio
 * @return Un nuevo espacio inicializado, o NULL en caso de error
 */
Space* space_create(Id id);

/**
 * @brief Destruye un espacio, liberando la memoria reservada
 * @author Profesores PPROG
 *
 * @param space Puntero al espacio que debe ser destruido
 * @return OK si todo va bien o ERROR si hubo algún problema
 */
Status space_destroy(Space* space);

/**
 * @brief Obtiene el ID de un espacio
 * @author Profesores PPROG
 *
 * @param space Puntero al espacio
 * @return El ID del espacio
 */
Id space_get_id(Space* space);

/**
 * @brief Establece el nombre de un espacio
 * @author Profesores PPROG
 *
 * @param space Puntero al espacio
 * @param name Cadena con el nombre a guardar
 * @return OK si se realiza con éxito o ERROR en caso contrario
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief Obtiene el nombre de un espacio
 * @author Profesores PPROG
 *
 * @param space Puntero al espacio
 * @return Una cadena con el nombre del espacio
 */
const char* space_get_name(Space* space);

/**
 * @brief Añade un objeto al conjunto de objetos del espacio
 * @author MAR
 *
 * @param space Puntero al espacio
 * @param id ID del objeto a añadir
 * @return OK si se añade con éxito o ERROR si no
 */
Status space_add_object(Space* space, Id id);

/**
 * @brief Elimina un objeto del conjunto de objetos del espacio
 * @author MAR
 *
 * @param space Puntero al espacio
 * @param id ID del objeto a eliminar
 * @return OK si se elimina con éxito o ERROR si no
 */
Status space_remove_object(Space* space, Id id);

/**
 * @brief Obtiene el conjunto (Set) de objetos que hay en el espacio
 * @author MAR
 *
 * @param space Puntero al espacio
 * @return Puntero al objeto Set del espacio
 */
Set* space_get_objects(Space* space);

/**
 * @brief Comprueba si un objeto específico está presente en el espacio
 * @author MAR
 *
 * @param space Puntero al espacio
 * @param id ID del objeto a buscar
 * @return TRUE si el objeto está en el espacio, FALSE en caso contrario
 */
Bool space_has_object(Space* space, Id id);

/**
 * @brief Establece el identificador del personaje que está en el espacio
 * @author MAT
 *
 * @param space Puntero al espacio
 * @param id El ID del personaje
 * @return OK si se establece correctamente o ERROR en caso contrario
 */
Status space_set_character(Space* space, Id id);


/**
 * @brief Establece una línea específica de la descripción gráfica (ASCII art) del espacio
 * @author MAT
 *
 * @param space Puntero al espacio
 * @param line El índice de la línea (normalmente de 0 a 4)
 * @param str La cadena que contiene el dibujo de esa línea
 * @return OK o ERROR
 */
Status space_set_gdesc_at(Space* space, int line, char* str);

/**
 * @brief Obtiene una línea específica de la descripción gráfica del espacio
 * @author MAT
 *
 * @param space Puntero al espacio
 * @param line El índice de la línea a obtener
 * @return Puntero a la cadena de texto de la línea o NULL si hay error
 */
const char* space_get_gdesc_at(Space* space, int line);

/**
 * @brief No tiene uso aun
 */
Status Space_discovered(Space* space);

/**
 * @brief Imprime toda la información del espacio por pantalla
 * @author Profesores PPROG
 *
 * Muestra el ID, nombre, conexiones, objetos y personaje presente.
 * @param space Puntero al espacio
 * @return OK o ERROR
 */
Status space_print(Space* space);


/**
 * @brief Libera la memoria de un espacio y sus conjuntos internos (objetos y personajes) [cite: 105]
 * @author MAR [cite: 89]
 * @param space Puntero al espacio a destruir
 * @return OK si se destruye correctamente, ERROR en caso contrario
 */
Status space_destroy(Space *space);

/**
 * @brief Añade un personaje al conjunto de personajes del espacio (F5) [cite: 105, 110]
 * @author MAR 
 * @param space Puntero al espacio
 * @param id El identificador del personaje a añadir [cite: 130]
 * @return OK si se añade correctamente, ERROR en caso contrario
 */
Status space_add_character(Space *space, Id id);

/**
 * @brief Elimina un personaje del conjunto del espacio (F5) [cite: 105, 110]
 * @author MAR
 * @param space Puntero al espacio
 * @param id El identificador del personaje a eliminar [cite: 130]
 * @return OK si se elimina correctamente, ERROR en caso contrario
 */
Status space_remove_character(Space *space, Id id);

/**
 * @brief Comprueba si un personaje específico está en el espacio (F5) [cite: 151]
 * @author MAR
 * @param space Puntero al espacio
 * @param id El identificador del personaje a buscar [cite: 130]
 * @return TRUE si el personaje está presente, FALSE en caso contrario
 */
Bool space_has_character(Space *space, Id id);

/**
 * @brief Obtiene el conjunto completo de personajes del espacio (F5) [cite: 104]
 * @author MAR 
 * @param space Puntero al espacio
 * @return Puntero al Set de personajes, o NULL en caso de error
 */
Set* space_get_character(Space *space);

/**
 * @brief Establece si un espacio ha sido descubierto (F12) [cite: 149]
 * @author MAR 
 * @param space Puntero al espacio
 * @return OK si se marca como descubierto, ERROR en caso contrario [cite: 150]
 */
Status space_set_discovered(Space *space);

/**
 * @brief Comprueba si el espacio ha sido descubierto por algún jugador (F12) [cite: 149]
 * @author MAR 
 * @param space Puntero al espacio
 * @return TRUE si ha sido descubierto, FALSE en caso contrario [cite: 150]
 */
Bool space_get_discovered(Space *space);

/**
 * @brief Obtiene el objeto del juego
 * @author MAR
 * @param space Puntero al espacio
 * @return Puntero al objeto 
 */
Set *space_get_object(Space *space);

/**
 * @brief Actualiza el objeto del juego
 * @author MAR
 * @param space Puntero al espacio
 * @param id Identificador del objeto
 * @return OK o ERROR
 */
Status space_set_object(Space *space, Id id);

#endif