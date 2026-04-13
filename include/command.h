/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores, M.A y M.C
 * @version 0
 * @date 10-02-2026
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 18


typedef enum { CMDS, CMDL } CommandType;

typedef enum { NO_CMD = -1, UNKNOWN, EXIT, TAKE, DROP, ATTACK, CHAT, INSPECT, MOVE} CommandCode;

typedef struct _Command Command;

/**
 * @brief Crea un nuevo comando
 * @author MAT y MAR
 * @return Comando inicializado o NULL
 */
Command* command_create();

/**
 * @brief Libera un comando
 * @author MAT y MAR
 * @param command Comando a destruir
 * @return OK o ERROR
 */
Status command_destroy(Command* command);

/**
 * @brief Asigna un código al comando
 * @author MAT y MAR
 * @param command Comando a modificar
 * @param code Nuevo código
 * @return OK o ERROR
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief Obtiene el código del comando
 * @author MAT y MAR
 * @param command Comando a consultar
 * @return CommandCode o NO_CMD
 */
CommandCode command_get_code(Command* command);

/**
 * @brief Lee y procesa la entrada de usuario (stdin)
 * @author MAR
 * @param command Comando donde guardar la entrada
 * @return OK o ERROR
 */
Status command_get_user_input(Command* command);

/**
 * @brief Obtiene el argumento del comando
 * @author MAR
 * @param command Comando a consultar
 * @return String del argumento o NULL
 */
const char* command_get_arg(Command* command);

#endif
