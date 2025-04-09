


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

#define ll long long
#define sleep_time(x) for (int i = 0; i < x; ++i){}

ll N;
ll max_time = 0;

void solve() {
    cin >> N;
    // vector<ll> expireTimes(N);
    // vector<ll> scores(N);
    vector<pair<ll, ll>> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i].first;
    }

    for (int i = 0; i < N; ++i) {
        cin >> a[i].second;
    }

    sort(a.begin(), a.end());

    priority_queue<ll> pq;

    ll i = N - 1;
    ll ans = 0, k = a[N-1].first;

    while (k > 0) {

        while (i >= 0 && a[i].first == k) {
            pq.push(a[i].second);
            i--;
        }

        if (!pq.empty()) {
            ans += pq.top();
            pq.pop();
            --k;
        }
        else {
            if (i >= 0) {
                k = a[i].first;
            }
            else {
                break;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    solve();
    return 0;
}