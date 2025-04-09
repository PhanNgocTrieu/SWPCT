#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// Function to calculate the total covered time with one lifeguard removed
int calculateMaxCoverage(vector<pair<int, int>> &shifts, int n) {
    vector<int> coverage(1001, 0);

    // Mark the coverage for all lifeguards
    for (int i = 0; i < n; i++) {
        for (int t = shifts[i].first; t < shifts[i].second; t++) {
            coverage[t]++;
        }
    }

    int totalCoverage = 0;
    for (int t = 0; t <= 1000; t++) {
        if (coverage[t] > 0) totalCoverage++;
    }

    int maxCoverage = 0;

    // Try removing each lifeguard and calculate the coverage
    for (int i = 0; i < n; i++) {
        for (int t = shifts[i].first; t < shifts[i].second; t++) {
            coverage[t]--;
        }

        int currentCoverage = 0;
        for (int t = 0; t <= 1000; t++) {
            if (coverage[t] > 0) currentCoverage++;
        }

        maxCoverage = max(maxCoverage, currentCoverage);

        for (int t = shifts[i].first; t < shifts[i].second; t++) {
            coverage[t]++;
        }
    }

    return maxCoverage;
}

int main() {
    ifstream fin("lifeguards.in");
    ofstream fout("lifeguards.out");

    int n;
    fin >> n;

    vector<pair<int, int>> shifts(n);
    for (int i = 0; i < n; i++) {
        fin >> shifts[i].first >> shifts[i].second;
    }

    int result = calculateMaxCoverage(shifts, n);
    fout << result << endl;

    return 0;
}