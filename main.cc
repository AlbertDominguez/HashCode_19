#include "structures.hh"
#include <iostream>
using namespace std;

vector<Picture> pictures;
vector<Slide> slides;

void read() {
    int N; cin >> N;
    slides.reserve(N);
    pictures = vector<Picture>(N);
    for (int i = 0; i < N; ++i) {
        pictures[i].id = i;
        char v; cin >> v;
        pictures[i].vertical = (v == 'V');
        int tagnum; cin >> tagnum;
        pictures[i].tags = vector<string>(tagnum);
        for (int j = 0; j < tagnum; ++j) {
            string tag;
            cin >> tag;
            pictures[i].tags[j] = tag;
            tagctrl[tag].insert(i);
        }
    }
}

void output() {
    cout << slides.size() << endl;
    for (Slide sd : slides) {
        cout << sd.ph1;
        if (sd.ph2 != -1) {
            cout << ' ' << sd.ph2;
        }
        cout << endl;
    }
}

int main () {
    read();
    // TEST CHECK
	/*for (auto pic : pictures) {
        cout << (pic.vertical ? "V " : "H ") << pic.tags.size();
        for (string s : pic.tags) cout << ' ' << s;
        cout << endl; 
    }
    for (auto x : tagctrl) {
        cout << x.first << ' ';
        for (auto i : x.second) {
            cout << i << ' ';
        }
        cout << endl;
    }*/
    // OUTPUT CHECK
    /*set<string> temp;
    Slide s1 = {};
    s1.ph1=1; s1.ph2=3;
    Slide s2 = {};
    s2.ph1=2; s2.ph2=-1;
    slides.push_back(s1);
    slides.push_back(s2);*/
    output();
}
