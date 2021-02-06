#pragma once

#include <cassert>
#include <memory>
#include <bitset>
#include "utils.h"
using std::unique_ptr;
using std::make_unique;
using std::ostream;


typedef unsigned int uint;

template <class Sleutel, class Data, unsigned int orde>
class ExtendibleHashTable;

template <class Sleutel, class Data, unsigned int orde>
class Pagina {
    friend class ExtendibleHashTable<Sleutel, Data, orde>;
    friend ostream &operator<<(ostream &out, Pagina<Sleutel, Data, orde> pagina) {
        out << "* Pagina-diepte: " << pagina.pagina_diepte << " *\n";
        for (int i = 0; i < pagina.aantalSleutels; i++) {
            out << pagina.sleutels[i]
                << " (hash: " << std::bitset<8>(std::hash<Sleutel>{}(pagina.sleutels[i])) << "): "
                << pagina.data[i] << "\n";
        }
        return out;
    }

  private:
    Sleutel sleutels[orde];
    Data data[orde];

    uint aantalSleutels = 0;
    uint pagina_diepte = 0; // 'k' in de slides

  public:

    int getK()
    {
        return pagina_diepte;
    }

    int getOrde()
    {
        return orde;
    }

    bool isVol() {
        return aantalSleutels == orde;
    }

    void voegtoe(Sleutel sleutel, Data waarde) {
        assert(!isVol());

        //voeg toe op een gesorteerde manier
        int i = aantalSleutels;
        for (; i > 0 && sleutels[i - 1] > sleutel; i--) {
            sleutels[i] = sleutels[i - 1];
            data[i] = data[i - 1];
        }

        sleutels[i] = sleutel;
        data[i] = waarde;

        aantalSleutels++;
    }

    /**
     * Verwijder de sleutel en data op de opgegeven index
     */
    void verwijder(int index) {
        assert(index < aantalSleutels);
        for (int i = index + 1; i < aantalSleutels; i++) {
            sleutels[i - 1] = sleutels[i];
            data[i - 1] = data[i];
        }
        aantalSleutels--;
    }

    unique_ptr<Data> geefData(Sleutel sleutel){
        int sleutel_index = 0;
        for (; sleutel_index < aantalSleutels && sleutels[sleutel_index] < sleutel; sleutel_index++) {
        }

        if (sleutel_index < aantalSleutels && sleutels[sleutel_index] == sleutel) {
            unique_ptr<Data> d = make_unique<Data>(data[sleutel_index]);
            return d;
        }else{
            return {};
        }
    }

    /**
     * Zoek de gegeven sleutel in de pagina en verwijder indien gevonden
     */
    unique_ptr<Data> verwijder(Sleutel sleutel) {

        int sleutel_index = 0;
        for (; sleutel_index < aantalSleutels && sleutels[sleutel_index] < sleutel; sleutel_index++) {
        }

        if (sleutel_index < aantalSleutels && sleutels[sleutel_index] == sleutel) {
            unique_ptr<Data> d = make_unique<Data>(data[sleutel_index]);
            verwijder(sleutel_index);

            return d;
        }
        return nullptr;
    }

    /**
     * Deze functie verhoogt de `pagina_diepte` met 1 en splitst hierbij de 
     * pagina in tweeën. 
     */
    Pagina<Sleutel, Data, orde> splits() {
        Pagina<Sleutel, Data, orde> nieuwePagina;
        pagina_diepte++;
        nieuwePagina.pagina_diepte = pagina_diepte;
        for (int i = 0; i<aantalSleutels; i++)
        {
            Sleutel sleutel = sleutels[i];
            if(geef_deel_van_hash(sleutel, pagina_diepte) >> (pagina_diepte-1) == 0b0001)
            {
                nieuwePagina.voegtoe(sleutel, *geefData(sleutel));
                verwijder(sleutel);
            }
        }
        return nieuwePagina;
    }
};