#include "structures.hh"
using namespace std;

vector<Picture> pictures;
vector<Slide> slides;


void read() { // Reads the data from the txt file
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
            cin >> pictures[i].tags[j];
        }
    }
}


Slide createSlide(const Picture& p1, const Picture& p2) { // Creates a slide given 2 vertival pictures
    Slide ans;
    ans.ph1 = p1.id;
    ans.ph2 = p2.id;
    set_union(p1.tags.begin(), p1.tags.end(), 
               p2.tags.begin(), p2.tags.end(), 
               inserter(ans.tags, ans.tags.begin()));
    return ans;
}

Slide createSlide(const Picture& p1) { // Creates a slide given a horizontal picture
    Slide ans;
    ans.ph1 = p1.id;
    ans.ph2 = -1;
    copy(p1.tags.begin(), p1.tags.end(), inserter(ans.tags, ans.tags.end()));
    return ans;
}

int score(const Slide& s1, const Slide& s2) { // Returns the score between 2 slides
    set<string> common;
    set_intersection(s1.tags.begin(), s1.tags.end(),
                    s2.tags.begin(), s2.tags.end(),
                    inserter(common, common.begin()));

    int ctags = common.size();

    int difs1 = s1.tags.size() - ctags;
    int difs2 = s2.tags.size() - ctags;

    return (min(ctags, min(difs1, difs2)));
}

bool comp(Slide& s1, Slide& s2) { // to be passed to sort function
    return s1.tags.size() < s2.tags.size();
}

vector<Slide> get_slides() { // Creation of all the slides to be used
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
    sort(verticals.begin(), verticals.end(), comp); // Sort by tag number
    int i = 0; 
    int j = verticals.size()-1;
    while (i < j) {
        ret.push_back(createSlide(pictures[verticals[i].ph1], pictures[verticals[j].ph1]));
        ++i;
        --j;
    }    
    return ret;
}



int totalscore (const vector<Slide>& sol){ // Computes the score in the whole slideshow
    int n = sol.size();
    int sum = 0;
    for (int i = 0; i < n-1; ++i) sum += score(sol[i], sol[i+1]);
    return sum;
}

void swapping (vector<Slide>& solution, int& sc) {
    int it_max = 100000;
    for (int i = 0; i < it_max; ++i){
        int n = solution.size();
        int swap1 = rand() % (n-2) + 1;
        int swap2 = rand() % (n-2) + 1;

        int scminus = score(solution[swap1], solution[swap1-1]) 
                    + score(solution[swap1], solution[swap1+1])
                    + score(solution[swap2], solution[swap2-1]) 
                    + score(solution[swap2], solution[swap2+1]);
        int scplus  = score(solution[swap2], solution[swap1-1]) 
                    + score(solution[swap2], solution[swap1+1])
                    + score(solution[swap1], solution[swap2-1]) 
                    + score(solution[swap1], solution[swap2+1]);
        if (scplus > scminus) {
            swap(solution[swap1], solution[swap2]);
            sc -= scminus;
            sc += scplus;
        } 
    }

}


void output(const vector<Slide>& Slds) { // Outputs the final slideshow properties onto a file
    cout << Slds.size() << endl;
    for (Slide sd : Slds) {
        cout << sd.ph1;
        if (sd.ph2 != -1) {
            cout << ' ' << sd.ph2;
        }
        cout << endl;
    }
}

int main () {
    read();
    vector<Slide> preprocessed_slides;
    preprocessed_slides = get_slides();
    int sc1 = totalscore(preprocessed_slides);
    swapping(preprocessed_slides, sc1);
    output(preprocessed_slides);
}
