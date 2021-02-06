#ifndef MATCHER_H
#define MATCHER_H

#include "Deksel.h"
#include "Pot.h"
#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Matcher{
public: static vector<pair<Deksel,Pot>> match(const vector<Deksel>&, const vector<Pot>&);
};

#endif
