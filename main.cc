#include "structures.hh"
#include <iostream>
#include <cstdlib>
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


Slide createSlide(const Picture& p1, const Picture& p2) {
    Slide ans;
    ans.ph1 = p1.id;
    ans.ph2 = p2.id;
    set_union(p1.tags.begin(), p1.tags.end(), 
               p2.tags.begin(), p2.tags.end(), 
               inserter(ans.tags, ans.tags.begin()));
    return ans;
}

Slide createSlide(const Picture& p1) {
    Slide ans;
    ans.ph1 = p1.id;
    ans.ph2 = -1;
    copy(p1.tags.begin(), p1.tags.end(), inserter(ans.tags, ans.tags.end()));
    return ans;
}

int score(const Slide& s1, const Slide& s2) {
    set<string> common;
    set_intersection(s1.tags.begin(), s1.tags.end(),
                    s2.tags.begin(), s2.tags.end(),
                    inserter(common, common.begin()));

    int ctags = common.size();

    int difs1 = s1.tags.size() - ctags;
    int difs2 = s2.tags.size() - ctags;

    return (min(ctags, min(difs1, difs2)));
}

bool comp(Slide& s1, Slide& s2) {
    return s1.tags.size() < s2.tags.size();
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
    sort(verticals.begin(), verticals.end(), comp);
    int i = 0; 
    int j = verticals.size()-1;
    while (i < j) {
        ret.push_back(createSlide(pictures[verticals[i].ph1], pictures[verticals[j].ph1]));
        ++i;
        --j;
    }    
    return ret;
}

vector<int> greedy(const vector<Slide>& poslides, int& totalscore){
    int n = poslides.size();
    vector<int> solution;
    solution.reserve(n);

    // First slide will be random a.k.a the first one
    solution.push_back(0);
    // Fill up solution until no slides left
    vector<bool> used (n, false);
    used[0] = true;
    int it_max = 1000;
    for (int done = 0; done < n-1; ++done){
        int best = -1;
        int bestscore = -1;
        int tempscore;
        int previous = solution[done];
        int j = 0;
        cout << done << endl;
        // We compare with all other possible slides and keep the best
        for (int i = 1; j < it_max and i < n-1;++i){
            if (used[i]) continue;
            ++j;
            tempscore = score(poslides[previous], poslides[i]);
            // If better we keep it
            if (bestscore < tempscore){

                bestscore = tempscore;
                best = i;
            }

        }
        solution.push_back(best);
        used[best] = true;
        totalscore += bestscore;
    }

    return solution;
}


int totalscore (const vector<Slide>& sol){
    int n = sol.size();
    int sum = 0;
    for (int i = 0; i < n-1; ++i) sum += score(sol[i], sol[i+1]);
    return sum;
}

void swapping (vector<int>& order, const vector<Slide>& solution, int& sc){
    int it_max = 100000;
    for (int i = 0; i < it_max; ++i){
        int n = solution.size();
        int swap1 = rand() % (n-2) + 1;
        int swap2 = rand() % (n-2) + 1;
        int swp1 = order[swap1];
        int swp2 = order[swap2];
        int scminus = score(solution[swp1], solution[swp1-1]) 
                    + score(solution[swp1], solution[swp1+1])
                    + score(solution[swp2], solution[swp2-1]) 
                    + score(solution[swp2], solution[swp2+1]);
        int scplus =  score(solution[swp2], solution[swp1-1]) 
                    + score(solution[swp2], solution[swp1+1])
                    + score(solution[swp1], solution[swp2-1]) 
                    + score(solution[swp1], solution[swp2+1]);
        if (scplus > scminus) {
            swap(order[swap1], order[swap2]);
            sc -= scminus;
            sc += scplus;
        } 
    }

}


void output(const vector<Slide>& Slds, const vector<int>& order) {
    for (int sd : order) {
        cout << Slds[sd].ph1;
        if (Slds[sd].ph2 != -1) {
            cout << ' ' << Slds[sd].ph2;
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
    vector<Slide> preprocessed_slides;
    preprocessed_slides = get_slides();
    int temp = 0;
    vector<int> order;
    order = greedy(preprocessed_slides, temp);
    int sc1 = totalscore(preprocessed_slides);
    swapping(order, preprocessed_slides, sc1);
    
    output(preprocessed_slides, order);
    cout << sc1 << endl;
}
