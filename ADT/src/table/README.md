# Tabellimplementation

Det som skiljer tabellen från de övriga datatyperna är att vi här måste hantera
både nycklar och värden. Denna hantering fungerar analogt med de övriga, men vi
konkretiserar ändå med ett par exempel på hur tabellen kan användas.

## Jämförelsefunktion

För att vår tabell ska fungera behöver vi specificera hur nycklar ska jämföras.
Detta tillåter oss att t.ex. använda strängar eller heltal som nycklar utan att
den underliggande implementationen behöver ändras. Detta bygger på en
`compare_function`, som tar två pekare och returnerar `0` ifall de är lika, `0>`
om första värdet är större än det andra, samt `0<` om första värdet är mindre än
det andra. I fallet med heltal kan detta se ut såhär:

```c
static int compare_ints(const void *k1, const void *k2)
{
	int key1 = *(int *)k1;
	int key2 = *(int *)k2;

	if ( key1 == key2 )
		return 0;
	if ( key1 < key2 )
		return -1;
	return 1;
}
```

Vi kan då skapa en tabell med `table_empty(compare_ints, free, free)  som vi
sedan kan använda såhär:

```c
table *t = table_empty(compare_ints, free, free);

int *key = malloc(sizeof(int));
*key = 5;
char *key = calloc(5, sizeof(char));
strcpy(key, "test");

table_insert(t, key, key);

int key_to_lookup = 5;
table_lookup(t, &key_to_lookup); 
```

Om vår `compare_function` är felaktigt implementerad så kommer inte
`table_lookup` hitta värdet, trots att vi stoppat in det.

## Minneshantering

När vi skapar en tabell måste vi specificera hur minnet för nycklar och värden
ska hanteras. Ofta kommer vi vilja allokera minne på heapen dynamiskt, och låta
tabellen avallokera både nyklar och värden:

```c
table *t = table_empty(compare_ints, free, free);

int *key = malloc(sizeof(int));
*key = 5;
char *key = calloc(5, sizeof(char));
strcpy(key, "test");

table_insert(t, key, key);
table_kill(t);
```

Vi skulle även kunna låta nycklarna ligga på stacken, och bara allokera värden
på heapen enl. följande exempel:

```c
table *t = table_empty(compare_ints, NULL, free);

int key = 5;
char *key = calloc(5, sizeof(char));
strcpy(key, "test");

table_insert(t, &key, key);
table_kill(t);
```

Det skulle också kunna vara så att nycklarna allokeras dynamiskt, men att de
också stoppas i en annan datatyp (t.ex. en lista). Följande kodsnutt illustrera
det exemplet:

```c
table *t = table_empty(compare_ints, NULL, free);
list *l = list_empty(free);

int *key = malloc(sizeof(int));
*key = 5;
char *key = calloc(5, sizeof(char));
strcpy(key, "test");

table_insert(t, key, key);
list_insert(l, key, list_first(l));

// Kommer inte frigöra key, bara key
table_kill(t);

// Frigör också key
list_kill(l);
```

## Utskrift

Till skillnad från de övriga datatyperna så vill vi skriva ut både nyckeln och
värdet med vår print-funktion. Istället för att exponera den interna `struct`:en
`table_entry` utanför c-filen, så använder vi oss istället av en print-funktion
som tar två parameterar.

```c
static void print_int_string_pair(const void *key, const void *key)
{
	printf("[%d, %s]\n", *(int*)key, (char*)key);
}
```

Ett anrop till `table_print(t, print_int_string_pair)` skulle då skriva ut `[5,
    test]` om vi utgår ifrån det tidigare exemplet.


# Minimal Working Example

Se [table_mwe1.c](table_mwe1.c), [table_mwe2.c](table_mwe2.c) och [table_mwe3.c](table_mwe3.c).
