#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBJS 100

typedef int Id;

typedef struct {
    Id ids[MAX_OBJS];
    int count;
} Set;

typedef struct {
    Set set;
} Inventory;

Inventory* inventory_create() {
    Inventory* inv = (Inventory*)malloc(sizeof(Inventory));
    inv->set.count = 0;
    return inv;
}

void inventory_destroy(Inventory *i) {
    free(i);
}

int inventory_add(Inventory *i, Id id) {
    if (i->set.count >= MAX_OBJS) return -1;  // Inventory is full
    i->set.ids[i->set.count++] = id;
    return 0;  // Success
}

int inventory_del(Inventory *i, Id id) {
    for (int j = 0; j < i->set.count; j++) {
        if (i->set.ids[j] == id) {
            i->set.ids[j] = i->set.ids[i->set.count - 1];
            i->set.count--;
            return 0;  // Success
        }
    }
    return -1;  // Not found
}

Id inventory_find(Inventory *i, Id id) {
    for (int j = 0; j < i->set.count; j++) {
        if (i->set.ids[j] == id) return id;
    }
    return -1;  // Not found
}

void inventory_print(Inventory *i) {
    for (int j = 0; j < i->set.count; j++) {
        printf("ID: %d\n", i->set.ids[j]);
    }
}

Set inventory_get_inventory(Inventory *i) {
    return i->set;
}