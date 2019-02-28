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

vector<Slide> get_slides() {
    vector<Slide> ret;
    vector<Slide> verticals;
    ret.reserve(pictures.size());
    verticals.reserve(pictures.size());
    for (Picture p : pictures) {
        if (!p.vertical) {
            ret.push_back(createSlide(p));
        } else {
            verticals.push_back(createSlide(p));
        }
    }
    vector<bool> used_verts(verticals.size(), false);
    for (int i = 0; i < verticals.size(); ++i) {
        if (not used_verts[i]) {
            used_verts[i] = true;
            int min_score = -1;
            int min_idx = -1;
            for (int j = 0; j < used_verts.size(); ++j) {
                if (not used_verts[j]) {
                    int sc = score(verticals[i], verticals[j]);
                    if (min_score == -1 or sc < min_score) {
                        min_score = sc;
                        min_idx = j;
                    }
                }
            }
            if (min_idx != -1) {
                used_verts[min_idx] = true;
                ret.push_back(createSlide(pictures[verticals[i].ph1], pictures[verticals[min_idx].ph1]));
            }
        }
    }
    return ret;
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
