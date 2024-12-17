#include <iostream>
using namespace std;
#define MAXN (1000)

int N;
int ID[MAXN + 10];

int CalLargestBlock(int id_ignore){
	int max_block_size = 0;
	int cur_size = 1;
	int preId = ID[0];
	for (int i = 1; i < N; i++){
		if (ID[i] == id_ignore) { continue; }
		if (ID[i] == preId) {
			cur_size++;
		}
		else {
			preId = ID[i];
			cur_size = 1;
		}

		if (max_block_size < cur_size) {
			max_block_size = cur_size;
		}
	}
	return max_block_size;
}

int Solve(){
	int sol = (int)1e7, max_cnt = 0;
	for (int i = 0; i < N; i++){
		int ret = CalLargestBlock(ID[i]);
		if ((max_cnt < ret) || ((max_cnt == ret) && (sol < ID[i]))) {
			max_cnt = ret;
			sol = ID[i];
		}
	}
	return sol;
}

void InputData(){
	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> ID[i];
	}
}

int main(){
	int ans;
	InputData();//입력 함수

	ans = Solve();

	cout << ans << "\n";//출력
	return 0;
}