#include "hashtable.h"

struct hashtable {
    int max;
    array_1d *arr;
};

hashtable* hashtable_empty(int max) {
    array_1d *arr = array_1d_create(0, max, NULL);

    struct hashtable *tbl = calloc(1, sizeof(*tbl));
    tbl->arr = arr;
    tbl->max = max;

    return tbl;
}
int hashtable_hash(hashtable *tbl, char *key) {
    int asc_sum = 0;
    for(int i = 0; i < strlen(key); i++) {
        asc_sum += key[i];
    }
    return tbl->max % asc_sum;
}

hashtable* hashtable_insert(hashtable* tbl, char *key) {
    int idx = hashtable_hash(tbl, key);

    if(!array_1d_has_key(tbl->arr, idx)) {
        array_1d_set_key(tbl->arr, key, idx);
    } else {
        while(array_1d_has_key(tbl->arr, idx) && idx < tbl->max) {
            idx++;
        }
        if(idx == tbl->max) {
            printf("Could not insert that key! Probably issue with clustering.\n");
        } else {
            array_1d_set_key(tbl->arr, key, idx);
        }
    }

    return  tbl;
}

int hashtable_lookup(hashtable *tbl, char *key) {
    int idx = hashtable_hash(tbl, key);

    if(array_1d_inspect_key(tbl->arr, idx) == key) {
        return idx;
    } else {
        while(array_1d_inspect_key(tbl->arr, idx) != key && idx < tbl->max) {
            idx++;
        }
        if(idx == tbl->max) {
            return -1;        
        } else {
            return idx;
        }
    }

}

void hashtable_kill(hashtable *tbl) {
    array_1d_kill(tbl->arr);
    free(tbl);
}

