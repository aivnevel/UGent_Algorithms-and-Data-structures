#ifndef VOORWERP_HPP
#define VOORWERP_HPP
#include <iostream>
using std::ostream;

class Voorwerp {
private:
    int diameter;
    int identifier;
public:
    //constructor
    Voorwerp(const int x);
    
    //comparators overloaden
    bool operator==(const Voorwerp &) const;
    bool operator<(const Voorwerp &) const;
    bool operator>(const Voorwerp &) const;
    
    //getters en setters voor diameter en identifier
    int getDiameter() const;//const betekent hier dat functie niets zal overschrijven
    int getIdentifier() const;//const betekent hier dat functie niets zal overschrijven
    void setIdentifier(int x);
    
    //ostream overloaden, om een Voorwerp te kunnen printen in de vorm van std::cout<<Voorwerp;
    friend ostream& operator<<(ostream& os, const Voorwerp&);
};

#endif
