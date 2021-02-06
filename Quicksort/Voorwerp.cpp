#include "Voorwerp.hpp"
#include <iomanip>
#include <iostream>

Voorwerp::Voorwerp(int x){
    diameter = x;
}

//operators implementeren
bool Voorwerp::operator<(const Voorwerp& voorwerp) const {
    return diameter<voorwerp.diameter;
}

bool Voorwerp::operator==(const Voorwerp & voorwerp) const {
    return diameter==voorwerp.diameter;
}

bool Voorwerp::operator>(const Voorwerp & voorwerp) const {
    return diameter>voorwerp.diameter;
}

//getters voor de tabelformattering
int Voorwerp::getDiameter() const {
    return diameter;
}

//getters voor de tabelformattering
int Voorwerp::getIdentifier() const {
    return identifier;
}

//setter om identifier te kunnen instellen in de kind-klassen
void Voorwerp::setIdentifier(int x) {
    identifier = x;
}

//operator<< overloaden zodat hiermee een Voorwerp uitgeprint kan worden
ostream& operator<<(ostream& os, const Voorwerp& v) {
    os << v.diameter << '\\' << v.identifier << " ";
    return os;
}




