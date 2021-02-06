#include "huffman.h"
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <stack>
using std::cout;
using std::make_shared;
using std::priority_queue;
using std::shared_ptr;
using std::vector;

struct Knoop {
    uint gewicht;
    vector<uchar> karakter;
    bool nietBlad;
    shared_ptr<Knoop> links;
    shared_ptr<Knoop> rechts;
    vector<int> code;
};

/**
 * Maakt een priority queue die Knoop-objecten teruggeeft volgens oplopend gewicht
 */
auto maak_priority_queue() {

    // Comparator die de gewichten van knopen met elkaar vergelijkt
    auto compare_gewicht = [](const auto &p1, const auto &p2) {
        return p1->gewicht > p2->gewicht;
    };

    return priority_queue<shared_ptr<Knoop>,
                          vector<shared_ptr<Knoop>>,
                          decltype(compare_gewicht)>{compare_gewicht};
}

map<uchar, string> huffman(const map<uchar, uint> &freq) {

    auto queue = maak_priority_queue();

    for (auto&& [key, value] : freq)
    {
        queue.push(make_shared<Knoop>(Knoop{value, vector<uchar>{key}, false}));
    }
    auto wortel = queue.top();
    while (!queue.empty()) {
        auto k1 = queue.top();
        queue.pop();
        if(queue.empty())
        {
            wortel = k1;
            continue;
        }
        auto k2 = queue.top();
        queue.pop();
        vector<uchar> karakters(k1->karakter);
        for (auto&& c: k2->karakter)
        {
            karakters.push_back(c);
        }
        queue.push(make_shared<Knoop>(Knoop{k1->gewicht + k2->gewicht, karakters, true, k1, k2}));
    }
    std::stack<shared_ptr<Knoop>> NOK;
    NOK.push(wortel);
    while(!NOK.empty())
    {
        auto knoop = NOK.top();
        NOK.pop();
        if(knoop->links)
        {
            knoop->links->code = knoop->code;
            knoop->links->code.push_back(0);
            NOK.push(knoop->links);
        }
        if(knoop->rechts)
        {
            knoop->rechts->code = knoop->code;
            knoop->rechts->code.push_back(1);
            NOK.push(knoop->rechts);
        }
    }

    NOK.push(wortel);
    map<uchar, string> oplossing;
    while(!NOK.empty())
    {
        auto knoop = NOK.top();
        NOK.pop();
        if(knoop->links)
        {
            if(!knoop->links->nietBlad)
            {
                string codering;
                for(auto&& c: knoop->links->code)
                {
                    if(c == 1)
                    {
                        codering+='1';
                    }
                    else
                    {
                        codering+='0';
                    }
                }
                oplossing.insert({knoop->links->karakter[0], codering});
            }
            NOK.push(knoop->links);
        }
        if(knoop->rechts)
        {
            if(!knoop->rechts->nietBlad)
            {
                string codering;
                for(auto&& c: knoop->rechts->code)
                {
                    if(c == 1){
                        codering+='1';
                    }
                    else
                    {
                        codering+='0';
                    }
                }
                oplossing.insert({knoop->rechts->karakter[0], codering});
            }
            NOK.push(knoop->rechts);
        }
    }

    // Voorbeeld van hoe je elementen toevoegt aan de queue:
    //
    // queue.push(make_shared<Knoop>(Knoop{6}));
    // queue.push(make_shared<Knoop>(Knoop{1}));
    // queue.push(make_shared<Knoop>(Knoop{7}));
    // queue.push(make_shared<Knoop>(Knoop{3}));
    // queue.push(make_shared<Knoop>(Knoop{4}));
    // queue.push(make_shared<Knoop>(Knoop{2}));
    // queue.push(make_shared<Knoop>(Knoop{5}));

    // Voorbeeld van hoe je elementen volgens oplopend gewicht
    // uit de queue haalt:
    //
    // while (!queue.empty()) {
    //     auto k = queue.top();
    //     queue.pop();

    //     std::cout << k->gewicht << "\n";
    // }

    map<uchar, string> codering{{'z', "1"}, {'x', "00"}, {'y', "01"}};

    return oplossing;
}