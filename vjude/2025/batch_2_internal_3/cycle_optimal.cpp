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

struct step {
    ll x, y;
    ll prev_x, prev_y;
};

void do_bfs(const vector<string>&c, vector<vector<bool>>& vs, ll x, ll y) {
    queue<step> q;
    q.push({x,y,-1,-1});
    auto get_c = c[x][y];
    vs[x][y] = true;
    while(!q.empty()) {
        auto v = q.front();
        q.pop();

        for (int i = 0; i <  4; ++i) {
            ll nx = v.x + dx[i];
            ll ny = v.y + dy[i];
            if (
                nx >= 0 && nx < row
                && ny >= 0 && ny < col
                && c[nx][ny] == get_c
            ) {
                if (nx != v.prev_x || ny != v.prev_y) {
                    if (vs[nx][ny]) {
                        cout << "Yes\n";
                        exit(0);
                    }
                    if (!vs[nx][ny]) {
                        vs[nx][ny] = true;
                        q.push({nx, ny, v.x, v.y});
                    }
                }
            }
        }
    }
}

void callhandl_bfs(const vector<string>& c) {
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    for (ll i = 0; i < row; ++i) {
        for (ll j = 0; j < col; ++j) {
            if (!visited[i][j]) {
                do_bfs(c, visited, i, j);
            }
        }
    }
}

void solve()
{
    cin >> row >> col;
    vector<string> cycle(row, string(col, '0'));
    for (int i = 0; i < row; i++)
    {
        cin >> cycle[i];
    }

    callhandl_bfs(cycle);
    cout << "No" << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t; cin >> t;
    // while (t--) {
    solve();
    // }

    return 0;
}