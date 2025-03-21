// https://vjudge.net/contest/700173#problem/A
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    ll m, n;
    cin >> m >> n;

    // Read the grid
    vector<vector<ll>> grid(m, vector<ll>(n, -1));
    for (ll i = 0; i < m; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // Frequency maps for even and odd groups
    map<ll, ll> freq_even, freq_odd;
    ll count_even = 0, count_odd = 0;

    // Divide cells into even and odd groups
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i + j) % 2 == 0) {
                freq_even[grid[i][j]]++;
                count_even++;
            } else {
                freq_odd[grid[i][j]]++;
                count_odd++;
            }
        }
    }

    // Calculate the maximum frequency for each group
    ll max_even = 0, max_odd = 0;
    for (auto& p : freq_even) {
        max_even = max(max_even, p.second);
    }
    for (auto& p : freq_odd) {
        max_odd = max(max_odd, p.second);
    }

    // Calculate the total cost
    ll cost_even = count_even - max_even;
    ll cost_odd = count_odd - max_odd;
    cout << cost_even + cost_odd << endl;
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

/*
    #include <bits/stdc++.h>
    using namespace std;
    #define ll long long

    void solve() {
        ll m, n;
        cin >> m >> n;

        // Read the grid
        vector<vector<ll>> grid(m, vector<ll>(n, -1));
        for (ll i = 0; i < m; i++) {
            for (ll j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        // Frequency maps for even and odd groups
        map<ll, ll> freq_even, freq_odd;
        ll count_even = 0, count_odd = 0;

        // Divide cells into even and odd groups
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i + j) % 2 == 0) {
                    freq_even[grid[i][j]]++;
                    count_even++;
                } else {
                    freq_odd[grid[i][j]]++;
                    count_odd++;
                }
            }
        }

        // Find the two most frequent colors in each group
        vector<pair<ll, ll>> even_freq(freq_even.begin(), freq_even.end());
        vector<pair<ll, ll>> odd_freq(freq_odd.begin(), freq_odd.end());

        sort(even_freq.begin(), even_freq.end(), [](auto &a, auto &b) {
            return a.second > b.second;
        });
        sort(odd_freq.begin(), odd_freq.end(), [](auto &a, auto &b) {
            return a.second > b.second;
        });

        // Get the top two frequencies for each group
        ll max_even1 = even_freq.size() > 0 ? even_freq[0].second : 0;
        ll max_even2 = even_freq.size() > 1 ? even_freq[1].second : 0;
        ll color_even1 = even_freq.size() > 0 ? even_freq[0].first : -1;

        ll max_odd1 = odd_freq.size() > 0 ? odd_freq[0].second : 0;
        ll max_odd2 = odd_freq.size() > 1 ? odd_freq[1].second : 0;
        ll color_odd1 = odd_freq.size() > 0 ? odd_freq[0].first : -1;

        // Case 1: Paint both groups independently
        ll cost_independent = (count_even - max_even1) + (count_odd - max_odd1);

        // Case 2: Paint both groups using the same color
        ll cost_same_color = LLONG_MAX;
        if (color_even1 != color_odd1) {
            cost_same_color = (count_even - max_even1) + (count_odd - max_odd1);
        } else {
            cost_same_color = min(
                (count_even - max_even1) + (count_odd - max_odd2),
                (count_even - max_even2) + (count_odd - max_odd1)
            );
        }

        // Output the minimum cost
        cout << min(cost_independent, cost_same_color) << endl;
    }

    int main() {
        ll t;
        cin >> t;
        while (t--) {
            solve();
        }
        return 0;
    }
*/