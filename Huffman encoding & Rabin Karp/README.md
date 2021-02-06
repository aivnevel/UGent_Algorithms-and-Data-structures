# Test 2 Gevorderde Algoritmen (15 december 2020) voor Alexander Van Nevel

## Beginnen

1. Start de Ubuntu shell.
1. Download de opgave repository. Geef je UGent gebruikersnaam (`aivnevel`) en wachtwoord in wanneer dit gevraagd wordt.

   ```bash
   git clone https://github.ugent.be/GevAlTest2/GevAlTest2-aivnevel.git
   ```

   > ⓘ Indien je hier een authenticatie fout krijgt op Windows is het waarschijnlijk omdat het UGent wachtwoord dat Windows opgeslagen heeft fout is. Je kan dit wachtwoord aanpassen via het "Referentiebeheer" programma, zoek voor de "github.ugent.be" referentie bij "Windows Referenties".

1. Open de test in VSCode vanuit Ubuntu.

   ```bash
   cd GevAlTest2-aivnevel
   code .
   ```

   *Indien je op Windows werkt, controleer dan of je links onderaan het VSCode venster "WSL" of "WSL: Ubuntu" ziet staan zoals op onderstaande screenshot.*

   ![vscode WSL](.examen-tools/vscode-remote-ubuntu.png)
1. Open het bestand `gestart.txt`, verander `neen` in `ja` en sla de wijzigingen op ("File" > "Save").
1. Voer de taak "Start Examen [Gevorderde Algoritmen]" uit (in de bovenste menu "Terminal" > "Run Task..." en dan "Start Examen [Gevorderde Algoritmen]"). **Geef bovenaan het VSCode venster je UGent gebruikersnaam en wachtwoord in.**

   ![Gebruikersnaam en wachtwoord](.examen-tools/username.png)

   Dit dient de wijzigingen in het `gestart.txt` bestand in, en zal iedere drie minuten opnieuw alle wijzigingen indienen tot je de taak stopzet of VSCode afsluit.

1. Controleer op <https://github.ugent.be/GevAlTest2/GevAlTest2-aivnevel.git> of het `gestart.txt` bestand aangepast is.

Tijdens de test zullen de wijzigingen iedere tien minuten ingediend worden. Je kan dit zelf ook manueel doen door middel van de task "Manueel Indienen [Gevorderde Algoritmen]". Om zeker te zijn dat je geen git conflicten krijgt tijdens de test mag je **git niet zelf gebruiken** tijdens de test. Gebruik enkel de tasks om in te dienen.

## Opgave

### Vraag 1: Huffmancodering

Implementeer in [`huffman.cpp`](src/huffman.cpp) de volgende functie:

```cpp
/**
 * Berekent de optimale Huffmancodering voor een tekst waarin de
 * karakters voorkomen met de opgegeven frequenties.
 * 
 * @param freq een woordenboek die elk karakter afbeeldt op het aantal 
 *             keer dat het voorkomt in de tekst.
 * 
 * @returns een woordenboek die elk karakter afbeeldt op zijn optimale binaire
 *          voorstelling. We gebruiken voor het gemak een `string` hiervoor.
 * 
 */
map<uchar, string> huffman(const map<uchar, uint> &freq);
```

Je krijgt van ons een prioriteitswachtrij cadeau die structs kan sorteren volgens het
gewicht dat in deze struct gedefinieerd is:

```cpp
struct Knoop {
   uint gewicht;
};
```

Deze prioriteitswachtrij maak je aan mbv de functie `maak_priority_queue()`.

Om het beheer van de levensduur van deze Knoop-objecten te vergemakkelijken is de
`priority_queue` van het type `priority_queue<shared_ptr<Knoop>>` ipv `priority_queue<Knoop>`.
(We gebruiken `shared_ptr` in plaats van `unique_ptr` omdat de `top`-operatie van `priority_queue`
een `const`-referentie teruggeeft, en daarom niet geschikt is voor een `move`-operatie).

Een voorbeeld van hoe je deze queue gebruikt:

```cpp
auto queue = maak_priority_queue();

queue.push(make_shared<Knoop>(Knoop{6}));
queue.push(make_shared<Knoop>(Knoop{1}));
queue.push(make_shared<Knoop>(Knoop{7}));
queue.push(make_shared<Knoop>(Knoop{3}));
queue.push(make_shared<Knoop>(Knoop{4}));
queue.push(make_shared<Knoop>(Knoop{2}));
queue.push(make_shared<Knoop>(Knoop{5}));

while(!queue.empty()){
   auto k = queue.top();
   queue.pop();

   std::cout << k->gewicht << "\n";
}
```

Dit levert als output:

```
1
2
3
4
5
6
7
```

Breid deze `Knoop`-struct uit met de nodige extra velden om de optimale huffmancodering te kunnen 
berekenen.
 
**Tip:** denk bijvoorbeeld aan het toevoegen van enkele pointers om een boom van knopen op te stellen. 
Is er een verschil in inhoud tussen bladknopen en niet-bladknopen?

### Vraag 2: Rabin-Karp

Een mogelijke methode om een bepaald patroon te zoeken in de tekst maakt is het algoritme van Karp en Rabin. 
Implementeer hiervoor in [`vraag2.cpp`](src/vraag2.cpp) de zoekfunctie:

```cpp

queue<int> zoek_rabinkarp(const string& naald, const string &hooiberg, int priemgetal = 997){}

```

Gebruik als hashfunctie `modulo <priemgetal>` (zoals het voorbeeld uit de slides, en uitgelegd in de cursus). 
Een karakter wordt voorgesteld door 8 bits. Het alfabet is dus 2^8 = 256 karakters groot (cfr. constante `ALFABET_GROOTTE`).

**Tip:** Een eerste versie zonder *rolling hash* kan handig zijn om de rest van je code te valideren. Rabin-Karp is echter pas efficient als 
de berekende hash voor de vorige positie in de hooiberg wordt hergebruikt voor de volgende positie. Vermijd daarom in je finale versie om 
de hash elke keer vanaf 0 terug te berekenen.

## Indienen

1. Voer de task "Manueel Indienen [Gevorderde Algoritmen]" uit (via de menu bovenaan: "Terminal" > "Run Task..." en kies "Manueel Indienen [Gevorderde Algoritmen]").
1. Controleer op <https://github.ugent.be/GevAlTest2/GevAlTest2-aivnevel.git> of alle wijzigingen doorgevoerd zijn.
1. Sluit VSCode af zodat het automatisch indienen stopt.
1. Laat je begeleider via MS Teams weten dat je klaar bent.

Als je jouw code op GitHub ziet staan dan heb je correct ingediend. Je kan zoveel indienen als je wilt. De laatst ingediende code zal verbeterd worden. Na het indienen mag je VSCode op je computer afsluiten. Bij het afsluiten zal het automatisch indienen ook gestopt worden.