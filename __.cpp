#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    // Create a vector of buckets for jobs based on waiting days
    vector<vector<int>> jobs(M + 1);

    for (int i = 0; i < N; i++) {
        int Ai, Bi;
        cin >> Ai >> Bi;
        if (Ai <= M) {
            jobs[Ai].push_back(Bi); // Add reward to the corresponding day bucket
        }
    }

    // Max-heap to store rewards
    priority_queue<int> maxHeap;
    long long totalReward = 0;

    // Iterate from the last day to the first day
    for (int day = M; day >= 1; day--) {
        // Add all jobs available on this day to the max-heap
        int stillAvailable = day;
        for (int reward : jobs[day]) {
            if (stillAvailable >= day) {
                maxHeap.push(reward);
                stillAvailable--;
            }
        }

        // Take the job with the maximum reward (if available)
        if (!maxHeap.empty()) {
            totalReward += maxHeap.top();
            maxHeap.pop();
        }
    }

    // Output the total maximum reward
    cout << totalReward << endl;

    return 0;
}