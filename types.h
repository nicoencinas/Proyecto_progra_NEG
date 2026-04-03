/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
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
#define MAX_PLAYERS 1000
#define MESSAGE_SIZE 256

typedef long Id;

typedef enum { FALSE, TRUE } Bool;

typedef enum { ERROR, OK } Status;

typedef enum { N, S, E, W, NO_DIR } Direction;

#define WITH_PLAYER 10000


#endif
