#include <iostream>
#include <algorithm>
using namespace std;

int N;//선수의 인원수 number of playersnumber of players
long long T;//시간 time
long long P[100000 + 10];//선수 초기 위치 player initial position
long long S[100000 + 10];//선수 속도 player speed
int group_first[100000 + 10];//각 그룹의 선두선수 leader of each group


void InputData() {
	cin >> N >> T;
	for (int i = 0; i < N; i++) {
		cin >> P[i] >> S[i];
	}
}

int solve() {
    // Create an array of indices to sort based on positions
    int indices[100000 + 10];
    for (int i = 0; i < N; i++) {
        indices[i] = i;
    }

    // Sort indices based on the positions of the runners
    sort(indices, indices + N, [](int a, int b) {
        return P[a] < P[b];
    });

    // Initialize the number of groups
    int num_groups = 0;

    // Iterate through the sorted indices to form groups
    for (int i = 0; i < N; i++) {
        int idx = indices[i];
        // If this runner is the first in a new group
        if (num_groups == 0 || S[idx] < S[group_first[num_groups - 1]]) {
            group_first[num_groups] = idx;
            num_groups++;
        }
    }

    return num_groups;
}

int main() {
	int ans = -1;
	InputData();//입력 Input

	//코드를 작성하세요 Write the code
    ans = solve();
	//출력 Output
	cout << ans << endl;
	for (int i = 0; i < ans; i++) cout << group_first[i] << " ";
	return 0;
}