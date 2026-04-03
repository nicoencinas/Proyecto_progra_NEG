#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "set.h"
#include "types.h"
#include "inventory.h"

struct _Inventory
{

    int max_obj;
    Set *inventory;
    
};


Inventory* inventory_create(int max_objs) {
    Inventory *i = NULL;

   
    i = (Inventory *) malloc(sizeof(struct _Inventory));
    
    if (i == NULL) {
        return NULL;
    }
    i->max_obj = max_objs;
    i->inventory = set_create();

    if (i->inventory == NULL) {
        free(i);
        return NULL;
    }

    return i;
}
Status inventory_destroy(Inventory *i)
{
    if (!i)
        return ERROR;
    free(i);
    return OK;
}

Status inventory_add(Inventory *i, Id id)
{
    if (!i)
        return ERROR;
    return set_add(i->inventory, id);
}

Status inventory_del(Inventory *i, Id id)
{
    if (!i)
        return ERROR;
    return set_del(i->inventory, id);
}
Bool inventory_find(Inventory *i, Id id)
{
    if (!i || id == NO_ID)
        return FALSE;

    return set_find(i->inventory, id);
}

Status inventory_print(Inventory *i)
{
    if (!i)
        return ERROR;
    fprintf(stdout, "(Max Objects: %d))\n", i->max_obj);
    set_print(i->inventory);
    return OK;
}
Set *inventory_get_inventory(Inventory *i)
{
    if (!i)
    {
        return NULL;
    }
    return i->inventory;
}