#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int main()
{
    hashtable *tbl = hashtable_empty(5000);

    hashtable_insert(tbl, "Hej");
    hashtable_insert(tbl, "Hej2");


    //Index will be -1 if the key was not found
    printf("Index: %d\n", hashtable_lookup(tbl, "Hej"));
    printf("Index: %d\n", hashtable_lookup(tbl, "Hej2"));
    printf("Index: %d\n", hashtable_lookup(tbl, "Hej3"));

    hashtable_kill(tbl);
    return 0;
}