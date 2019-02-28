#ifndef Structures_hh
#define Structures_hh

#include <algorithm>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;



struct Picture {
    int id;
    bool vertical;
    vector<string> tags;
};


struct Slide {
    int ph1;
    int ph2 = -1;
    set<string> tags;
};

unordered_map<string,set<int>> tagctrl;



#endif