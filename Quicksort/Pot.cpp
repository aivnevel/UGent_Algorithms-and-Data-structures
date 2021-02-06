#include "Pot.h"
#include <iostream>
#include <iomanip>

Pot::Pot(int x): Voorwerp(x) {
    //met static blijft de id verder optellen
    //hier, in dit geval, als unieke id, krijgt Pot oneven getallen
    static int id = 1;
    (*this).setIdentifier(id);
    //stel de volgende id in
    id+=2;
}
