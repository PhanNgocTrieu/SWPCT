
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long

void process() {
    ll columns, X;
    ll maxH = 0;
    cin >> columns >> X;
    ll maxCurH = 0;
    vector<ll> tanks(columns);
    for (int i = 0; i < columns; ++i) {
        cin >> tanks[i];
        if (maxCurH < tanks[i]) { maxCurH = tanks[i]; }
    }
    // sort(tanks.begin(), tanks.end());
    for (ll h = maxCurH; h >= 1; --h) {
        ll sum = 0;
        for (int j = 0; j < columns; ++j) {
            if (tanks[j] > h || sum > X) { continue; }
            sum += (h - tanks[j]);
        }
        
        if (sum <= X) {
            ll cX = X;
            cX -= sum;
            if (cX >= columns) {
                h += (cX / columns);
            }
            maxH = max(maxH, h);
            break;
        }
        
    }
    cout << maxH << "\n";
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t; cin >> t;
    while (t--) {
        process();
    }
    return 0;
}



#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
 
 
int main() {
    int N, X, a, T;
    cin >> T;
    while(T--) {
        map<int, int> pr;
        cin >> N >> X;
        for(int i = 0; i < N; i++) {
            cin >> a;
            pr[a]++;
        }
        pr[2000000001] = 1;
        long long sum = 0, w = 0, h = 0, t;
        for(auto it = pr.begin(); it != pr.end(); it++) {
            t = (it->first - h) * w;
            if(X > t) {
                X -= t;
                h = it->first;
                w += it->second;
            }
            else if(w > 0) {
                h += X / w;
                break;
            }
        }
        cout << h << '\n';
    }
    return 0;
}