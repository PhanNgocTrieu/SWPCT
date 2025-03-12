// https://vjudge.net/contest/690988#problem/B
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
vector<ll> arrivals;

bool validate(ll wait_t) {
    // cout << "wait_t: " << wait_t << '\n';
    ll bus = 0;
    ll cow = 0;
    ll lcow = 0;
    while (cow < n) {
        if (cow == lcow) {
            // cout << "\tupdate bus" << '\n';
            bus++;
        }

        if (arrivals[cow] - arrivals[lcow] > wait_t) {
            // cout << "\tarrivals[cow]: " << arrivals[cow] << " arrivals[lcow]: " << arrivals[lcow] << " > wait_t" << '\n';
            lcow = cow;
        }
        else if (cow - lcow + 1 == s) {
            // cout << "\tcow: " << cow << " lcow: " << lcow << " == s" << '\n';
            lcow = ++cow;
        }
        else {
            ++cow;
            // cout << "\tupdate cow: " << cow << '\n';
        }
    }
    // cout << "\tbus: " << bus << '\n';
    return bus <= m;
}

void solve()
{
    cin >> n >> m >> s;
    arrivals.resize(n);
    for (auto& v : arrivals) {
        cin >> v;
    }
    sort(arrivals.begin(), arrivals.end());
    // debug_v(arrivals);
    ll ans = 0;

    ll l = 0, r = arrivals[n-1] - arrivals[0];

    while(l < r) {
        ll m = (l + r) / 2;
        if (validate(m)) {
            r = m;
        }
        else {
            l = m + 1;
        }
    }

    cout << l << '\n';
}

int main()
{
    setIO("convention");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t; cin >> t;
    // while (t--) {
    solve();
    // }

    return 0;
}