## Opgave

### Bellman-Ford

Implementeer in [`bellmanford.cpp`](src/bellmanford.cpp) de volgende functie:

```cpp
/**
 * Deze functie geeft alle kortste paden vanaf een bepaalde start-knoop (met `start_knoop_nr`) terug.
 *
 * Enerzijds geeft het de afstand tot de start-knoop terug 
 * (= som van de kosten van alle gevolgde takken tot deze knoop).
 *
 * Anderzijs geeft het de voorloper terug van elke knoop 
 * (= het knoop-nr die voor een bepaalde knoop op het kortste pad ligt)
 *
 * @throw runtime_error als de graaf een negatieve lus bevat
 */
KortstePad bellmanFord(const GraafMetTakdata<GERICHT, int> &g, int start_knoop_nr){}

```

Hierbij is `KortstePad` gedefinieerd in [`bellmanford.h`](include/bellmanford.h) als een struct met twee vectoren:

```cpp

struct KortstePad {
    /**
     * Afstand is gelijk aan INT32_MAX indien er geen pad is
     */
    vector<int> afstand;

    /**
     * Voorloper is gelijk aan -1 als er geen pad is
     */
    vector<int> voorloper;
};
```

**Tip:** gebruik *structured binding* om het KortstePad object aan te maken.

```cpp

vector<int> afstand (...);
vector<int> voorloper (...);

...

return {afstand,voorloper};

```

### Topdown rood-zwarte boom

Implementeer in [`rzwboom.h`](include/rzwboom.h) een functie die nieuwe knopen op een correcte 
top-down manier zal toevoegen. De functie zal een sleutel aannemen als parameter en is 
gedefinieerd als volgend:

```cpp

void voegtoe_topdown(const Sleutel& sleutel){}

```

**Opmerking:** Duplicate sleutels zijn niet toegelaten in de boom. Als er toch duplicate 
sleutels toegevoegd worden, moet er een `runtime errror` optreden: (`throw runtime_error("sleutel bestaat al");`) 

**Bonus:** Een top-down implementatie van een rood-zwarte boom heeft geen ouderpointers nodig om te werken. Vermijd het gebruik ervan voor bonuspunten.
