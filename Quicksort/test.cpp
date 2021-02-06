#include "Matcher.h"
#include <vector>
#include <random>
#include <iostream>
#include <utility>

void vulVectoren(const std::vector<int>& diameters, std::vector<Deksel>& deksels, std::vector<Pot>& potjes){    
    for(const int& x : diameters){
        deksels.push_back(Deksel(x));        
        potjes.push_back(Pot(x));
    }
    std::mt19937 eng{std::random_device{}()};    
    std::shuffle(deksels.begin(),deksels.end(),eng);

    //reseed
    std::mt19937 eng2{std::random_device{}()};    
    std::shuffle(potjes.begin(),potjes.end(),eng2);
}

int main(){
    /*
     ## ONTWERP
     Deksels sorteren adhv pot pivot en Potten sorteren adhv deksel pivot
     => pivot bepalen en deze meegeven als pivot aan Pot
     vectors sorteren op basis van 3-way quicksort: verdeel de vectoren in 3 delen
        v[l..i] kleiner dan de pivot.
        v[i+1..j-1] gelijk aan de pivot.
        v[j..r] groter dan de pivot.
     i en j duiden de grenzen aan van alle elementen die mogen gebruikt worden als pivot
     in het algoritme neem ik i+1, maar j-1 zou evengoed zijn.
     
     ## ALGORITME
        1. Stop de iteratie als l >= r (iteratie is compleet als l => r)
     
        2. Partioneer + bereken een index pivot uit deksel adhv p[r], r is de meest rechtse index en p stelt de potjes voor
            pivot = partition(d, l, r, i, j, p[r]);
     
        3. Gebruik deze pivot van deksel om nu potjes te partioneren
            partition(p, l, r, i_2, j_2, d[pivot]);
        4. Voor dit nu recursief uit, voor alle elementen kleiner dan de pivot vector[l..i]
                                    en voor alle elementen  groter dan de pivot vector[j..r]
     ## PARTITIONEREN
        
        5. Indien l en r naast elkaar staan, (of gelijk zijn) (r - l <= 1)
            dan moet je nog enkel checken of deze 2 elementen op de goede plaats staan, indien niet dan swap je ze nog en zal deze iteratie compleet zijn l wordt gelijk gesteld aan i en r wordt gelijkgesteld aan j, als quicksort(..) wordt opgeroepen dan zal i==l en j==r de check in het begin van quicksort zal ervoor zorgen dat deze iteratie hier compleet is
     
        6. Initialiseer m, die het midden aangeeft, initieel staat deze zo links mogelijk (m=l)
            zolang deze kleiner (of gelijk is aan r) dan gaat de lus door,
                elementen die kleiner zijn dan de pivot, worden geswapt met l en l 1 plaats vooruit geschoven, aangezien het element waar l op stond nu zeker kleiner is dan de pivot
                elementen die gelijk zijn aan de pivot die worden overgeslaan (m++)
                elementen die groter zijn dan de pivot die worden naar rechts geswapt (naar r), r wordt 1 naar links geschoven, omdat het element in r nu zeker goed staat
        7. i en j updaten met nu de waardes die de grenzen aanduiden (dit kan omdat i en j 'by reference' zijn meegegeven) i = l-1;  j = m;
     
     ## EXTRA
        in de MATCHER klasse staat de code, voor elke lijn becommentarieert
            
     */

    std::vector<int> diameters {1, 1, 2, 3, 4, 4, 4, 5, 6, 6, 7, 8, 8, 9, 9, 10};
    std::vector<Deksel> deksels;
    std::vector<Pot> potjes;
    vulVectoren(diameters, deksels, potjes);
    std::vector<std::pair<Deksel,Pot>> paren = Matcher::match(deksels,potjes);
    
    std::cout << "OK" << std::endl;
    return 0;
}
