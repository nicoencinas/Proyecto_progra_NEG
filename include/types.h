/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 1
 * @date 20-04-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define MAX_CHARACTERS 1000
#define MAX_OBJECTS 1000
#define MAX_LINKS 1000
#define MAX_IDS 1000
#define NO_ID -1
#define MAX_PLAYERS 8
#define MESSAGE_SIZE 256

typedef long Id;

typedef enum { FALSE, TRUE } Bool;

typedef enum { ERROR, OK } Status;

typedef enum { N, S, E, W, U, D, NO_DIR } Direction;

#define WITH_PLAYER 10000

#define OBJECT_NULL -10000


#endif
