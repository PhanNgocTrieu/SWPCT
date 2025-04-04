


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
    vector<ll> expireTimes(N);
    vector<ll> scores(N);
    for (int i = 0; i < N; ++i) {
        cin >> expireTimes[i];
        max_time = max(max_time, expireTimes[i]);
    }

    for (int i = 0; i < N; ++i) {
        cin >> scores[i];
    }

    map<ll, priority_queue<ll>> mq;
    for (int i = 0; i < N; ++i) {
        mq[expireTimes[i]].push(scores[i]);
    }

    ll ans = 0;
    // cout << "max_time: " << max_time << endl;
    for (int i = max_time; i > 0; --i) {
        ll m_v = 0;

        for (auto itr = mq.begin(); itr != mq.end(); ++itr) {
            if (itr->first < i) {
                continue;
            }

            if (itr->second.empty()) {
                continue;
            }

            auto g = itr->second.top();
            itr->second.pop();
            // cout << "top: " << g << endl;
            m_v = max(m_v, g);
        }
        ans += m_v;
    }

    cout << ans << "\n";
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    solve();
    return 0;
}