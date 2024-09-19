// https://codeforces.com/problemset/problem/231/A
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
void solve() {
    ll n;
    cin >> n;
    vector<ll> friends(3,0);
    ll res = 0;
    while (n--) {
        cin >> friends[0] >> friends[1] >> friends[2];
        int numFriends = 0;
        for (auto& f : friends) {
            if (f) {
                numFriends++;
                if (numFriends > 1) {
                    res++;
                    break;
                }
            }
        }
    }
    cout << res << endl;
}

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    solve();
    return 0;
}