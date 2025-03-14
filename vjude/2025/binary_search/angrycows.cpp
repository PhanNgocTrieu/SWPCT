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

// ll n, m, s;
vector<ll> arr;
vector<ll> cows;

bool validate(ll cows, ll R) {
    ll chose = 0;
    for (ll i = 1; i < arr.size(); ++i) {
        // cout << "arr[i]: " << arr[i] << " - arr[chose]: " << arr[chose] << " = " << arr[i] - arr[chose] <<'\n';
        if ((arr[i] - arr[chose]) <= (R * 2)) {
            continue;
        }
        else {
            cows--;
            chose = i;
        }
    }

    return cows > 0;
}

void solve()
{
    ll nHales, cows;
    cin >> nHales >> cows;
    arr.resize(nHales);
    for (ll i = 0; i < nHales; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    // debug_v(arr);
    ll low = 0, high = nHales;

    while (low < high) {
        ll mid = (high + low) / 2;
        // cout << "low: " << low << " high: " << high << " mid:" << mid << '\n';
        if (validate(cows, mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    cout << high << '\n';
}

int main()
{
    setIO("angry");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t; cin >> t;
    // while (t--) {
    solve();
    // }

    return 0;
}