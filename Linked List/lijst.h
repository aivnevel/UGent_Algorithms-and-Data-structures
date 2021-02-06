//C++17-compatibele lijst. Ontbrekende elementen: move en copy, iterator
#ifndef __LIJST_H
#define __LIJST_H

//
// speciale code voor debuggen
//
#define DEBUG

//
//speciale code voor iteratoren
//
#define ITERATOR

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using std::endl;
using std::ofstream;
using std::ostream;
using std::string;

template <class T>
class Lijstknoop;
template <class T>
class Lijst;

template <class T>
using Lijstknoopptr = std::unique_ptr<Lijstknoop<T>>;
template <class T>
ostream& operator<<(ostream&, const Lijst<T>&);

template <class T>
class Lijst : private Lijstknoopptr<T>
{
public:
    //toekenning, constructoren
    //overname constructoren van unique_ptr

    using std::unique_ptr<Lijstknoop<T>>::operator=;
    using std::unique_ptr<Lijstknoop<T>>::swap;

    Lijst() = default;
    Lijst(const Lijst&);
    Lijst(Lijst&&);
    Lijst& operator=(const Lijst&);
    Lijst& operator=(Lijst&&);
    virtual ~Lijst() = default;

    //operaties
    //duplicaten zijn toegelaten.

    void voegToe(const T&);
    //geefaantal geeft het aantal keer dat de sleutel voorkomt.
    //gebruikt de zoekfunctie om door de lijst te lopen!
    //zonder argument: geef lengte lijst
    int geefAantal(const T&) const;
    int geefAantal() const;
    //verwijder verwijdert slechts het eerste exemplaar met de gegeven
    //T, en geeft geen fout als de T niet gevonden wordt.
    //gebruik de zoekfunctie om door de lijst te lopen!
    void verwijder(const T&);
    //verwijder eerste knoop.
    void verwijderEerste();    
    bool isClone(const Lijst<T>&) const;
    void applySocialDistancing(const T&, const T&);
    
    //uitschrijf- en tekenoperaties
    //dotformaat:

    void teken(const char*) const;
    //uitschrijven: voor elke knoop de T-waarde, gescheiden door komma's
    friend ostream& operator<<<>(ostream&, const Lijst&);
    void schrijf(ostream&) const;

    //iterator; gaat ervan uit dat alles const is
    class iterator
    {
    private:
        Lijstknoop<T>* lkptr;

    public:
        iterator(Lijstknoop<T>* lkptr = nullptr);

        const T& operator*() const;
        const iterator& operator++();
        bool operator==(const iterator&);
        bool operator!=(const iterator&);
    };

    iterator begin() const;
    iterator end() const;

protected:
    // zoek geeft een pointer naar de Lijst die de sleutelwaarde bevat,
    // en geeft een pointer naar de lege lijst op het einde als de sleutel niet
    // voorkomt.
    const Lijst* zoek(const T&) const;
    Lijst* zoek(const T&);
    //preconditie zoekgesorteerd: lijst is gesorteerd
    //teruggeefwaarde: wijst naar Lijst waar sleutel staat/zou moeten staan.
    Lijst<T>* zoekGesorteerd(const T& sleutel);
};

template <class T>
class Lijstknoop
{
    friend class Lijst<T>;
    friend ostream& operator<<<>(ostream&, const Lijst<T>&);

public:
    Lijst<T> volgend;
    Lijstknoop(const T&);
#ifdef DEBUG
    ~Lijstknoop();
#endif
protected:
    T sleutel;
#ifdef DEBUG
public:
    static bool controle(int, int);

protected:
    static int aantalGemaakt;
    static int aantalVerwijderd;
#endif
};

template <class T>
int Lijstknoop<T>::aantalGemaakt = 0;
template <class T>
int Lijstknoop<T>::aantalVerwijderd = 0;

////////////////////////////////////////////////////////////////////////////////

template <class T>
Lijst<T>::Lijst(const Lijst& andere)
{
    if (this == &andere)
    {
        return;
    }

    const Lijst* it_andere = &andere;
    Lijst* it_this = this;

    while (it_andere && *it_andere)
    {
        *it_this = std::make_unique<Lijstknoop<T>>((*it_andere)->sleutel);

        it_andere = &((*it_andere)->volgend);
        it_this = &((*it_this)->volgend);
    }
}

