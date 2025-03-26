#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define print_set(s) for (auto x : s) cout << x << " "; cout << endl;
#define print_vec(v) for (auto x : v) cout << x << " "; cout << endl;
#define print_pair_vec(v) for (auto x : v) cout << x.first << " " << x.second << endl;
void setIO(const string& file) {
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}

void solve() {
    string words;
    cin >> words;
    set<pair<char, char>> pairs;
    ll ans = 0;

    for (int i = 0; i < words.length(); ++i) {
        // cout << "mapping word: " << words[i] << '\n';
        map<char, ll> mc;
        // cout << "\t right side\n";
        for (int j = i + 1; j < words.length(); ++j) {
            if (words[j] == words[i]) {
                for (auto x : mc) {
                    if (x.second == 1) {
                        pair<char, char> p = {words[i], x.first};
                        if (p.first > p.second) {
                            swap(p.first, p.second);
                        }
                        if (pairs.find(p) == pairs.end()) {
                            // cout << "\t pair: " << words[i] << " " << x.first << '\n';
                            pairs.insert(p);
                            ans++;
                        }
                    }
                }
                break;
            }
            if (mc.find(words[j]) == mc.end()) {
                mc[words[j]]++;
            } else {
                mc[words[j]]--;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    setIO("circlecross");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}