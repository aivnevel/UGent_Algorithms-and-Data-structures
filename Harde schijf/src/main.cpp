#include "exthash.h"

#include <iostream>
#include <string>
using std::cout;
using std::string;
#include <bitset>
using std::bitset;

int main() {

    /* Landcodes toevoegen aan de paginas op de schijf*/
    Schijf<Pagina<string, string, 4>> schijf;
    ExtendibleHashTable<string, string, 4> landcodes(schijf);

    landcodes.voegtoe("AT", "Oostenrijk");
    landcodes.voegtoe("BE", "Belgie");
    landcodes.voegtoe("CZ", "Tsjechie");
    landcodes.voegtoe("DK", "Denemarken");
    landcodes.voegtoe("DE", "Duitsland");
    landcodes.voegtoe("EE", "Estland");
    landcodes.voegtoe("ES", "Spanje");
    landcodes.voegtoe("FR", "Frankrijk");
    landcodes.voegtoe("HR", "Kroatie");
    landcodes.voegtoe("IT", "Italie");
    landcodes.voegtoe("HU", "Hongarije");
    landcodes.voegtoe("SE", "Zweden");
    landcodes.voegtoe("NL", "Nederland");

    cout << landcodes << "\n";

    cout << "--GeefData: \n" ;
    string testcodes[] = {"BE", "IT", "US"}; //US komt niet voor
    for (auto code : testcodes) {
        auto data = landcodes.geefData(code);
        if (data) {
            cout << "Code " << code << " --> " << *data << "\n";
        } else {
            cout << "Code " << code << " komt niet voor \n";
        }
    }

    cout << "--Verwijderen van BE (België): \n" ;
    landcodes.verwijder("BE");

    cout << "--GeefData: \n" ;
    for (auto code : testcodes) { //US en BE komen niet voor
        auto data = landcodes.geefData(code);
        if (data) {
            cout << "Code " << code << " --> " << *data << "\n";
        } else {
            cout << "Code " << code << " komt niet voor \n";
        }
    }


    int b = 1;               // 0b0001
    int c = b << 2;          // 0b0100
    int d = b | c;           // 0b0101
    int f = 0b1001 & 0b1010; // 0b1000

    cout << bitset<4>(b) << ", " << bitset<4>(c) << ", " << bitset<4>(d) << ", " << bitset<4>(f) << "\n";

    
    return 0;
}