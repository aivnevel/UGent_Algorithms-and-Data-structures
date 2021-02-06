#include "Matcher.h"
#include <iostream>
using std::swap;
using std::cout;
using std::endl;
using std::make_pair;

//2x template class, helaas is het niet mogelijk om het type van de ouderklasse te gebruiken, het is niet omdat vector<ouder> in de parameterlijst staat dat je vector<kind> mag meegeven.. , wat wel zou mogen is het ouder type als parameter en het kind type meegeven. Echter is dit hier niet bruikbaar
template<typename D, typename P>
void quicksort(vector<D>& d, vector<P>& p){
    quicksort(d,p,0,(int)d.size()-1);
    cout<<endl;
}

template<typename D, typename P>
void quicksort(vector<D>& d, vector<P>& p, int l, int r){
    //zolang linker index van potjes kleiner blijft dan rechterindex van potjes moet je verder gaan
    if (l >= r){
        return;
    }
    //
    //i(_2) en j(_2) duiden respectivelijk het begin en het einde van de middelste groep aan
    //              > i en j voor deksels,
    //              > i_2 en j_2 voor potjes
    int i, j, i_2, j_2, pivot;
    //zoek een index van een element uit het tweede deel (linkse i +1 bv.), dit is de nieuwe pivot
    pivot = partition(d, l, r, i, j, p[r]);
    
    //indien het rechtse element - het linkerelement kleiner is dan 0 dan moet je niet verder de recursie uitvoeren
    //nadat je deksels gepartioneert hebt, moet je ook potjes partioneren, nu adhv een pivot van deksel
    partition(p, l, r, i_2, j_2, d[pivot]);
    
    //opsplitsen in 3 stukken: kleiner dan de pivot: [l,i], gelijk aan de pivot: [i,j] , groter dan de pivot: [j,r]
    quicksort(d, p, l, i);
    quicksort(d, p, j, r);
    cout<<".";
}

//partitioneer in 3 stukken:
//een linkerdeel
template<typename A,typename B>
int partition(vector<A>& s, int l, int r, int& i, int& j, B pivot){
    
    //indien (rechter wijzer - linker wijzer) kleiner is of gelijk aan 1, kunnen er nog 2 elementen zijn die eventueel gewisseld moeten worden, erna moet de iteratie stoppen
    if (r - l <= 1){
        //laatste stap: controleer of rechter element kleiner is dan het linkerelement en wissel ze met elkaar als dat zo is
        if (s[r] < s[l]){
            swap(s[r], s[l]);
        }
        //i wordt het linkerelement en j het rechter element:
        //zet i en j op dezelfde plaatsen als l en r, gevolg zal zijn: als ze meegegeven worden aan de volgende iteratie van quicksort,
        //  dan wordt i en l met elkaar vergeleken en j en r met elkaar vergeleken:
        //  Ze zijn beide gelijk dus stopt de iteratie
        i = l;
        j = r;
    } else {
        //start met middelste wijzer helemaal links te zetten
        int m = l;
        //zolang middelste wijzer kleiner is dan de rechter wijzer dan
        // kunnen er nog elementen in staan die kleiner zijn dan de pivot
        // of elementen die groter zijn dan de pivot: blijf verder zoeken
        while (m <= r) {
            //als het element waar m op staat kleiner is dan de pivot dan breng je dit element naar het linkerdeel
            if (s[m]<pivot) {
                //wissel het element waar m op staat met het element waar l op staat, en schuif beiden 1 naar voor
                swap(s[l++], s[m++]);
            }
            //indien m op een element staat dat gelijk is aan de pivot,
            //mag deze blijven staan en verschijft hij de loper m met één vooruit
            else if (s[m]==pivot) {
                m++;
            }
            //indien m op een waarde staat dat groter is dan de pivot dan breng je dit element naar het rechterdeel,
            //het element waar de rechterwijzer naar wees is nu zeker dat deze groter is dan de pivot,
            //dus deze mag 1 stap dichter komen naar de pivot
            else if (s[m]>pivot) {
                swap(s[m], s[r--]);
            }
        }
        //verzet i en j nu naar de plaats waar l gestopt is (-1)
        i = l-1;
        //en verzet j naar waar m stond
        j = m;
        //=> i en j duiden nu de grenzen aan van het tweede deel: binnen [i+1,j-1] zijn alle diameters gelijk
    }
    //return de index van een element van de tweede groep, alles binnenhet bereik van [i+1,j-1] zit in de tweede groep (zijn dus gelijk)
    return i+1;
}

vector<pair<Deksel,Pot>> Matcher::match(const vector<Deksel>& v_dek, const vector<Pot>& v_pot){
    //maak een object aan om paren in te steken
    vector<pair<Deksel,Pot>> vec;
    
    //maak een deksels object aan om alle deksels uit de const te kopieren (gegeven is een const)
    vector<Deksel> deksels(v_dek);
    
    //maak een potjes object aan om alle potjes uit de const te kopieren (gegeven is een const)
    vector<Pot> potjes(v_pot);
    
    cout<<"deksels-pre: diamteter\\identifier"<<endl;
    for(auto x : deksels){
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<"potjes-pre: diamteter\\identifier"<<endl;
    for(auto x : potjes){
        cout<<x<<" ";
    }
    cout<<endl<<endl;
    cout<<"3-way quicksort"<<endl;
    
    //run quicksort
    quicksort(deksels,potjes);
    
    cout<<"quicksort klaar"<<endl<<endl;
    cout<<"deksels-post: diamteter\\identifier"<<endl;
    for(auto x : deksels){
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<"potjes-post: diamteter\\identifier"<<endl;
    for(auto x : potjes){
        cout<<x<<" ";
    }
    cout<<endl;
    for (int i = 0; i<v_dek.size(); i++) {
        vec.push_back(make_pair(deksels[i], potjes[i]));
    }
    /*
     
     formattering voor vergelijkingstabel weer te geven, deze controleert of het algoritme werkt
     */
    cout<<endl<<"koppels: "<<endl;
    cout<<"\t\t _______________________________________________________"<<endl;
    cout<<"\t\t|Deksel D"<<"\t|Deksel ID"<<"\t|Pot D"<<"\t\t|Pot ID"<<"\t\t|match ?|"<<endl;
    cout<<"\t\t|-------------------------------------------------------|"<<endl;
    for(auto x : vec){
        cout<<"\t\t|"<<x.first.getDiameter()<<"\t\t\t|"<<x.first.getIdentifier()<<"\t\t\t|"<<x.second.getDiameter()<<"\t\t\t|"<<x.second.getIdentifier();
        (x.first == x.second ? cout<<"\t\t\t|Ja.    |"<<endl : cout<<"\t\t\t|Neen.  |"<<endl);
    }
    cout<<"\t\t -------------------------------------------------------"<<endl;
    /*
     
     einde van formattering
     */
    
    cout<<"input_deksels: diamteter\\identifier"<<endl;
    for(auto x : v_dek){
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<endl;
    cout<<"input_potjes: diamteter\\identifier"<<endl;
    for(auto x : v_pot){
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<endl;
    
    return vec;
}

