#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "object.h"

struct _Object
{
  Id id;
  char name[WORD_SIZE + 1];
  char desc[40];
  int health;
  Bool movable;
  Id dependency;
  Id open;
};

Object *object_create(Id id)
{
  Object *newObject = NULL;

  if (id == NO_ID)
    return NULL;

  newObject = (Object *)calloc(1, sizeof(Object));
  if (newObject == NULL)
  {
    return NULL;
  }

  newObject->id = id;
  newObject->name[0] = '\0';
  newObject->health = 0;
  newObject->movable = FALSE;
  newObject->dependency = NO_ID;
  newObject->open = NO_ID;

  return newObject;
}

Status object_destroy(Object *object)
{
  if (!object)
  {
    return ERROR;
  }

  free(object);

  return OK;
}

Id object_get_id(Object *object)
{
  if (!object)
  {
    return NO_ID;
  }

  return object->id;
}

Status object_set_name(Object *object, char *name)
{
  if (!object || !name)
  {
    return ERROR;
  }

  if (!strcpy(object->name, name))
  {
    return ERROR;
  }

  return OK;
}

const char *object_get_name(Object *object)
{
  if (!object)
  {
    return NULL;
  }

  return object->name;
}

Status object_set_desc(Object *object, char *desc)
{
  if (!object || !desc)
  {
    return ERROR;
  }

  strncpy(object->desc, desc, 40);

  return OK;
}

char *object_get_desc(Object *object)
{
  if (object == NULL)
  {
    return NULL;
  }

  return object->desc;
}

Status object_set_health(Object *object, int health)
{
  if (!object)
  {
    return ERROR;
  }

  object->health = health;

  return OK;
}

int object_get_health(Object *object)
{
  if (!object)
  {
    return OBJECT_NULL;
  }

  return object->health;
}

Status object_set_movable(Object *object, Bool movable)
{
  if (!object)
  {
    return ERROR;
  }

  object->movable = movable;

  return OK;
}

Bool object_get_movable(Object *object)
{
  if (!object)
  {
    return FALSE;
  }

  return object->movable;
}

Status object_set_dependency(Object *object, Id object_id)
{
  if (!object || object_id == NO_ID)
  {
    return ERROR;
  }

  object->dependency = object_id;

  return OK;
}

Id object_get_dependency(Object *object)
{
  if (!object)
  {
    return NO_ID;
  }

  return object->dependency;
}

Status object_set_open(Object *object, Id id)
{
  if (!object || id == NO_ID)
  {
    return ERROR;
  }

  object->open = id;

  return OK;
}

Id object_get_open(Object *object)
{
  if (!object)
  {
    return NO_ID;
  }

  return object->open;
}

Status object_print(Object *object)
{
  Id idaux = NO_ID;
  Status stataux = ERROR;
  int intaux = -1;
  Bool boolaux = FALSE;

  if (!object)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  intaux = object_get_health(object);
  if (intaux == -1)
  {
    fprintf(stdout, "No health found\n");
  }
  else
  {
    fprintf(stdout, "---> Health: %d.\n", intaux);
  }

  idaux = object_get_dependency(object);
  if (idaux == NO_ID)
  {
    fprintf(stdout, "No object id found\n");
  }
  else
  {
    fprintf(stdout, "---> Dependency: %ld.\n", idaux);
  }

  boolaux = object_get_movable(object);
  if (boolaux == FALSE)
  {
    fprintf(stdout, "Movable : False");
  }
  else
  {
    fprintf(stdout, "--> Movable: True");
  }

  stataux = object_get_open(object);
  if (stataux == NO_ID)
  {
    fprintf(stdout, "Cannot open anything\n");
  }
  else
  {
    fprintf(stdout, "---> Open: %d.\n", stataux);
  }

  return OK;
}
