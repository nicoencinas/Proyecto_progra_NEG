/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 0
 * @date 24-01-2026
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include "set.h"
#include "character.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space
{
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Set *object;              /*!< Whether the space has an object or not */
  Id ch;
  char gdesc[5][MAX_CHARACTERS];
  Bool discovered;
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space *space_create(Id id)
{
  Space *newSpace = NULL;

  if (id == NO_ID)
    return NULL;

  newSpace = (Space *)calloc(1, sizeof(Space));
  if (newSpace == NULL)
  {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->object = set_create();
  newSpace->discovered = FALSE;

  return newSpace;
}

Status space_destroy(Space *space)
{
  if (!space)
  {
    return ERROR;
  }
  set_destroy(space->object);
  free(space);
  return OK;
}

Id space_get_id(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space *space, char *name)
{
  if (!space || !name)
  {
    return ERROR;
  }

  if (!strcpy(space->name, name))
  {
    return ERROR;
  }
  return OK;
}

const char *space_get_name(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return space->name;
}

Status space_set_object(Space *space, Id id)
{
  if (!space)
  {
    return ERROR;
  }
  set_add(space->object, id);
  return OK;
}

Set *space_get_object(Space *space)
{
  if (!space)
  {
    return FALSE;
  }
  return space->object;
}

Status space_print(Space *space)
{

  /* Error Control */
  if (!space)
  {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 3. Print if there is an object in the space or not */
  if (space_get_object(space))
  {
    fprintf(stdout, "---> Object in the space.\n");
    set_print(space->object);
  }
  else
  {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}

Bool space_has_object(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return FALSE;
  }

  return set_find(space->object, id);
}
Status space_add_object(Space *space, Id id)
{
  if (!space || id == NO_ID)
    return ERROR;
  return set_add(space->object, id);
}

Status space_remove_object(Space *space, Id id)
{
  if (!space || id == NO_ID)
    return ERROR;
  return set_del(space->object, id);
}

Status space_set_character(Space *space, Id id)
{
  if (!space)
  {
    return ERROR;
  }
  space->ch = id;
  return OK;
}

Id space_get_character(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->ch;
}
const char *space_get_gdesc_at(Space *space, int line)
{
  if (!space || line < 0 || line >= 5)
  {
    return NULL;
  }
  return space->gdesc[line];
}
Status space_set_gdesc_at(Space *space, int line, char *str)
{
  if (!space || !str || line < 0 || line >= 5)
  {
    return ERROR;
  }
  strncpy(space->gdesc[line], str, 11);
  space->gdesc[line][11] = '\0';
  return OK;
}

Status Space_discovered(Space *space)
{
  if (!space)
    return ERROR;
  space->discovered = TRUE;
  return OK;
}

Bool space_get_discovered(Space *space)
{
  if (!space)
    return FALSE;
  return space->discovered;
}