#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define loop(i, s) for (int i = 0; i < s; ++i)
#define loop_se(i, st, en) for (int i = st; i <= en; ++i)
#define ll long long
#define print_vt(vt) \
    for (auto e : vt) { \
        cout << e << " ";   \
    }   \
    cout << endl; \


void start() {
    FILE* f_in = freopen("hps.in", "r", stdin);
    FILE* f_out = freopen("hps.out", "w", stdout);
    int N;
    cin >> N;
    vector<int> pH(N + 1, 0);
    vector<int> pP(N + 1, 0);
    vector<int> pS(N + 1, 0);
    loop_se(i, 1, N) {
        char g; 
        cin >> g;
        pH[i] = pH[i - 1];
        pP[i] = pP[i - 1];
        pS[i] = pS[i - 1];
        if (g == 'H') {
            pH[i]++;
        } else if (g == 'P') {
            pP[i]++;
        }
        else {
            pS[i]++;
        }
    }

    // print_vt(pH);
    // print_vt(pP);
    // print_vt(pS);

    int maxWins = 0;
    loop_se(i, 1, N) {
        // Find the current max
        auto max_val = max(pH[i], max(pP[i], pS[i]));
        auto post_max = max(pH[N] - pH[i], max(pP[N] - pP[i], pS[N] - pS[i]));
        // cout << "max_val: " << max_val << " - post_max: " << post_max << endl;
        maxWins = max(maxWins, max_val + post_max);
    }

    cout << maxWins;

    fclose(f_in);
    fclose(f_out);
}

int main() {
    start();
    return 0;
}
