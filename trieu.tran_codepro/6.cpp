#include <iostream>
#include <stack>
using namespace std;

int N; 
int W[100000 + 10];

void InputData(void) {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> W[i];
	}
}

int main(void) {

	InputData(); 
	int ans = 0;

	stack<int> st;
    for (int i = 0; i < N; i++) {
		while(!st.empty() && st.top() < W[i])
        {
            ans++;
            st.pop();
        }
        if(!st.empty()) ans++;
        if(st.empty() || st.top() != W[i]) st.push(W[i]);
	}

	cout << ans << endl;

	return 0;
}