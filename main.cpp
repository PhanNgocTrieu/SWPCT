#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

int N; // 선수의 인원수 number of players
long long T; // 시간 time
long long P[100000 + 10]; // 선수 초기 위치 player initial position
long long S[100000 + 10]; // 선수 속도 player speed
struct runner {
    long long start;
    long long pos;
    long long spd;
};
vector<runner> runners;
vector<runner> group_first; // 각 그룹의 선두선수 leader of each group
void InputData() {
    cin >> N >> T;
    for (int i = 1; i <= N; i++) {
        cin >> P[i] >> S[i];
        runners.push_back({
            i,
            P[i],
            S[i]
        });
    }
}

int solve() {
    // Create an array of indices to sort based on positions
    // Sort indices based on the positions of the runners
    sort(runners.begin(), runners.end(), [](const runner& a, const runner& b) {
        return a.pos < b.pos;
    });
    // Initialize the number of groups
    int num_groups = 0;

    for (auto& r : runners) {
        r.pos += r.spd * T;
    }
    // cout << "After running \n";
    // for (auto r : runners) {
    //     cout << "(r.start, r.pos, r.spd): " << r.start << "," << r.pos << "," << r.spd << "\n";
    // }
    group_first.push_back(runners[runners.size() - 1]);
    num_groups++;
    for (int i = N - 1; i >= 0; --i) {
        if (runners[i].spd < group_first[num_groups - 1].spd
        && runners[i].pos < group_first[num_groups - 1].pos) {
            // cout << "pushing: (" << runners[i].start << "," << runners[i].spd << "," << runners[i].pos << ")" << "\n";
            group_first.push_back(runners[i]);
            num_groups++;
        }
        else if (runners[i].spd >= group_first[num_groups - 1].spd
        && runners[i].pos < group_first[num_groups-1].pos) {
            // cout << "pushing: (" << runners[i].start << "," << runners[i].spd << "," << runners[i].pos << ")" << "\n";
            group_first.push_back(runners[i]);
            num_groups++;
        }
    }
    return num_groups;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
// #define READ_FILE
#ifdef READ_FILE
    FILE* f_in = freopen("pails.in", "r+", stdin);
    FILE* f_out = freopen("pails.out", "w+", stdout);
#endif

    int ans = -1;
    InputData(); // 입력 Input

    // 코드를 작성하세요 Write the code
    ans = solve();
    // 출력 Output
    cout << ans << endl;
    for (auto f : group_first) {
        cout << f.start << " ";
    }
    cout << "\n";

#ifdef READ_FILE
    fclose(f_in);
    fclose(f_out);
#endif

    return 0;
}