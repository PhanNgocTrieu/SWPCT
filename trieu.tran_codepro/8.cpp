#include <iostream>
#include <vector>
using namespace std;

int N;
long long T;//시간 time
long long P[100000 + 10];//선수 초기 위치 player initial position
long long S[100000 + 10];//선수 속도 player speed
long long E[100000 + 10];//선수 속도 player speed
int group_first[100000 + 10];//각 그룹의 선두선수 leader of each group


void InputData() {
	cin >> N >> T;
	for (int i = 0; i < N; i++) {
		cin >> P[i] >> S[i];
        E[i] = P[i] +  T * S[i];
	}
}

int main() {
	int ans = 0, k = 0;
	InputData();
    long long cur = 2e18;
    for(int i = N - 1; i >= 0; i--) {
        if(E[i] < cur) {
            group_first[ans] = i + 1;
            cur = E[i];
            ans++;
        }
    }

	cout << ans << endl;
	for (int i = 0; i < ans; i++) cout << group_first[i] << " ";
	return 0;
}