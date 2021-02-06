#include "bellmanford.h"

#include <iostream>
using std::cout;

void kleineGraafTest() {
    GraafMetTakdata<GERICHT, int> g(6);

    // van, naar, gewicht
    int takken[9][3] = {{0, 1, 4}, {0, 2, 1}, {1, 2, 3}, {2, 4, 1}, {3, 1, -4}, {3, 5, 1}, {4, 3, 2}, {4, 1, 1}, {4, 5, 4}};

    for (auto [van, naar, gewicht] : takken) {
        g.voegVerbindingToe(van, naar, gewicht);
    }

    g.teken("eenvoudigegraaf.dot");

    int van = 0;
    auto [afstand, voorloper] = bellmanFord(g, van);

    for (int naar = 0; naar < g.aantalKnopen(); naar++) {
        if (van != naar) {
            if (afstand[naar] != INT32_MAX) {
                cout << "Pad van " << van << " naar " << naar << " gaat via " << voorloper[naar] << " en heeft totaal gewicht " << afstand[naar] << "\n";
            } else {
                cout << "Pad van " << van << " naar " << naar << " bestaat niet\n";
            }
        }
    }
}

int main() {
    kleineGraafTest();
    return 0;
}