#ifndef Structures_hh
#define Structures_hh

#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;


struct Picture {
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