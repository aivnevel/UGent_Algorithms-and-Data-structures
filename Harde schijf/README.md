## Opgave

### Uitwendige hashtabel

Schrijf de functies `voegtoe`, `geefData` en `verwijder` om gegevens toe te voegen en op te 
zoeken in een uitwendige hashtabel gedefinieerd in de klasse [`ExtendibleHashTable`](include/exthash.h).

Deze klasse slaat zijn gegevens op in `Pagina`'s, waarvan het maximum aantal elementen
gegeven is door de `orde` van de `ExtendibleHashTable`. Deze pagina's worden opgeslagen
in de [`Schijf`](include/schijf.h) klasse gekend uit het labo B-Trees.

We maken gebruik van de ingebouwde `std::hash`-functie om de hash van een sleutel te 
berekenen. Je krijgt van ons 2 hulpfuncties die deze hashfunctie oproepen en de hash verwerken:

```cpp

/**
 * Geef het getal terug dat wordt voorgesteld door de minst significante
 * `aantal_bits` uit de hash van `sleutel`.
 *
 * Voor sleutel s met hash 11001101:
 * geef_deel_van_hash(s, 3) = 5 = 0b101
 */
template <class Sleutel>
uint geef_deel_van_hash(Sleutel sleutel, uint aantal_bits);

/**
 * Geef de bit terug die staat op `plaats` bits van het einde van de hash.
 * 
 * vb. plaats 0 geeft de allerlaatste bit van de hash terug.
 *     plaats 1 geeft de voorlaatste bit van de hash terug.
 * 
 * Voor sleutel s met hash 11001101:
 * geef_bit_van_hash(s, 0) = true
 * geef_bit_van_hash(s, 1) = false
 * 
 * @returns true als bit 1 is, false als bit 0 is
 */
template <class Sleutel>
bool geef_bit_van_hash(Sleutel sleutel, uint plaats);

```

Verder zijn de functies `voegtoe` en `geefData` en `verwijder` in `Pagina` al
geimplementeerd voor jou.

1. Schrijf in [`Pagina`](include/pagina.h) een functie `splits` die kan gebruikt worden om een volle 
   pagina te splitsen door de `pagina_diepte` met 1 te verhogen. Het ene deel van 
   de sleutels blijft in de bestaande pagina zitten, het andere deel komt terecht
   in een nieuwe pagina die als resultaat van de `splits`-functie wordt teruggegeven.

2. Schrijf in [`ExtendibleHashTable`](include/exthash.h) de functie `voegtoe`. Roep op het juiste
   moment de functie `Pagina::splits` op, en doe het nodige om het resultaat hiervan
   op te slaan.

3. Schrijf in `ExtendibleHashTable` de functie `geefData`. Je kan gebruik maken van
   `Pagina::geefData` voor een deel van het werk.

4. Schrijf in `ExtendibleHashTable` de functie `verwijder`. Je kan gebruik maken van
   `Pagina::verwijder` voor een deel van het werk. Het is niet nodig om pagina's terug
   samen te voegen als dit kan. Een unique_ptr naar de data die bij de sleutel hoorde, wordt teruggegeven.


**TIPS**:

* De klasse `Schijf` stelt een trage harde schijf voor. Beperk het aantal 
  `lees`/`schrijf`/`herschrijf` dus zoveel mogelijk

* Het gebruik van bit-operatoren is gemakkelijker om over te redeneren dan `pow`:

  ```cpp

  int b = 1;               // 0b0001
  int c = b << 2;          // 0b0100
  int d = b | c;           // 0b0101
  int f = 0b1001 & 0b1010; // 0b1000
  ```
