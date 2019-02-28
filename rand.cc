#include "structures.hh"
#include <iostream>
#include <cstdlib>

int totalscore (const vector<Slide>& sol){
    int n = sol.size();
    int sum = 0;
    for (int i = 0; i < n-1; ++i) sum += score(sol[i], sol[i+1]);
    return sum;
}

void swapping (vector<Slide>& solution, int score){
    int it_max = 10000;
    for (int i = 0; i < it_max; ++i){
        int n = solution.size();
        int swap1 = rand() % (n-2) + 1;
        int swap2 = rand() % (n-2) + 1;

        int scminus = score(solution[swap1], solution[swap1-1]) 
                    + score(solution[swap1], solution[swap1+1])
                    + score(solution[swap2], solution[swap2-1]) 
                    + score(solution[swap2], solution[swap2+1]);
        int scplus =  score(solution[swap2], solution[swap1-1]) 
                    + score(solution[swap2], solution[swap1+1])
                    + score(solution[swap1], solution[swap2-1]) 
                    + score(solution[swap1], solution[swap2+1]);
        if (scplus > scminus) swap(solution[swap1], solution[swap2]);
    }

}