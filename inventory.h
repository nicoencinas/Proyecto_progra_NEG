#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "set.h"
#include "types.h"

typedef struct _Inventory Inventory;

Inventory *inventory_create();

Status inventory_destroy(Inventory *i);

Status inventory_add(Inventory *i, Id id);
Status inventory_del(Inventory *i, Id id);

Bool inventory_find(Inventory *i, Id id);
Status inventory_print(Inventory *i);
Set *inventory_get_inventory(Inventory *i);