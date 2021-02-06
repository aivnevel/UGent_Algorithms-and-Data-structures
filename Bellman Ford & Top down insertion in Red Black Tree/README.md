# Test 1 Gevorderde Algoritmen (10 november 2020) voor Alexander Van Nevel

## Beginnen

1. Start de Ubuntu shell.
1. Download de opgave repository. Geef je UGent gebruikersnaam (`aivnevel`) en wachtwoord in wanneer dit gevraagd wordt.

   ```bash
   git clone https://github.ugent.be/GevAlTest1/GevAlTest1-aivnevel.git
   ```

   > ⓘ Indien je hier een authenticatie fout krijgt op Windows is het waarschijnlijk omdat het UGent wachtwoord dat Windows opgeslagen heeft fout is. Je kan dit wachtwoord aanpassen via het "Referentiebeheer" programma, zoek voor de "github.ugent.be" referentie bij "Windows Referenties".

1. Open de test in VSCode vanuit Ubuntu.

   ```bash
   cd GevAlTest1-aivnevel
   code .
   ```

   *Indien je op Windows werkt, controleer dan of je links onderaan het VSCode venster "WSL" of "WSL: Ubuntu" ziet staan zoals op onderstaande screenshot.*

   ![vscode WSL](.examen-tools/vscode-remote-ubuntu.png)
1. Open het bestand `gestart.txt`, verander `neen` in `ja` en sla de wijzigingen op ("File" > "Save").
1. Voer de taak "Start Examen [Gevorderde Algoritmen]" uit (in de bovenste menu "Terminal" > "Run Task..." en dan "Start Examen [Gevorderde Algoritmen]"). **Geef bovenaan het VSCode venster je UGent gebruikersnaam en wachtwoord in.**

   ![Gebruikersnaam en wachtwoord](.examen-tools/username.png)

   Dit dient de wijzigingen in het `gestart.txt` bestand in, en zal iedere 2.5 minuten opnieuw alle wijzigingen indienen tot je de taak stopzet of VSCode afsluit.

1. Controleer op <https://github.ugent.be/GevAlTest1/GevAlTest1-aivnevel.git> of het `gestart.txt` bestand aangepast is.

Tijdens de test zullen de wijzigingen iedere tien minuten ingediend worden. Je kan dit zelf ook manueel doen door middel van de task "Manueel Indienen [Gevorderde Algoritmen]". Om zeker te zijn dat je geen git conflicten krijgt tijdens de test mag je **git niet zelf gebruiken** tijdens de test. Gebruik enkel de tasks om in te dienen.

## Opgave

### Vraag 1: Bellman-Ford

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

### Vraag 2: Topdown rood-zwarte boom

Implementeer in [`rzwboom.h`](include/rzwboom.h) een functie die nieuwe knopen op een correcte 
top-down manier zal toevoegen. De functie zal een sleutel aannemen als parameter en is 
gedefinieerd als volgend:

```cpp

void voegtoe_topdown(const Sleutel& sleutel){}

```

**Opmerking:** Duplicate sleutels zijn niet toegelaten in de boom. Als er toch duplicate 
sleutels toegevoegd worden, moet er een `runtime errror` optreden: (`throw runtime_error("sleutel bestaat al");`) 

**Bonus:** Een top-down implementatie van een rood-zwarte boom heeft geen ouderpointers nodig om te werken. Vermijd het gebruik ervan voor bonuspunten.

## Indienen

1. Voer de task "Manueel Indienen [Gevorderde Algoritmen]" uit (via de menu bovenaan: "Terminal" > "Run Task..." en kies "Manueel Indienen [Gevorderde Algoritmen]").
1. Controleer op <https://github.ugent.be/GevAlTest1/GevAlTest1-aivnevel.git> of alle wijzigingen doorgevoerd zijn.
1. Sluit VSCode af zodat het automatisch indienen stopt.
1. Laat je begeleider via MS Teams weten dat je klaar bent.

Als je jouw code op GitHub ziet staan dan heb je correct ingediend. Je kan zoveel indienen als je wilt. De laatst ingediende code zal verbeterd worden. Na het indienen mag je VSCode op je computer afsluiten. Bij het afsluiten zal het automatisch indienen ook gestopt worden.