template <class T>
Lijst<T>::Lijst(Lijst&& andere) : std::unique_ptr<Lijstknoop<T>>{std::move(andere)}
{
}

template <class T>
Lijst<T>& Lijst<T>::operator=(const Lijst& andere)
{
    if (this != &andere)
    {
        Lijst temp{andere};
        swap(temp);
    }

    return (*this);
}

template <class T>
Lijst<T>& Lijst<T>::operator=(Lijst&& andere)
{
    // swap(andere); // of
    // this->reset(andere.release()); // of
    std::unique_ptr<Lijstknoop<T>>::operator=(std::move(andere));

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
Lijst<T>::iterator::iterator(Lijstknoop<T>* lkptr) : lkptr{lkptr}
{
}

template <class T>
const T& Lijst<T>::iterator::operator*() const
{
    return lkptr->sleutel;
}

template <class T>
const typename Lijst<T>::iterator& Lijst<T>::iterator::operator++()
{
    lkptr = (lkptr->volgend).get();

    return *this;
}

template <class T>
bool Lijst<T>::iterator::operator==(const iterator& andere)
{
    return (lkptr == andere.lkptr);
}

template <class T>
bool Lijst<T>::iterator::operator!=(const iterator& andere)
{
    return !(*this == andere);
}

template <class T>
typename Lijst<T>::iterator Lijst<T>::begin() const
{
    return iterator(this->get());
}

template <class T>
typename Lijst<T>::iterator Lijst<T>::end() const
{
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
Lijstknoop<T>::Lijstknoop(const T& _sl) : sleutel(_sl)
{
    //    std::cerr<<"Knoop met sleutel "<<sleutel<<" wordt gemaakt\n";
    aantalGemaakt++;
}
#ifdef DEBUG

template <class T>
Lijstknoop<T>::~Lijstknoop()
{
    //    std::cerr<<"Knoop met sleutel "<<sleutel<<" wordt verwijderd\n";
    aantalVerwijderd++;
}
template <class T>
bool Lijstknoop<T>::controle(int gemaakt, int verwijderd)
{
    if (aantalGemaakt == gemaakt && aantalVerwijderd == verwijderd)
        return true;
    else
    {
        std::cerr << "Fout bij controle:\n";
        std::cerr << "Aantal gemaakte knopen   : " << aantalGemaakt << " (moet zijn: " << gemaakt << ")\n";
        std::cerr << "Aantal verwijderde knopen: " << aantalVerwijderd << " (moet zijn: " << verwijderd << ")\n";
        throw "Mislukte controle";
    };
};
#endif

template <class T>
ostream& operator<<(ostream& os, const Lijst<T>& l)
{
#ifdef ITERATOR
    for (auto&& sleutel : l)
        os << sleutel << ", ";
#else
    if (l.get())
    {
        os << l.get()->sleutel << ", ";
        os << l.get()->volgend;
    }
#endif
    return os;
}

template <class T>
void Lijst<T>::schrijf(ostream& os) const
{
#ifdef ITERATOR
    if (this->get() != 0)
    {
        os << this->get()->sleutel;
        std::for_each(++begin(), end(), [&](const T& sleutel) { os << " . " << sleutel; });
    }
#else
    {
        Lijstknoop<T>* kn = this->get();
        if (kn != 0)
        {
            os << kn->sleutel;
            kn = kn->volgend.get();
        };
        while (kn != 0)
        {
            os << " . " << kn->sleutel;
            kn = kn->volgend.get();
        };
    }
#endif
}
//oplossing:

template <class T>
bool Lijst<T>::isClone(const Lijst<T>& ander) const
{
    const Lijst<T>*l1 = this, *l2 = &ander; //twee lopers
    while (*l1 && *l2 && (*l1)->sleutel == (*l2)->sleutel)
    {
        l1 = &((*l1)->volgend);
        l2 = &((*l2)->volgend);
    };
    return (!(*l1) && !(*l2));
};

template <class T>
const Lijst<T>* Lijst<T>::zoek(const T& sleutel) const
{
    const Lijst<T>* pl = this;
    while (*pl && pl->get()->sleutel != sleutel)
        pl = &(pl->get()->volgend);
    return pl;
}

template <class T>
int Lijst<T>::geefAantal(const T& sleutel) const
{
    int aantal = 0;
    const Lijst<T>* pl = this;
    while (*pl)
    {
        if (sleutel == (*pl)->sleutel)
            ++aantal;
        pl = &(pl->get()->volgend);
    };
    return aantal;
};

template <class T>
int Lijst<T>::geefAantal() const
{
    int aantal = 0;
    const Lijst<T>* pl = this;
    while (*pl)
    {
        ++aantal;
        pl = &(pl->get()->volgend);
    };
    return aantal;
};

template <class T>
Lijst<T>* Lijst<T>::zoek(const T& sleutel)
{
    Lijst* pl = this;
    while (*pl && pl->get()->sleutel != sleutel)
        pl = &(pl->get()->volgend);
    return pl;
}

template <class T>
void Lijst<T>::voegToe(const T& sleutel)
{
    Lijstknoopptr<T> nieuw = std::make_unique<Lijstknoop<T>>(sleutel);
    Lijstknoopptr<T>::swap(nieuw->volgend);
    *this = std::move(nieuw);
}

template <class T>
void Lijst<T>::verwijderEerste()
{
    if (this->get() != 0)
    {
        Lijstknoopptr<T> staart(std::move(this->get()->volgend));
        this->reset();
        Lijstknoopptr<T>::swap(staart);
    }
}

template <class T>
void Lijst<T>::verwijder(const T& sleutel)
{
    zoek(sleutel)->verwijderEerste();
}

template <class T>
Lijst<T>* Lijst<T>::zoekGesorteerd(const T& sleutel)
{
    Lijst* plaats = this;
    while (*plaats && plaats->get()->sleutel < sleutel)
        plaats = &plaats->get()->volgend;
    return plaats;
};

template <class T>
void Lijst<T>::teken(const char* bestandsnaam) const
{
    ofstream uit(bestandsnaam);
    assert(uit);
    uit << "digraph {\nrankdir=\"LR\";\n\"0\"[label=\"\",shape=diamond];\n\"0\" -> \"1\";\n";
    int knoopteller = 1; //knopen moeten een eigen nummer krijgen.
    const Lijst<T>* loper = this;
    while (*loper)
    {
        uit << "subgraph cluster_" << knoopteller << " {\nrankdir=\"LR\";\n";
        uit << "\"" << knoopteller << "\" [label=\"" << (*loper)->sleutel << "\",color=white];\n";
        uit << "\"" << knoopteller << "v\" [shape=diamond,label=\"\"];\n";
        uit << "\"" << knoopteller << "\" -> \"" << knoopteller << "v\" [color=white];\n";

        uit << "}\n";
        uit << "\"" << knoopteller << "v\" -> \"" << knoopteller + 1 << "\" [lhead=cluster_" << knoopteller
            << " ltail=cluster_" << knoopteller + 1 << "];\n";
        loper = &((*loper)->volgend);
        knoopteller++;
    };
    uit << "\"" << knoopteller << "\" [shape=point];\n";
    uit << "}";
};

int berekenOverlap(int min, int tweedeMin, int max, int tweedeMax, int N){
    //geval 1: loper 1 stopt 1 té vroeg om te voorkomen dat tweedeLoper crasht (omdat tweedeLoper de opvolger is van loper)
    if(tweedeMin<= min + N && tweedeMin >= max - N &&
       tweedeMax<= min + N && tweedeMax >= max - N)
        return 0;
    //geval 2: de tweede lijst zijn minimum ligt binnen het interval van de eerste lijst zijn min,max
    else if(tweedeMin > min &&
            tweedeMin < max)
        return max-tweedeMin+1; // 7 - 6 = 1 => overlap is eigenlijk 2 dan, dus 1 optellen
    //geval 3: de tweede lijst zijn maximum ligt binnen het interval van de eerste lijst zijn min,max
    else if (tweedeMax > min &&
             tweedeMax < max)
        return tweedeMax-min+1;
    //geval 4: geen overlap
    return 1;
}

template <class T>
void Lijst<T>::applySocialDistancing(const T& N, const T& isolationKey){
    //controleer of er in de lijst getallen zitten, indien niet dan zou het programma crashen
    if(*this){
        
        Lijst<T> *loper = this, *tweedeLoper = this;
        
        /*
         initialiseer min en max met de sleutel van de startpositie (anders zou deze in de eerste iteratie leeg zijn) => hiervoor is er geval 1 in de functie 'berekenOverlap'
            
         */
        int min = (*loper)->sleutel;
        int max = (*loper)->sleutel;
        
        while(*loper){
            /*
             
             startpositie voor het bereik van de eerstesublijst start op het eerste element, deze verder ontwikkelen in de eerstvolgende while-loop
             */
            int tweedeMin = (*loper)->sleutel;
            int tweedeMax = (*loper)->sleutel;
            
            /*
             
            1.    controleer of de volgende van de volgende bestaat,
                  indien niet dan moet de while-lus stoppen aangezien er geen opvolgend element meer is
            
            2.    eerste subrij max en min bepalen
                  sleutel is oke als het huidige minimum bereik + N groter is of gelijk aan de huidige sleutel
                  en ook moet het huidige maximum bereik - N kleiner zijn of gelijk aan de huidige sleutel
            */
            while((*loper)->volgend &&
                  (*loper)->volgend->sleutel <= tweedeMin + N &&
                  (*loper)->volgend->sleutel >= tweedeMax - N){
                
                //indien de sleutel groter was dan max
                if((*loper)->volgend->sleutel > tweedeMax)
                    tweedeMax = (*loper)->volgend->sleutel;
                
                //dezelfde redenering als hierboven maar dan voor minimum
                else if((*loper)->volgend->sleutel < tweedeMin)
                    tweedeMin = (*loper)->volgend->sleutel;
                
                //verschuif loper vooruit, dit is zeker oke want dit werd in de while loop gechecked
                loper = &((*loper)->volgend);
            }
            
            /*
                hulpfunctie, aantal lijnen code verminderen
             */
            int overlap = berekenOverlap(min, tweedeMin, max, tweedeMax, N);
            
            for(int i=0; i<overlap; i++){
                tweedeLoper = &((*tweedeLoper)->volgend);
                /*
                 naive oplossing: achteraan toevoegen
                            hierdoor zal je elke sublijst 2x moeten overlopen, aangezien je steeds tweedeLoper verloor omdat je achteraan toevoegt (unique_ptr 'tweedeLoper' zal resetten dan)
        
                 optimalisatie: vooraan toevoegen
                    door vooraan toe te voegen heeft de unique_ptr 'tweedeLoper',die verder in de lijst staat, geen last van de verplaatsingen, die vooraan gebeuren
                 
                 */
                tweedeLoper->voegToe(isolationKey);
            }
            /*
             
             uitleg:
                tweedeLoper moet wijzen naar de huidige locatie van loper (het einde van de net afgehandelde sublijst): in de volgende stap wordt deze locatie gebruikt om 0'en in te vullen
             
                loper moet nu wijzen naar de start van de volgende sublijst,
                loper zit momenteel aan het einde van een sublijst dus als deze 1 opschuift staat hij in de volgende sublijst of:
                    stel dat er geen volgende sublijst meer is dan stopt de while loop,
                      ----
                        het is niet erg dat de loper dan staat op het element na het laatste element aangezien dit element OOK bestaat
                            (bewijs hiervoor is dat alle elementen een Lijst bevatten dus ook het laatste element)
                            !MAAR: het element NA het laatste element zijn volgend is niet ingevuld EN, zijn sleutel is ook NIET ingevuld!
                      ----
             */
            tweedeLoper = loper;
            loper = &((*tweedeLoper)->volgend);
            
            /*
             
             tweedeMin en tweedeMax doorgeven aan min en max, om hierop de overlap te berekenen in de volgende iteratie
             */
            min = tweedeMin;
            max = tweedeMax;
        }
    }
}


#endif
