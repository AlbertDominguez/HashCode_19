#include "structures.hh"
#include <algorithm>
#include <iostream>

Slide createSlide(Picture p1, Picture p2) {
    Slide ans;
    ans.ph1 = p1.id;
    ans.ph2 = p2.id;
    set_union(p1.tags.begin(), p1.tags.end(), 
               p2.tags.begin(), p2.tags.end(), 
               inserter(ans.tags, ans.tags.begin()));
    return ans;
}

Slide createSlide(Picture p1) {
    Slide ans;
    ans.ph1 = p1.id;
    ans.ph2 = -1;
    copy(p1.tags.begin(), p1.tags.end(), inserter(ans.tags, ans.tags.end()));
    return ans;
}

int main(){
    Picture p1, p2;
    p1.id = 0;
    p2.id = 1;

    p1.tags = {"pau", "ibrar", "domi"};
    p2.tags = {"pau", "ibrar", "dani"};
    Slide ans = create(p1);


    for (auto it = ans.tags.begin(); it != ans.tags.end(); ++it) cout << ' ' << *it;
    cout << endl;

    cout << "Foto 1: " << ans.ph1 << endl;
    cout << "Foto 2: " << ans.ph2 << endl;
    
    
}