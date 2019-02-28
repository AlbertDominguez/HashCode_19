#include "structures.hh"
#include <iostream>

vector<int> greedy(const vector<Slide>& poslides, int& totalscore){
    int n = poslides.size();
    vector<int> solution;
    solution.reserve(n);

    // First slide will be random a.k.a the first one
    solution.push_back(0);
    // Fill up solution until no slides left
    vector<bool> used (n, false);
    used[0] = true;
    for (int done = 0; done < n-1; ++done){
        int best = -1;
        int bestscore = -1;
        int tempscore;
        int previous = solution[done];
        // We compare with all other possible slides and keep the best
        for (int i = 1; i < n; ++i){
            if (used[i]) continue;
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

int main(){
    Slide s1, s2, s3;
    s1.tags = {"a", "b", "c", "z"};
    s2.tags = {"a", "b", "c", "e"};
    s3.tags = {"a", "j", "d", "z"};
    vector<Slide> all;
    all.push_back(s1);
    all.push_back(s2);
    all.push_back(s3);
    int tscore = 0;
    
    vector<int> ans = greedy(all, tscore);
    cout << tscore << endl;
    for (int i = 0; i < 3; ++i){
        cout << ans[i] << " ";
    }
    cout << endl;
    
    
}