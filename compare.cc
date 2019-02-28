#include "structures.hh"
#include <algorithm>
#include <iostream>

int score(Slide s1, Slide s2) {
    set<string> common;
    set_intersection(s1.tags.begin(), s1.tags.end(),
                    s2.tags.begin(), s2.tags.end(),
                    inserter(common, common.begin()));

    int ctags = common.size();

    int difs1 = s1.tags.size() - ctags;
    int difs2 = s2.tags.size() - ctags;

    return (min(ctags, min(difs1, difs2)));
}

int main() {
    Slide s1;
    Slide s2;

    s1.tags = {"pau", "domi", "ibrar"};
    s2.tags = {"pau", "domi", "ibrar"};

    cout << score(s1, s2) << endl;

    
}