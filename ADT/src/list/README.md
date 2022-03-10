# Dubbellänkad lista
En två-cellsimplementation av ADT:n _Lista_.

## Minneshantering

Följande kodsnutt kommer skapa en lista med ett element som har värdet 5. I
detta exempel så allokeras inget minne dynamiskt, därför behöver vi inte heller
ta hand om något minne efter vi använt klart listan.

```c
int val = 5;
list *l = list_empty(NULL);
list_insert(l, &val, list_first(l));
```

Vi kan skriva om ovan exempel så att minne allokeras på heapen, men då måste vi
manuellt komma ihåg att avallokera detta minne efter användning.

```c
int *val = malloc(sizeof(int));
*val = 5;

list *l = list_empty(NULL);
list_insert(l, val, list_first(l));
...
list_kill(l);
free(val);
```

Om vi vill allokera minne dynamiskt, men vill att listan själva ska hantera
avallokering av minne (e.g. vid `list_remove`) så behöver vi ange en
minneshanteringsfunktion:
```c
int *val = malloc(sizeof(int));
*val = 5;

list *l = list_empty(free);
list_insert(l, val, list_first(l));
...
list_kill(l);
```

I exemplet ovan kommer `list_kill(l)` att anropa `free` för varje element i
listan, och därmed sköta minneshanteringen åt oss.

### Egen free-funktion

Det är också möjligt att definiera en egen funktion som ska sköta
avallokeringen. Till exempel kanske vi vill skriva ut varje värde som
avallokeras i debugging-syfte. Då kan vi skriva en enkel wrapper-funktion för
`free` på följande sätt:

```c
static void free_and_print(void *data)
{
	printf("Free'ing [%d]\n", *(int*)data);
	free(data);
}
```

Denna funktion skulle då kunna användas på följande sätt:

```c
list *l = list_empty(free_and_print);
int *val = malloc(sizeof(int));
*val = 5;
list_insert(l, val, list_first(l));
list_kill(l);
```

Denna kodsnutt skulle då skriva ut `Free'ing [5]`.


## Utskrift

För att skriva ut listan, t.ex. vid debugging eller för att visa innehållet för
en användare så kan vi definiera en egen funktion för att presentera tillståndet
hos datatypen. Det enklaste fallet är om vi enbart vill skriva ut, e.g., en
lista med heltal där varje värde hamnar på en egen rad:

```c
static void print_ints(const void *data)
{
	printf("%d\n", *(int*)data);
}
```

Notera att inparametern är av typen `const`. `const` indikerar att pekaren bara
får läsas, ej manipuleras. Vi vill inte att en print-funktion ska kunna ändra på
listans innehåll.

`print_ints` kan nu användas på följande sätt:

```c
list *l = list_empty(free);
int *val = malloc(sizeof(int));
*val = 5;
list_insert(l, val, list_first(l));

list_print(l, print_ints);
```

Detta exempel skulle skriva ut `5` på en egen rad.


# Minimal working example

Mycket av det som behandlats ovan sammanfattas i följande minimal working
example:

Se [list_mwe1.c](list_mwe1.c) och [list_mwe2.c](list_mwe2.c).
