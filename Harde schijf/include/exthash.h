#pragma once

#include "schijf.h"
#include "pagina.h"
#include "utils.h"
#include <bitset>
#include <memory>
#include <ostream>
#include <vector>

using std::ostream;
using std::unique_ptr;
using std::vector;


typedef unsigned int uint;

template <class Sleutel, class Data, unsigned int orde>
class ExtendibleHashTable {
    friend ostream &operator<<(ostream &out, ExtendibleHashTable<Sleutel, Data, orde> exthash) {
        out << "Uitwendige hashtabel (globale diepte=" << exthash.globale_diepte << ")\n";

        for (uint i = 0; i < exthash.blok_indices.size(); i++) {
            out << to_binary(i, exthash.globale_diepte) << " -> " << exthash.blok_indices[i] << "\n";
            out << exthash.schijf.lees(exthash.blok_indices[i]);
            out << "-----------------\n";
        }

        return out;
    }

  private:
    int globale_diepte = 0; // 'd' in de slides/cursus
    Schijf<Pagina<Sleutel, Data, orde>> &schijf;
    vector<BlokIndex> blok_indices; // 'hashtabel' in de slides/cursus

  public:
    ExtendibleHashTable(Schijf<Pagina<Sleutel, Data, orde>> &schijf) : schijf(schijf) {
        //we starten met 1 lege pagina op de schijf
        Pagina<Sleutel, Data, orde> nieuwePagina;
        blok_indices.push_back(schijf.schrijf(nieuwePagina));
    }

    void voegtoe(const Sleutel &sleutel, const Data &waarde); // waarde bij de sleutel wegschrijven op de schijf
    unique_ptr<Data> geefData(const Sleutel &sleutel);        // waarde bij de sleutel opvragen
    unique_ptr<Data> verwijder(const Sleutel &sleutel);        // sleutel verwijderen
};

template <class Sleutel, class Data, unsigned int orde>
void ExtendibleHashTable<Sleutel, Data, orde>::voegtoe(const Sleutel &sleutel, const Data &waarde) {
    uint hash = geef_deel_van_hash(sleutel, globale_diepte);
    Pagina<Sleutel, Data, orde> pagina = schijf.lees(blok_indices[hash]);
    // std::cout<<pagina.isVol()<< " " << pagina.getOrde() <<std::endl;
    if(pagina.isVol())
    {
        if(pagina.getK() == globale_diepte)
        {
            globale_diepte++;
            blok_indices.resize(blok_indices.size()*2);// hashtabel verdubbelt in grootte wanneer globale_diepte gelijk is aan de pagina_diepte van volle pagina waaraan een sleutel moet worden toegevoegd
            for (int i = 0; i < blok_indices.size()/2; i++)
            {
                blok_indices[blok_indices.size()/2+i] = blok_indices[i] + 1 << globale_diepte;// vul hashtabel aan
            }
        }
        pagina = pagina.splits();
        blok_indices.push_back(schijf.schrijf(pagina));
    }
    pagina.voegtoe(sleutel, waarde);
}

template <class Sleutel, class Data, unsigned int orde>
unique_ptr<Data> ExtendibleHashTable<Sleutel, Data, orde>::geefData(const Sleutel &sleutel) {
    uint hash = geef_deel_van_hash(sleutel, globale_diepte);
    Pagina<Sleutel, Data, orde> pagina = schijf.lees(blok_indices[hash]);
    return pagina.geefData(sleutel);
}

template <class Sleutel, class Data, unsigned int orde>
unique_ptr<Data> ExtendibleHashTable<Sleutel, Data, orde>::verwijder(const Sleutel &sleutel) {
    uint hash = geef_deel_van_hash(sleutel, globale_diepte);
    Pagina<Sleutel, Data, orde> pagina = schijf.lees(blok_indices[hash]);
    return pagina.verwijder(sleutel);
}