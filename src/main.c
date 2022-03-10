#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int main()
{
    hashtable *tbl = hashtable_empty(5000);

    hashtable_insert(tbl, "Hej");
    hashtable_insert(tbl, "Hej2");

    //idx = -1 if the key was not found.
    int idx = hashtable_lookup(tbl, "Hej");

    printf("The index is: %d\n", idx);
    return 0;
}