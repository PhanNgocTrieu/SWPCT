// https://vjudge.net/contest/690982#problem/F
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define debug_q(q)                     \
    {                                  \
        auto q_ = q;                   \
        while (!q_.empty())            \
        {                              \
            cout << q_.front() << ' '; \
            q_.pop();                  \
        }                              \
        cout << '\n';                  \
    }

#define debug_pq(pq)                  \
    {                                 \
        cout << #pq << ": ";          \
        auto pq_ = pq;                \
        while (!pq_.empty())          \
        {                             \
            cout << pq_.top() << ' '; \
            pq_.pop();                \
        }                             \
        cout << '\n';                 \
    }

#define debug_v(v)            \
    {                         \
        cout << #v << ": ";   \
        for (auto x : v)      \
        {                     \
            cout << x << ' '; \
        }                     \
        cout << '\n';         \
    }

#define debug_vv(vv)                        \
    {                                       \
        for (int i = 0; i < vv.size(); i++) \
        {                                   \
            cout << "v[" << i << "]: ";     \
            for (auto x : vv[i])            \
            {                               \
                cout << x << ' ';           \
            }                               \
            cout << '\n';                   \
        }                                   \
    }

#define debug_x(x)                       \
    {                                    \
        cout << #x << ": " << x << '\n'; \
    }

#define debug_msg(msg)        \
    {                         \
        cout << #msg << '\n'; \
    }

#define debug_map(m)                                         \
    {                                                        \
        for (auto it = m.begin(); it != m.end(); it++)       \
        {                                                    \
            cout << it->first << ": " << it->second << '\n'; \
        }                                                    \
    }

#define ans_v(v)              \
    {                         \
        for (auto x : v)      \
        {                     \
            cout << x << ' '; \
        }                     \
        cout << '\n';         \
    }

typedef long long ll;
typedef pair<ll, ll> pll;
ll row, col;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

ll n, m, s;
vector<ll> arr;
vector<ll> cows;


void solve()
{
    cin >> n;
    vector<ll> r(n);
    for (ll i = 0; i < n; i++) {
        cin >> r[i];
    }

    // Compute prefix sums
    vector<ll> prefix_sum(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + r[(i - 1) % n];
    }

    // debug_v(prefix_sum);

    ll total_cows = prefix_sum[n]; // Total number of cows
    ll min_distance = LLONG_MAX;

    // Calculate total walking distance for each starting room
    for (int start = 0; start < n; start++) {
        ll distance = 0;
        for (int i = 0; i < n; i++) {
            int room = (start + i) % n;
            distance += r[room] * i; // Distance for cows in room
        }
        min_distance = min(min_distance, distance);
    }

    cout << min_distance << endl;

}

int main()
{
    setIO("cbarn");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t; cin >> t;
    // while (t--) {
    solve();
    // }

    return 0;
}