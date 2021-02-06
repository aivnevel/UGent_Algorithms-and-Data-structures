//testprogramma voor het social distance algoritme

#include "lijst.h"
#include <cstdlib>
#include <iostream>
#include <string>


Lijst<int> maakLijst(const std::vector<int>& v){
    Lijst<int> l;
    for(auto sleutel: v){
        l.voegToe(sleutel);
    }
    return l;
}

int main()
{
    {
        /*
         Implementatie:
                100%, volledig
         
         Ontwerpkeuze minimum vereiste:
            De lijst eenmalig overlopen met zo weinig mogelijk pointers naar lijst.
         
         *** EXTRA CHECK: WAARVOOR DE PRECONDITIE GELDT MAAR DE LIJST NOG STEEDS ZAL CRASHEN
            1. de eerste stap is om te controleren of er wel elementen in de lijst staan, met if(*this) wordt dit getest (eerste lijn in methode applySocialDistancing: met een lege lijst crasht de functie
                => extra vector 7 gemaakt om dit aan te tonen (*)
         
         *** INITIALISATIE
            2. Initialiseer een pointer naar een lijst om de gelinkte lijst te overlopen (loper) en een pointer naar een lijst om aan te geven waar er telkens elementen zullen toegevoegd worden (tweedeLijst)
         
            3. initialiseer verder 2 variabelen voor de huidige sublijst en 2 variabelen van de vorige sublijst, initieel bevatten alle 4 de sleutel van de eerste sublijst
                        (door een extra check te doen in berekenOverlap(...), die ik verder in de uitleg zal verduidelijk
         
            4. initialiseer een variabele voor de overlap te berekenen
         
         *** ALGORITME
            5. laat de loper over de lijst lopen totdat het een element tegenkomt waarvoor geldt dat het element niet meer kan opgenomen worden op een manier dat het bereik niet overschreid wordt met meer dan N:
                    sleutel <= tweedeMin + N && sleutel >= tweedeMax - N ## hier lees je: indien we de initiele minima veronderstellen, kan de sleutel dan nog in het bereik liggen?
                                                                                        + indien we de initiele maxima veronderstellen, kan de sleutel dan nog in het bereik liggen?
                                                                                        indien het antwoord hierop ja is en sleutel vormt een nieuw extrema dan passen we het bereik aan,
                                                                                    door ofwel tweedeMax of tweedeMin uit te breiden
                hiernaast gebeurd er een extra check die controleer of de loper nog een volgend element heeft, indien dit niet zo is dan stopt de while lus
            
            6. aan de hand van het gekende vorige minimum en maximum + het huidige minimum en maximum kan je nu de overlap berekenen, hier zit je echter met een probleem:
                        bij de eerste iteratie bevatten de vorige minimum en maximum dezelfde waarde EN ze liggen in het bereik van de berekende minimum en maximum hiervoor doe ik een extra controle in berekenOverlap()
                                indien vorige minimum en maximum beiden in het bereik liggen van berekende minimum en maximum dan is er geen sprake van overlap: de functie geeft 0 terug
                    erna is dit niet meer van toepassing want anders, als het toch in het bereik ligt van het berekende minimum en maximum bevat de methode een fout, berekenen van de overlap gebeurd als volgt:
         
                    Stel:
                                1_____5
                                    |_______|
                                    3       7
                                                    
                
                    strategie:
                                                                
                                (bereik overlapt): ligt minimum of maximum in het interval van berekende minimum en maximum ? (of omgekeerd)
                                                        MAAR het overlappende deel ligt niet in het volledige bereik,
                                                            dit is bij de eerste iteratie altijd zo,
                                                            min en max worden initieel ingestelt op de waarde van de eerste sleutel.
                                                            Daarom is deze extra 'MAAR' vereist.
                                                    
                                                    indien het antwoord hierop ja is, dan word de overlap berekend als volgt: het verschil van de overlappende delen + 1, in dit geval (5 - 3) + 1 is een overlap van 3
                                                                        Klopt dit?
                                                                                    1. 3 en 3
                                                                                    2. 4 en 4
                                                                                    3. 5 en 5
                                                                            Inderdaad we hebben een overlap van 3
                                (bereik overlapt niet): overlap van 1
         
                                speciaal geval
         7. isolationKeys toevoegen
                tweedeLoper staat op de plaats waar isolation keys worden toegevoegd, tweedeLoper zal verder in deze uitleg uitgebreid besproken worden, momenteel veronderstellen we dat dit ook zo is
                Voeg vooraan toe of achteraan?
                De keuze hier is vrij duidelijk, aangezien we een unique_ptr hebben die verder in de lijst staat, dan de plaats waar isolationKeys toegevoegd worden zal deze gemoved worden,
                moesten we achteraan toevoegen. Dit is ongewenst, de plaats verliezen waar de loper staat, betekent dat deze opnieuw overlopen zou moeten worden.
                
                Hier is de keuze dus snel gemaakt: vooraan toevoegen, de functie 'void voegToe(const T& sleutel)' die reeds gedefinieerd en geïmplementeerd werd, wordt hiervoor gebruikt.
         
         8. unique_ptr's verzetten
                Aan het einde word de tweedeLoper verzet naar de plaats waar de loper staat, tweedeLoper zal dus wijzen naar het einde van de net overlopen sublijst
                loper wordt hierna verzet naar de opvolger van tweedeLoper, waarom is het niet erg dat ik niet controleer of een opvolgend element hier wel bestaat?
         
                    het is niet erg dat de loper dan staat op het element na het laatste element aangezien dit element OOK bestaat
                    (bewijs hiervoor is dat alle elementen een Lijst bevatten dus ook het laatste element)
                    !MAAR: het element NA het laatste element zijn volgend is niet ingevuld EN, zijn sleutel is ook NIET ingevuld! (**)
         
         9. Doorgeven van de berekende min, max
                Om in de volgende iteratie het overlappend bereik met de vorige sublijst te berekenen, is het bereik nodig van de vorige sublijst,
                dus bewaren we de berekende min en max in een variabele tweedeMin en tweedeMax
         
         10. Controleren of we het einde van de lijst bereikt hebben (**)
                while(*loper) controleert of de waarde van de loper inhoud bevat, als deze Lijst(unique_ptr) niet is ingevuld met een waarde en een volgende unique_ptr (m.a.w. het laatste element van de lijst) dan stopt de while lus en is het algoritme afgelopen
         
         *** DETAILS
                In de methode applySocialDistancing is er nog specifieke info gegeven over waarom ik wat doe
                                                                        
         */
        //We testen met lijsten van int sleutelwaarden
        std::vector<std::vector<int>> testvectoren;
        //bemerk dat volgorden in omgekeerde volgorde zijn gespecifeerd, omdat voegToe steeds aan het begin van de lijst toevoegt
        std::vector<int> v1 = {1,5,6,3,8,5,6,9,6,7,4,5,1,2};
        testvectoren.push_back(v1);
        std::vector<int> v2 = {7,5,3,2,7,4,5,1,5,6,7,9,1};
        testvectoren.push_back(v2);
		std::vector<int> v3 = {20,1,1,1,1,1,1,6,6,6,6,6,6,6,10};
        testvectoren.push_back(v3);
		std::vector<int> v4 = {1,2,3,4,5,6,7,1,2,3,4,5,6,1,2,3,4,5,1,2,3};
        testvectoren.push_back(v4);
		std::vector<int> v5 = {3,2,1,4,3,2,1,5,4,3,2,1,6,5,4,3,2,1};
        testvectoren.push_back(v5);
        std::vector<int> v6 = {1,5,9,13,13,12,8,5,1};
        testvectoren.push_back(v6);
        /*
            std::vector<int> v7 = {};//(*)
            testvectoren.push_back(v7);
         */
        
        
        int socialDistance = 3;
        int isolationKey = 0;

        for(std::vector<int>& v: testvectoren){
            Lijst<int> l;
            //eerste element in vector wordt laatste element van gelinkte lijst
            l = maakLijst(v);
            std::cerr << "Testen van de vector: " << std::endl;
            l.schrijf(std::cerr);
            std::cerr << std::endl;
            l.applySocialDistancing(socialDistance, isolationKey);
            std::cerr << "Na toepassen van social distancing: " << std::endl;
            l.schrijf(std::cerr);
            std::cerr << std::endl;
        }	
		
    }

    std::cout << "OK\n";

    return 0;
}
