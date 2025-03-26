#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> table(n, vector<int>(m));

    // Input the table
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> table[i][j];
        }
    }

    // Frequency maps for the two groups
    map<int, int> group1_freq, group2_freq;

    // Divide the table into two groups based on the checkerboard pattern
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i + j) % 2 == 0) {
                group1_freq[table[i][j]]++;
            } else {
                group2_freq[table[i][j]]++;
            }
        }
    }

    // Find the most frequent colors in both groups
    int max_group1_color = 0, max_group1_count = 0;
    for (map<int, int>::iterator it = group1_freq.begin(); it != group1_freq.end(); ++it) {
        if (it->second > max_group1_count) {
            max_group1_color = it->first;
            max_group1_count = it->second;
        }
    }

    int max_group2_color = 0, max_group2_count = 0;
    for (map<int, int>::iterator it = group2_freq.begin(); it != group2_freq.end(); ++it) {
        if (it->second > max_group2_count) {
            max_group2_color = it->first;
            max_group2_count = it->second;
        }
    }

    // Calculate the minimum number of steps
    int total_cells = n * m;
    int group1_cells = (n * m + 1) / 2; // Cells in group 1
    int group2_cells = total_cells - group1_cells; // Cells in group 2

    int cost1 = (group1_cells - max_group1_count) + (group2_cells - max_group2_count);
    int cost2 = INT_MAX;

    // Ensure the colors are different for the two groups
    if (max_group1_color != max_group2_color) {
        cost2 = cost1;
    } else {
        // Try alternative colors for one of the groups
        int second_max_group1_count = 0;
        for (map<int, int>::iterator it = group1_freq.begin(); it != group1_freq.end(); ++it) {
            if (it->first != max_group1_color) {
                second_max_group1_count = max(second_max_group1_count, it->second);
            }
        }

        int second_max_group2_count = 0;
        for (map<int, int>::iterator it = group2_freq.begin(); it != group2_freq.end(); ++it) {
            if (it->first != max_group2_color) {
                second_max_group2_count = max(second_max_group2_count, it->second);
            }
        }

        cost2 = min(
            (group1_cells - second_max_group1_count) + (group2_cells - max_group2_count),
            (group1_cells - max_group1_count) + (group2_cells - second_max_group2_count)
        );
    }

    // Output the minimum cost
    cout << min(cost1, cost2) << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}