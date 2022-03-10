# Datatypsimplementationer för kursen datastrukturer och algoritmer vid Institutionen för datavetenskap, Umeå universitet.

# Version 1.0.8.2, 2019-03-26.

# Givna datatyper

Här återfinns implementationer av några av de datatyper som kommer användas
under denna kurs. Nedan följer information om hur dessa kompileras och hur
`minimal working examples` körs för varje datatyp.

## Headerfiler

Headerfilerna för de givna datatyperna är alla samlade i mappen `include`. Dessa
kan inkluderas med hjälp av `-I`-flaggan till `gcc`, se exempel nedan.

## undefined reference

Det är möjligt att du får t.ex. följande felmeddelande:

```bash
/tmp/ccLd0e5H.o: In function `queue_empty':
queue.c:(.text+0x14): undefined reference to `list_empty'
```

Detta innebär att du inte anget alla nödvändiga C-filer till kompilatorn. I
fallet ovan saknas `list.c`.

# En-dimensionellt fält

```bash
user@host:~$ cd ~/datastructures/src/array_1d
user@host:~/datastructures/src/array_1d$ gcc -std=c99 -Wall -I../../include/ array_1d.c array_1d_mwe1.c -o array_1d_mwe1
user@host:~/datastructures/src$ ./array_1d_mwe1
[ [1], [4], [9], [16], [25], [36] ]
user@host:~/datastructures/src/array_1d$ gcc -std=c99 -Wall -I../../include/ array_1d.c array_1d_mwe2.c -o array_1d_mwe2
user@host:~/datastructures/src$ ./array_1d_mwe2
[ [(Jan, 31)], [(Feb, 28)], [(Mar, 31)], [(Apr, 30)], [(May, 31)], [(Jun, 30)], [(Jul, 31)], [(Aug, 31)], [(Sep, 30)], [(Oct, 31)], [(Nov, 30)], [(Dec, 31)] ]
```
# Två-dimensionellt fält

```bash
user@host:~$ cd ~/datastructures/src/array_2d
user@host:~/datastructures/src/array_2d$ gcc -std=c99 -Wall -I../../include/ array_2d.c array_2d_mwe1.c -o array_2d_mwe1
user@host:~/datastructures/src/array_2d$ ./array_2d_mwe1
[ [ [11], [12], [13] [ [21], [22], [23] [ [31], [32], [33] [ [41], [42], [43] ]
```
# Lista (oriktad, dubbellänkad)

```bash
user@host:~$ cd ~/datastructures/src/list
user@host:~/datastructures/src/list$ gcc -std=c99 -Wall -I../../include/ list.c list_mwe1.c -o list_mwe1
user@host:~/datastructures/src/list$ ./list_mwe1
List after inserting one key:
( [5] )
List after inserting second key at the end:
( [5], [8] )
List after inserting a third key in the middle:
( [5], [2], [8] )
List after removing first element:
( [2], [8] )
```

# Riktad lista (enkellänkad)

```bash
user@host:~$ cd ~/datastructures/src/dlist
user@host:~/datastructures/src/dlist$ gcc -std=c99 -Wall -I../../include/ dlist.c dlist_mwe1.c -o dlist_mwe1
user@host:~/datastructures/src/dlist$ ./dlist_mwe1
("Alfons", "Bengt", "Cia", "David", "Florian", "Gunnar")
```

# Kö

```bash
user@host:~$ cd ~/datastructures/src/queue
user@host:~/datastructures/src/queue$ gcc -std=c99 -Wall -I../../include/ queue.c queue_mwe1.c ../list/list.c -o queue_mwe1
user@host:~/datastructures/src/queue$ ./queue_mwe1
QUEUE before dequeuing:
{ [1], [2], [3] }
QUEUE after dequeuing:
{ [2], [3] }
```


# Stack

```bash
user@host:~$ cd ~/datastructures/src/stack
user@host:~/datastructures/src/stack$ gcc -std=c99 -Wall -I../../include/ stack.c stack_mwe1.c -o stack_mwe1
user@host:~/datastructures/src/stack$ ./stack_mwe1
--STACK before popping--
{ [3], [2], [1] }
--STACK after popping--
{ [2], [1] }
```

# Tabell

```bash
user@host:~$ cd ~/datastructures/src/table
user@host:~/datastructures/src/table$ gcc -std=c99 -Wall -I../../include/ table.c table_mwe1.c ../dlist/dlist.c -o table_mwe1
user@host:~/datastructures/src/table$ ./table_mwe1
Table after inserting 3 pairs:
[98185, Kiruna]
[90184, Umea]
[90187, Umea]
Lookup of postal code 90187: Umea.
Table after adding a duplicate:
[90187, Umea (Universitet)]
[98185, Kiruna]
[90184, Umea]
[90187, Umea]
Lookup of postal code 90187: Umea (Universitet).
```
