/*
    Farmer John's N cows are standing in a row, as they have a tendency to do from time to time. 
    Each cow is labeled with a distinct integer ID number so FJ can tell them apart. 
    FJ would like to take a photo of a contiguous group of cows but, due to a traumatic childhood incident involving the numbers 
    1…6, he only wants to take a picture of a group of cows if their IDs add up to a multiple of 7.
    
    Please help FJ determine the size of the largest group he can photograph.

    INPUT FORMAT (file div7.in):
        The first line of input contains N (1≤N≤50,000). 
        The next N lines each contain the N integer IDs of the cows (all are in the range 0…1,000,000).
    OUTPUT FORMAT (file div7.out):
        Please output the number of cows in the largest consecutive group whose IDs sum to a multiple of 7. 
        If no such group exists, output 0.
        You may want to note that the sum of the IDs of a large group of cows might be too large to fit into a standard 32-bit integer. If you are summing up large groups of IDs, you may therefore want to use a larger integer data type, like a 64-bit "long long" in C/C++.
        
        Input	        Output
        7               5
        3
        5
        1
        6
        2
        14
        10
        In this example, 5+1+6+2+14 = 28.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <set>

using namespace std;
#define ll long long
using vl = vector<ll>;

// Functions
#define loop(I, S) for (int I = 0; I < S; I++)
#define loop_init(I,Str,End) for (int I = Str; I < End; I++)
#define loop_cond(I,S,U) for (I = 0; I < S; #U)
#define getVector(n, vt) for (auto n : vt)

#if 0
void subSequenceSumToSevens() {
    int size;
    cin >> size;
    vector<int> cows(size);
    vector<ll> prefix(size + 1);
    prefix[0] = 0;
    for (int i = 1; i <= size; i++) {
        cin >> cows[i - 1];
        prefix[i] = prefix[i - 1] + cows[i - 1];
    }
    ll res = 0;
    for (ll i = 1; i <= size; i++) {
        for (ll j = i + 1; j <= size; j++) {
            if ( (prefix[j] - prefix[i]) % 7 == 0) {
                res = max(res, j - i);
            }
        }
    }
    cout << res << endl;
}
#endif

void subsequenceSumToSevens() {
    int size;
    cin >> size;
    vector<int> values(size + 1);
    vector<ll> prefix_mode_sum(size + 1);
    prefix_mode_sum[0] = 0;
    for (ll i = 1; i <= size; ++i) {
        cin >> values[i];
        prefix_mode_sum[i] = prefix_mode_sum[i - 1] + values[i];
        prefix_mode_sum[i] = prefix_mode_sum[i] % 7;
    }
    ll max_ = 0;
    for (ll i = 1; i <= size; ++i) {
        for (ll j = i + 1; j <= size; ++j) {
            if ( prefix_mode_sum[i] == prefix_mode_sum[j] ) {
                max_ = max(max_, j - i);
            }
        }
    }
    cout << max_ << endl;
}

void start() {  
    // If version is not c++11 -> could not use "auto" keyword, we need to define clearly as belows
    FILE* fd_in = freopen("div7.in", "r", stdin);
    FILE* fd_out = freopen("div7.out", "w", stdout);
    
    subsequenceSumToSevens();

    fclose(fd_in);
    fclose(fd_out);
}

int main() {
    start();
    return 0;
}
