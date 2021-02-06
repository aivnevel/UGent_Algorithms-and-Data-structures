#ifndef __RZWboom_H
#define __RZWboom_H

#include <cassert>
#include <fstream>
#include <sstream>
#include <functional>
#include <iostream>
#include <memory>

using std::string;
using std::ostream;
using std::ostringstream;


enum RZWkleur {
    rood,
    zwart
};

template <class Sleutel>
class RZWknoop;

/**
 * Binaire RZWboom waarin geen duplicaatsleutels zijn toegestaan.
 */
template <class Sleutel>
class RZWboom : public std::unique_ptr<RZWknoop<Sleutel>> {
  public:
    using std::unique_ptr<RZWknoop<Sleutel>>::unique_ptr;

    RZWboom(std::unique_ptr<RZWknoop<Sleutel>> &&a);
    RZWboom() : std::unique_ptr<RZWknoop<Sleutel>>(){};

    void inorder(std::function<void(const RZWknoop<Sleutel> &)> bezoek) const;
    void schrijf(std::ostream &os) const;
    void tekenAlsBinaireBoom(const char *bestandsnaam) const;
    string tekenrecBinair(ostream &uit, int &nullteller) const;
    RZWboom<Sleutel> *geefBoomBovenKnoop(RZWknoop<Sleutel> &knoop); // oproepen op wortel
    void roteer(bool naarlinks);
    int geefDiepte() const;
    RZWkleur geefKleur() const; 
    void zetKleur(RZWkleur kl);

    void voegtoe_topdown(const Sleutel &sleutel);
};

template <class Sleutel>
void RZWboom<Sleutel>::voegtoe_topdown(const Sleutel &sleutel) {
    auto loper = this;
    RZWknoop<Sleutel>* ouder = nullptr;
    while(*loper) {
        if((*loper)->links && (*loper)->rechts && (*loper)->links.geefKleur() == rood && (*loper)->rechts.geefKleur() == rood) {
            (*loper)->links.zetKleur(zwart);
            (*loper)->rechts.zetKleur(zwart);
            loper->zetKleur(rood);
        }
        if((*loper)->ouder && (*loper)->ouder->kleur == rood && (*loper)->kleur == rood) {
            auto loperLinks = (*loper)->ouder->links == *loper;
            if((*loper)->ouder->ouder && (*loper)->ouder->ouder->geefKind(loperLinks) && (*loper)->ouder->ouder->geefKind(loperLinks)->geefKind(loperLinks) && (*loper)->ouder->ouder->geefKind(loperLinks)->geefKind(loperLinks) != *loper){
                geefBoomBovenKnoop(*(*loper)->ouder)->roteer(loperLinks);
                geefBoomBovenKnoop(*(*loper)->ouder)->roteer(!loperLinks);
                loper->zetKleur(zwart);
                (*loper)->geefKind(!loperLinks).zetKleur(rood);
            } else {
                geefBoomBovenKnoop(*(*loper)->ouder->ouder)->roteer(!loperLinks);
                (*loper)->ouder->geefKind(!loperLinks).zetKleur(rood);
                (*loper)->ouder->kleur = zwart;
            }
        }
        ouder = loper->get();
        loper = &((*loper)->geefKind((*loper)->sleutel > sleutel));
    }
    loper->reset(new RZWknoop<Sleutel>(sleutel));
    (*loper)->ouder = ouder;
    zetKleur(zwart);
}

template <class Sleutel>
RZWboom<Sleutel>::RZWboom(std::unique_ptr<RZWknoop<Sleutel>> &&a) : std::unique_ptr<RZWknoop<Sleutel>>(move(a)) {}

template <class Sleutel>
void RZWboom<Sleutel>::inorder(std::function<void(const RZWknoop<Sleutel> &)> bezoek) const {
    if (*this) {
        (*this)->links.inorder(bezoek);
        bezoek(**this);
        (*this)->rechts.inorder(bezoek);
    };
}

