#ifndef __BELLMANFORD_H
#define __BELLMANFORD_H

#include "graaf.h"
#include <vector>

using std::vector;

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
KortstePad bellmanFord(const GraafMetTakdata<GERICHT, int> &g, int start_knoop_nr);

#endif // __BELLMANFORD_H