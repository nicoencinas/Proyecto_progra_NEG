#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "object.h"

struct _Object {
  Id id;                    
  char name[WORD_SIZE + 1]; 
  char desc[40];
};

Object* object_create(Id id) {
  Object* newObject = NULL;

  if (id == NO_ID) return NULL;

  newObject = (Object*)calloc(1, sizeof(Object));
  if (newObject == NULL) {
    return NULL;
  }

  newObject->id = id;
  newObject->name[0] = '\0';

  return newObject;
}


Status object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  return OK;
}

Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

Status object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

Status object_print(Object* object) {

  
  if (!object) {
    return ERROR;
  }

  
  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}
Status object_set_desc(Object* obj, char* desc) {
  
  if (!obj || !desc) {
    return ERROR;
  }
  strncpy(obj->desc, desc, 40);
  return OK;
}
char *object_get_desc(Object* obj)
{
  if (obj==NULL)
  {
    return NULL;
  }
  return obj->desc;
}