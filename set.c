#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "types.h"

struct _Set {
    Id ids[MAX_IDS]; 
    int n_ids;
};

Set *set_create() {
    Set *new_set = NULL;
    int i;

    new_set = (Set *)malloc(sizeof(struct _Set));
    if (new_set == NULL) return NULL;
    
    new_set->n_ids = 0;
    for (i = 0; i < MAX_IDS; i++) {
        new_set->ids[i] = NO_ID;
    }

    return new_set;
}

Status set_destroy(Set *set) {
    if (!set) return ERROR; 
    free(set);
    return OK;
}

Status set_add(Set *set, Id id) {

    if (!set || id == NO_ID || set->n_ids >= MAX_IDS) {
        return ERROR;
    }

    
    if (set_find(set, id) == TRUE) {
        return ERROR;
    }


    set->ids[set->n_ids] = id;
    set->n_ids++;

    return OK;
}

Status set_del(Set *set, Id id) {
    int i, found_at = -1;

    if (!set || id == NO_ID || set->n_ids == 0) return ERROR;

    for (i = 0; i < set->n_ids; i++) {
        if (set->ids[i] == id) {
            found_at = i;
            break;
        }
    }

    if (found_at == -1) return ERROR;

    for (i = found_at; i < set->n_ids - 1; i++) {
        set->ids[i] = set->ids[i + 1];
    }

    set->ids[set->n_ids - 1] = NO_ID;
    set->n_ids--;

    return OK;
}

Bool set_find(Set *set, Id id) {
    int i;
    if (!set || id == NO_ID) return FALSE;

    for (i = 0; i < set->n_ids; i++) {
        if (set->ids[i] == id) return TRUE;
    }
    return FALSE;
}

void set_print(Set *set) {
    int i;
    if (!set) return;

    fprintf(stdout, "--> Set (n_ids: %d): ", set->n_ids);
    for (i = 0; i < set->n_ids; i++) {
       
        fprintf(stdout, "%ld ", (long int)set->ids[i]);
    }
    fprintf(stdout, "\n");
}