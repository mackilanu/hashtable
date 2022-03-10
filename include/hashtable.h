#ifndef HASHTABLE_H
#include "array_1d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 5000

#define HASHTABLE_H

typedef struct hashtable hashtable;

hashtable* hashtable_empty(int max);

hashtable* hashtable_insert(hashtable* tbl, char *key);

hashtable *hashtable_remove(hashtable *tbl, char *key);
int hashtable_lookup(hashtable *tbl, char *key);

int hashtable_hash(hashtable *tbl, char *key);


#endif