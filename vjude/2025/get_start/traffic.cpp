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

// ll n, m, s;
vector<ll> arr;
vector<ll> cows;


void solve()
{
    ll n;
    ll A[100], B[100];
    string T[100];

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> T[i] >> A[i] >> B[i];
    }

    ll a = 0;
    ll b = 1e9;

    for (int i = n - 1; i >= 0; --i) {
        if (T[i] == "none") {
            a = max(a, A[i]);
            b = min(b, B[i]);
        }

        if (T[i] == "off") {
            a += A[i];
            b += B[i];
        }

        if (T[i] == "on") {
            a -= B[i];
            b -= A[i];
            a = max((ll)0, a);
        }
    }

    cout << a << " " << b << '\n';

    a = 0;
    b = 1e9;

    for (int i = 0; i < n; ++i) {
        if (T[i] == "none") {
            a = max(a, A[i]);
            b = min(b, B[i]);
        }

        if (T[i] == "on") {
            a += A[i];
            b += B[i];
        }

        if (T[i] == "off") {
            a -= B[i];
            b -= A[i];
            a = max((ll)0, a);
        }
    }

    cout << a << " " << b << '\n';
}

int main()
{
    setIO("traffic");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t; cin >> t;
    // while (t--) {
    solve();
    // }

    return 0;
}