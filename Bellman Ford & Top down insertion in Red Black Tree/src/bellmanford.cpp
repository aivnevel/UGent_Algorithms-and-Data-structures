#include "bellmanford.h"
#include <queue>

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
KortstePad bellmanFord(const GraafMetTakdata<GERICHT, int> &graaf, int start_knoop_nr) 
{
    vector<int> afstand(graaf.aantalKnopen(), INT32_MAX), voorloper(graaf.aantalKnopen(), -1), aantalKeerBezocht(graaf.aantalKnopen(), 0);
    afstand[start_knoop_nr] = 0;
    std::queue<int> wachtrij;
    wachtrij.push(start_knoop_nr);
    while(!wachtrij.empty()) 
    {
        int knoop = wachtrij.front();
        if(aantalKeerBezocht[knoop]++ > graaf.aantalKnopen())
        {
            throw std::runtime_error("negatieve lus");
        }
        wachtrij.pop();
        if(afstand[knoop] == INT32_MAX) 
        {
            continue;
        }
        for (auto&& [buurKnoop, verbinding] : graaf[knoop])
        {
            if(afstand[buurKnoop] > afstand[knoop] + *graaf.geefTakdata(knoop, buurKnoop)) 
            {
                afstand[buurKnoop] = afstand[knoop] + *graaf.geefTakdata(knoop, buurKnoop);
                voorloper[buurKnoop] = knoop;
                wachtrij.push(buurKnoop);
            }
        }
    }
    return {afstand, voorloper};
}
