/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 */

#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGHT 300

char *cmd_to_str[N_CMD][N_CMDT] =
    {
        {"", "No command"},
        {"", "Unknown"},
        {"e", "Exit"},
        {"t", "Take"},
        {"d", "Drop"},
        {"a", "Attack"},
        {"c", "Chat"},
        {"i", "Inspect"},
        {"m", "Move"}
      
    };

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
struct _Command
{
  CommandCode code;     /*!< Code of the command */
  char arg[CMD_LENGHT]; /*!< Argument of the command (e.g., object name) */
};

Command *command_create()
{
  Command *newCommand = NULL;

  newCommand = (Command *)calloc(1, sizeof(struct _Command));
  if (newCommand == NULL)
  {
    return NULL;
  }

  newCommand->code = NO_CMD;
  newCommand->arg[0] = '\0';

  return newCommand;
}

Status command_destroy(Command *command)
{
  if (!command)
  {
    return ERROR;
  }

  free(command);
  return OK;
}

Status command_set_code(Command *command, CommandCode code)
{
  if (!command)
  {
    return ERROR;
  }
  command->code = code;
  return OK;
}

CommandCode command_get_code(Command *command)
{
  if (!command)
  {
    return NO_CMD;
  }
  return command->code;
}

const char *command_get_arg(Command *command)
{
  if (!command)
  {
    return NULL;
  }
  return command->arg;
}

Status command_get_user_input(Command *command)
{
  char input[CMD_LENGHT] = "", *token = NULL;
  int i;
  CommandCode cmd;

  if (!command)
    return ERROR;

  command->arg[0] = '\0';

  if (fgets(input, CMD_LENGHT, stdin))
  {
    token = strtok(input, " \n\r");
    if (!token)
    {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;
    for (i = 2; i < N_CMD && cmd == UNKNOWN; i++)
    {

      if (cmd_to_str[i][CMDS] && !strcasecmp(token, cmd_to_str[i][CMDS]))
      {
        cmd = i + NO_CMD;
      }
      else if (cmd_to_str[i][CMDL] && !strcasecmp(token, cmd_to_str[i][CMDL]))
      {
        cmd = i + NO_CMD;
      }
    }

    command_set_code(command, cmd);

    if (cmd != UNKNOWN)
    {
      token = strtok(NULL, " \n\r");
      if (token != NULL)
      {
        strncpy(command->arg, token, CMD_LENGHT - 1);
      }
    }
    return OK;
  }
  return ERROR;
}