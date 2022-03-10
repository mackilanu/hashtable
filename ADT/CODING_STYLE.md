# Kodkonvention

I detta dokument beskrivs den kodkonvention som har följts/ska följas
för kod som läggs till kodbasen. Konventionen är till stor del baserad
på kodkonventionen som följs i Linux-kärnan. Därför kommer läsaren
hänvisas till dokumentet med den officiella kernelkonventionen.


# Linuxkärnans kodkonvention

Se [Linux kernel coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html).
Nedan följer en uppräkning av vilka punkter vi ska följa, samt
eventuella avvikelser från dessa. Om en punkt från dokumentet ovan ej
nämns nedan så gäller punkten ej.

## 1. Indentation

Indenteringskonventionen ska följas helt och hållet. Det är möjligt att
konfigurera utvecklingsmiljön (e.g. Codelite) att automatiskt indentera
korrekt.

## 2. Breaking long lines and strings

Denna punkt är också mycket viktig, samt något din utvecklingsmiljö kan 
hantera eller varna för.

## 3. Placing Braces and Spaces

Här ska alla punkter följas (även de under 3.1), med ett undantag:
Ensamma satser i t.ex. if-satser *ska* ha måsvingar.

## 4. Naming

När det kommer till namngivning är det viktigt att ha i åtanke att koden
tillsammans med kommentarerna ska tydligt förklara syftet med koden. Därför är
det viktigt att konventionen som beskrivs under `4. Naming` tolkas med detta i
hänsyn. Det innebär till exempel att om koden blir enklare att läsa med
variabelnamnet `counter` istället för `c` eller `tmp`, bör `counter` användas
istället.

## 5. Typedefs

Här avviker kursen från Linuxkärnans kodkonvention. För att främja
datatypernas gränsytor och göra dem så lik de teoretiska gränsytorna
som möjligt så används `typedefs` för t.ex. `struct list_pos`. I
Linuxkärnan hade motsvarande implementation krävt att det skrevs
`struct list_pos pos` överallt, medan datatyperna givna på kursen
förenklar detta till `list_pos pos`. Det viktiga här är att lära sig
gränsytorna.

## 6. Functions

Denna konvention ska följas så som den presenteras. Långa funktioner kommer
under denna kurs alltid vara onödigt, dela upp i mindre funktioner! Det ökar
läsbarheten, förenklar debugging, samt gör det enklare att diskutera koden.

## 7. Centralized exiting of functions

Det finns anledningar till att `goto` används i Linuxkärnan (e.g.
bakåtkompabilitet), men under denna kurs ska ni ej använda detta.

## 8. Commenting

Följ det första exemplet för kommentarer. Det finns exempel i de givna
datatyperna på hur funktioner kan dokumenteras.

## 14. Allocating memory

I Linuxkärnan finns inte `malloc` och `calloc`, motsvarande funktioner heter
`kmalloc` samt `kcalloc`. Vi kommer under denna kurs att översätta Linuxkärnans
konvention till följande:

```c
p = malloc(sizeof(*p));
```

samt 

```c
p = calloc(n, sizeof(*p));
```

Det är fullt möjligt att i det senare fallet vända på parametrarna (i.e.
`calloc(sizeof(*p), n)`) då storleken på minnet som allokeras beräknas som
första argumentet gånger det andra argumentet (i.e., 
`n*sizeof(*p) == sizeof(*p)*n`).

## 16. Function return keys and names

Här är det första och sista stycket vad som är viktigt att följa. Om en funktion
returnerar huruvida funktionen lyckades eller ej så signifierar `0` ett lyckat
anrop, och negativa värden signifierar fel (e.g. `-1` om en fil inte finns, `-2`
om filen inte gick att läsa). Om en funktion returnerar en pekare `p`, så 
indikerar `p == NULL` att funktionen inte lyckades.

# Avslutning

Det finns visst rum för tolkning under några av dessa punkter.
