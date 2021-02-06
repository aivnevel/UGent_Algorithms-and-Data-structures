#include <string>
#include <queue>
#include <iostream>
#include <vector>
using std::string;
using std::queue;
using std::cout;
using std::vector;

const int ALFABET_GROOTTE = 256;

queue<int> zoek_rabinkarp(const string& naald, const string &hooiberg, int priemgetal = 997) {
    int size = naald.size(), start = 1;
    
    vector<long> tabel(size);
    for(char c : naald)
    {
        auto it = tabel.begin();
        tabel.insert(it, start);
        start *= 10;
    }
    long hash = 0, it = 0;
    for(char c : naald)
    {
        hash += c * tabel[it];
        it++;
    }
    hash %= priemgetal;
    int sliderStart = 0, sliderEind = size, hashHooibergPrevious = 0;
    bool gevonden = false;
    queue<int> oplossing;
    for (int i = sliderStart; i <= sliderEind; i++)
    {
        hashHooibergPrevious += hooiberg[i]*tabel[i-sliderStart];
    }
    hashHooibergPrevious %= priemgetal;
    if(hashHooibergPrevious == hash)
        {
            long i = sliderStart;
            while(i < sliderEind)
            {
                gevonden = hooiberg[i] == naald[i-sliderStart];
                i++;
            }
            if(gevonden)
            {
                oplossing.push(sliderStart);
            }
        }
    while(sliderEind != hooiberg.size())
    {
        long hashHooiberg = 0;
        hashHooiberg = ((hashHooibergPrevious - hooiberg[sliderStart] * tabel[0]) * 10 + hooiberg[sliderEind])%priemgetal;
        if(hashHooiberg == hash)
        {
            long i = sliderStart;
            while(i < sliderEind)
            {
                gevonden = hooiberg[i] == naald[i-sliderStart];
                i++;
            }
            if(gevonden)
            {
                oplossing.push(sliderStart);
            }
        }
        sliderStart++;
        sliderEind++;
        hashHooibergPrevious = hashHooiberg;
    }
    return oplossing;
}


/* hulpfunctie die de queue met resultaten zal afprinten*/
void printPosities(queue<int> posities) {
    int v = -1;
    while (!posities.empty()) {
        v = posities.front();
        posities.pop();
        if (!posities.empty()) {
            std::cout << v << " - ";
        }
    }
    cout << v << "\n";
}

int main() {
    string tekst, naald;
    queue<int> posities;
    cout << "vraag 2: Rabin-Karp \n";
    
    //voorbeeld 1
    tekst = "Dit is een voorbeeltektst voor de tweede vraag op de test gevorderde algoritmen om het algoritme van Rabin-Karp te testen";
    naald = "algoritme";
    posities = zoek_rabinkarp(naald, tekst);
    printPosities(posities); // 69 - 87

    //voorbeeld 2
    tekst = "38326 25364 25365 25365 38326 25365";
    naald = "25365";
    posities = zoek_rabinkarp(naald, tekst);
    printPosities(posities); // 12 - 18 - 30

    std::cout << "Done" << std::endl;
    return 0;
}