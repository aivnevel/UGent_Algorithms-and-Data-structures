#ifndef __SCHIJF
#define __SCHIJF
#include <map>
#include <iostream>
using std::map;
typedef unsigned int BlokIndex;

//naamgeving gaat uit van de gebruiker: schrijf is een schrijfoperatie naar
//de schijf, enzovoorts
template <class Pagina>
class Schijf : private map<BlokIndex, Pagina>
{
public:
    /**
     * Schrijf een nieuwe pagina weg naar de schijf.
     * 
     * @returns de nieuwe BlokIndex voor de aangemaakte pagina
     */
    BlokIndex schrijf(const Pagina &p)
    {
        ++indexteller;
        this->operator[](indexteller) = p; //this-> is nodig (bij sommige compilers) omdat de parametrisatie niet afgeleid kan worden uit de argumenten.
        return indexteller;
    }

    /**
     * Verwijder de pagina met opgegeven BlokIndex
     */
    void verwijder(BlokIndex bi)
    {
        this->erase(bi);
    }

    /**
     * Verander de data opgeslagen in de pagina op de schijf
     */
    void herschrijf(const Pagina &p, const BlokIndex bi)
    {
        this->operator[](bi) = p;
    }

    /**
     * Lees de pagina met de overeenkomstige blokindex van de schijf
     */
    Pagina lees(const BlokIndex bi)
    {
        return this->operator[](bi);
    }

    //constructor
    Schijf() : map<BlokIndex, Pagina>(), indexteller(0){};

private:
    //teller die het aantal toegevoegde elementen op de schijf zal tellen, merk op dat na verwijderen er ook "lege" indexen op de schijf zullen zijn.
    BlokIndex indexteller;
};

#endif
