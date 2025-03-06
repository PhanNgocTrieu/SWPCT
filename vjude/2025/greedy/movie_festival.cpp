// https://vjudge.net/contest/690988#problem/C
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define debug_q(q) \
    { \
        auto q_ = q; \
        while (!q_.empty()) { \
            cout << q_.front() << ' '; \
            q_.pop(); \
        } \
        cout << '\n'; \
    }

#define debug_v(v) \
    { \
        cout << #v << ": "; \
        for (auto x : v) { \
            cout << x << ' '; \
        } \
        cout << '\n'; \
    }

#define debug_vv(vv) \
    { \
        for (int i = 0; i < vv.size(); i++) { \
            cout << "v[" << i << "]: "; \
            for (auto x : vv[i]) { \
                cout << x << ' '; \
            } \
            cout << '\n'; \
        } \
    }

#define debug_x(x) \
    { \
        cout << #x << ": " << x << '\n'; \
    }

#define debug_msg(msg) \
    { \
        cout << #msg << '\n'; \
    }

#define debug_map(m) \
    { \
        for (auto it = m.begin(); it != m.end(); it++) { \
            cout << it->first << ": " << it->second << '\n'; \
        } \
    }

typedef long long ll;

void solve() {
    int n, k;
    cin >> n >> k;
    vector< pair<int, int> > movies(n);
    for (int i = 0; i < n; i++) {
        cin >> movies[i].first >> movies[i].second;
    }

    // Sort movies by their ending times
    sort(movies.begin(), movies.end(), [](pair<int, int> a, pair<int, int> b){
        return a.second < b.second;
    });

    multiset<int> end_times;
    for (int i = 0; i < k; i++) {
        end_times.insert(0);
    }

    int ans = 0;
    for (auto movie : movies) {
        auto it = end_times.upper_bound(movie.first);
        if (it != end_times.begin()) {
            end_times.erase(--it);
            end_times.insert(movie.second);
            ans++;
        }
    }

    cout << ans << '\n';
}

// #define READ_FILE
#define FILE_I "div7.in"
#define FILE_O "div7.out"

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#ifdef READ_FILE
    auto f_i = freopen(FILE_I, "r", stdin);
    auto f_o = freopen(FILE_O, "w", stdout);
#endif
    // int t; cin >> t;
    // while (t--) {
        solve();

    // }

#ifdef READ_FILE
    fclose(f_i);
    fclose(f_o);
#endif
    return 0;
}