#include "structures.hh"
#include <iostream>
using namespace std;

vector<Picture> pictures;

void read() {
    int N; cin >> N;
    pictures = vector<Picture>(N);
    for (int i = 0; i < N; ++i) {
        char v; cin >> v;
        pictures[i].vertical = (v == 'V');
        int tagnum; cin >> tagnum;
        pictures[i].tags = vector<string>(tagnum);
        for (int j = 0; j < tagnum; ++j) {
            cin >> pictures[i].tags[j];
        }
    }
}

int main () {
    read();
	for (auto pic : pictures) {
        cout << (pic.vertical ? "V " : "H ") << pic.tags.si
        
        ze();
        for (string s : pic.tags) cout << ' ' << s;
        cout << endl; 
    }
}
