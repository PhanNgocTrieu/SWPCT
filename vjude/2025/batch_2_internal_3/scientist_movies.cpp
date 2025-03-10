// https://vjudge.net/contest/690988#problem/B
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
    }\

#define debug_pq(pq) \
    { \
        cout << #pq << ": "; \
        auto pq_ = pq; \
        while (!pq_.empty()) { \
            cout << pq_.top() << ' '; \
            pq_.pop(); \
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

typedef pair<ll, ll> pll;

// struct Compare {
//     constexpr bool operator()(
//         pair<ll,ll> const& a,
//         pair<ll,ll> const& b) const noexcept
//     {
//         return a.second > b.second;
//     }
// };

void solve() {
    ll ans = 1;
    ll n_sciences; cin >> n_sciences;
    map<ll, ll> science_map;
    for (ll i = 1; i <= n_sciences; i++) {
        ll l; cin >> l;
        science_map[l]++;
    }

    // debug_v(sciences);

    ll n_movies; cin >> n_movies;

    vector< pair<ll, ll> > movies(n_movies + 1);
    for (ll i = 1; i <= n_movies; i++) {
        ll title; cin >> title;
        movies[i].first = title;
    }

    for (ll i = 1; i <= n_movies; i++) {
        ll subtitle; cin >> subtitle;
        movies[i].second = subtitle;
    }

    ll max_very_pleasd = 0;
    ll max_almost_satisfied = 0;
    for (ll i = 1; i <= n_movies; ++i) {
        ll very_pleased = science_map[movies[i].first];
        ll almost_satisfied = science_map[movies[i].second];

        if (very_pleased > max_very_pleasd
        || (very_pleased == max_very_pleasd && almost_satisfied > max_almost_satisfied)) {
            ans = i;
            max_very_pleasd = very_pleased;
            max_almost_satisfied = almost_satisfied;
        }
    }

    cout << ans << '\n';
}

// #define READ_FILE
#define FILE_I "div7.in"
#define FILE_O "div7.out"

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
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