template <class Sleutel>
void RZWboom<Sleutel>::schrijf(std::ostream &os) const {
    inorder([&os](const RZWknoop<Sleutel> &knoop) {
        os << "(" << knoop.sleutel << " ";
        if (knoop.kleur == rood)
            os << "rood";
        else {
            os << "zwart";
        }
        os << ")";
        os << "\n  Linkerkind: ";
        if (knoop.links)
            os << knoop.links->sleutel;
        else
            os << "-----";
        os << "\n  Rechterkind: ";
        if (knoop.rechts)
            os << knoop.rechts->sleutel;
        else
            os << "-----";
        os << "\n";
    });
}

template <class Sleutel>
void RZWboom<Sleutel>::tekenAlsBinaireBoom(const char *bestandsnaam) const {
    std::ofstream uit(bestandsnaam);
    assert(uit);
    int nullteller = 0; //nullknopen moeten een eigen nummer krijgen.
    uit << "digraph {\n";
    this->tekenrecBinair(uit, nullteller);
    uit << "}";
}

template <class Sleutel>
string RZWboom<Sleutel>::tekenrecBinair(ostream &uit, int &nullteller) const
{
    ostringstream wortelstring;
    if (!*this)
    {
        wortelstring << "null" << ++nullteller;
        uit << wortelstring.str() << " [shape=point];\n";
    }
    else
    {
        wortelstring << '"' << (*this)->sleutel << '"';
        uit << wortelstring.str() << "[label=\"" << (*this)->sleutel << "\"]";
        if (this->geefKleur() == rood)
            uit << "[color=red]";
        uit << ";\n";
        string linkskind = (*this)->links.tekenrecBinair(uit, nullteller);
        string rechtskind = (*this)->rechts.tekenrecBinair(uit, nullteller);
        uit << wortelstring.str() << " -> " << linkskind << ";\n";
        uit << wortelstring.str() << " -> " << rechtskind << ";\n";
    };
    return wortelstring.str();
}


template <class Sleutel>
RZWboom<Sleutel> *RZWboom<Sleutel>::geefBoomBovenKnoop(RZWknoop<Sleutel> &knoop) {
    if (knoop.ouder == 0)
        return this; //wortel teruggeven als er geen ouder is
    else if (knoop.ouder->links.get() == &knoop)
        return &(knoop.ouder->links);
    else
        return &(knoop.ouder->rechts);
};

template <class Sleutel>
int RZWboom<Sleutel>::geefDiepte() const {
    if (!(*this))
        return 0;
    return 1 + std::max((*this)->links.geefDiepte(), (*this)->rechts.geefDiepte());
}

//preconditie: wortel en nodige kind bestaan
template <class Sleutel>
void RZWboom<Sleutel>::roteer(bool naarLinks) {
    RZWboom<Sleutel> kind = move((*this)->geefKind(!naarLinks));
    //beta verhangen
    (*this)->geefKind(!naarLinks) = move(kind->geefKind(naarLinks));
    //wortel verhangen
    kind->geefKind(naarLinks) = move(*this);
    //kind verhangen
    *this = move(kind);
    //ouderpointers goed zetten
    (*this)->ouder = (*this)->geefKind(naarLinks)->ouder;
    (*this)->geefKind(naarLinks)->ouder = this->get();
    if ((*this)->geefKind(naarLinks)->geefKind(!naarLinks)) //alpha niet leeg
        (*this)->geefKind(naarLinks)->geefKind(!naarLinks)->ouder = (*this)->geefKind(naarLinks).get();
};

template <class Sleutel>
void RZWboom<Sleutel>::zetKleur(RZWkleur kleur) {
    assert(*this);
    (*this)->kleur = kleur;
};

template <class Sleutel>
RZWkleur RZWboom<Sleutel>::geefKleur() const {
    if (*this)
        return (*this)->kleur;
    else {
        return zwart;
    }
}

#endif
