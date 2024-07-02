/*
    Problem Link: https://usaco.org/index.php?page=viewproblem2&cpid=572 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <bits/stdc++.h>
#include <set>

using namespace std;
// Kind of variables
#define ll long long

using vl = vector<ll>;

// Functions
#define loop(I, S) for (int I = 0; I < S; I++)
#define loop_init(I,Str,End) for (int I = Str; I < End; I++)
#define loop_cond(I,S,U) for (I = 0; I < S; #U)
#define getVector(n, vt) for (auto n : vt)
#define shift_left(n) (1 << n)
#define shift_right(n) (1 >> n)

struct prefix_cow {
    int num_one = 0;
    int num_two = 0;
    int num_three = 0;
};

bool setupFlag = false;

void breed_counting(const vector<int>& cows, int a, int b) {
    int size = cows.size();
    static vector<prefix_cow> prefixs;
    if (!setupFlag) {
        prefix_cow pref;
        prefixs.push_back(pref);
        loop(i, size) {
            if (cows[i] == 1) {
                pref.num_one++;
            } else if (cows[i] == 2) {
                pref.num_two++;
            } else {
                pref.num_three++;
            }
            prefixs.push_back(pref);
        }
        setupFlag = true;
    }

    cout << (prefixs[b].num_one - prefixs[a - 1].num_one) << " "
         << prefixs[b].num_two - prefixs[a - 1].num_two << " "
         << prefixs[b].num_three - prefixs[a - 1].num_three << endl;
}


void start() {  
    // If version is not c++11 -> could not use "auto" keyword, we need to define clearly as belows
    FILE* fd_in = freopen("bcount.in", "r", stdin);
    FILE* fd_out = freopen("bcount.out", "w", stdout);
    
    int _cows, _queries;
    cin >> _cows >> _queries;

    vector<int> cows;
    while (_cows--) {
        int cow;
        cin >> cow;
        cows.push_back(cow);
    }

    // queries
    while (_queries--) {
        int a, b;
        cin >> a >> b;
        breed_counting(cows, a, b);
    }

    fclose(fd_in);
    fclose(fd_out);
}

int main() {
    start();
}
