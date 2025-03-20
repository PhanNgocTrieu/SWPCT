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

vector<ll> count_freq(string s) {
	vector<ll> freq(26);
	for (char c : s) { freq[c - 'a']++; }
	return freq;
}


void solve()
{
    cin >> n;
    vector<ll> ans(26, 0);
    for (int i = 0; i < n; ++i) {
        string word1, word2;
        cin >> word1 >> word2;
        vector<ll> freq1 = count_freq(word1);
        vector<ll> freq2 = count_freq(word2);
        for (int i = 0; i < 26; ++i) {
            ans[i] += max(freq1[i], freq2[i]);
        }
    }

    for (int i = 0; i < 26; ++i)
    {
        // cout << (char)('a' + i) << ": " << ans[i] << '\n';
        cout << ans[i] << '\n';
    }
}

int main()
{
    setIO("blocks");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t; cin >> t;
    // while (t--) {
    solve();
    // }

    return 0;
}