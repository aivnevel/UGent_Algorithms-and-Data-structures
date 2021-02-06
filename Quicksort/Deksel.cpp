#include "Deksel.h"
#include <iostream>
#include <iomanip>

Deksel::Deksel(int x): Voorwerp(x) {
    //met static blijft de id verder optellen
    //hier, in dit geval, als unieke id, krijgt deksel even getallen
    static int id = 0;
    (*this).setIdentifier(id);
    //stel de volgende id in
    id+=2;
}
