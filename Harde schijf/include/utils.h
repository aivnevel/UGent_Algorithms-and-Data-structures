#pragma once

#include <string>
#include <functional>
using std::string;

typedef unsigned int uint;



/**
 * Geef het getal terug dat wordt voorgesteld door de minst significante
 * `aantal_bits` uit de hash van `sleutel`.
 */
template <class Sleutel>
uint geef_deel_van_hash(Sleutel sleutel, uint aantal_bits) {
    size_t hash = std::hash<Sleutel>{}(sleutel);
    uint mask = (1 << aantal_bits) - 1;
    return hash & mask;
}

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
bool geef_bit_van_hash(Sleutel sleutel, uint plaats) {
    size_t hash = std::hash<Sleutel>{}(sleutel);
    return 1 & hash >> plaats;
}

string to_binary(uint getal, int aantal_bits) {
    string resultaat = "";
    for (int i = 0; i < aantal_bits; i++) {
        resultaat = (1 & getal ? "1" : "0") + resultaat;
        getal >>= 1;
    }
    return resultaat;
}

