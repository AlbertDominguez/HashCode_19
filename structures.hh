#ifndef Structures_hh
#define Structures_hh

#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

using Slide = pair<int,int>;

struct Picture {
    bool vertical;
    vector<string> tags;
};

unordered_map<string,set<int>> tagctrl;



#endif