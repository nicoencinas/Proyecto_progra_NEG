/**
 * @brief It implements the link module
 *
 * @file link.c
 * @author JOEL y NICO
 * @version 1.0
 * @date 23-03-2026
 * @copyright GNU Public License
 */

#include "link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Link
 *
 * This struct stores all the information of a link.
 */
struct _Link
{
  Id id;                        /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];     /*!< Name of the link */
  Id origin;                    /*!< Original space */
  Id destination;               /*!< Space where we want to go */
  Direction direction;          /*!< Direction in which we want to move */
  Bool open;                    /*!< State of the link (open or closed) */
};

/** link_create allocates memory for a new link
 *  and initializes its members
 */
Link *link_create(Id id)
{
  Link *newLink = NULL;

  if (id == NO_ID) {
    return NULL;
  }

  if (!(newLink = (Link *) calloc(1, sizeof(Link)))) {
    return NULL;
  }

  newLink->id = id;
  newLink->name[0] = '\0';
  newLink->origin = NO_ID;
  newLink->destination = NO_ID;
  newLink->direction = NO_DIR;
  newLink->open = FALSE;

  return newLink;
}

Status link_destroy(Link *link)
{
  if (!link)
  {
    return ERROR;
  }
  
  free(link);

  return OK;
}

Id link_get_id(Link *link)
{
  if (!link)
  {
    return NO_ID;
  }
  
  return link->id;
}

const char *link_get_name(Link *link)
{
  if (!link)
  {
    return NULL;
  }

  return link->name;
}

Id link_get_origin(Link *link) 
{
  if (!link) 
  {
      return NO_ID;
  }

  return link->origin;
}

Id link_get_destination(Link *link) 
{
  if (!link) 
  {
    return NO_ID;
  }

  return link->destination;
}

Direction link_get_direction(Link *link) 
{
  if (!link) 
  {
    return NO_DIR;
  }

  return link->direction;
}

Bool link_get_open(Link *link)
{
  if(!link)
  {
    return FALSE;
  }

    return link->open;
}

Status link_set_name(Link *link, char *name)
{
  if (!link || !name)
  {
    return ERROR;
  }

  if (!strcpy(link->name, name))
  {
    return ERROR;
  }
  return OK;
}

Status link_set_origin(Link *link, Id id)
{
  if(!link || id==NO_ID)
  {
    return ERROR;
  }

  link->origin = id;

  return OK;
}

Status link_set_destination(Link *link, Id id) 
{
  if (!link || id == NO_ID) 
  {
    return ERROR;
  }

  link->destination = id;

  return OK;
}

Status link_set_direction(Link *link, Direction direction) 
{
  if (!link || direction == NO_DIR)
  {
    return ERROR;
  }

  link->direction = direction;

  return OK;
}

Status link_set_open(Link *link, Bool bool)
{
  if(!link || bool == NO_ID)
  {
    return ERROR;
  }

  link->open = bool;

  return OK;
}

Status link_print(Link *link)
{
  Id idaux = NO_ID;
  Direction diraux = NO_DIR;
  Bool boolaux = FALSE;

  /* Error Control */
  if (!link)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name);

  idaux = link_get_origin(link);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> Origin: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No origin.\n");
  }

  idaux = link_get_destination(link);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> Destination: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No destination.\n");
  }

  diraux = link_get_direction(link);
  if (diraux != NO_DIR) {
    fprintf(stdout, "---> Direction: %u.\n", diraux);
  } else {
    fprintf(stdout, "---> No direction.\n");
  }

  boolaux = link_get_open(link);
  if (boolaux == TRUE) {
    fprintf(stdout, "---> Open: TRUE.\n");
  } else {
    fprintf(stdout, "---> Open: FALSE.\n");
  }
  
  return OK;
}