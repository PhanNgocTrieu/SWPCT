#include <bits/stdc++.h>
using namespace std;

vector<long long> mm(LONG_MAX, -1);

long long minimum_coins(const vector<int>& coin, long long target) {
    if (mm[target] != -1) {
        return mm[target];
    }

    long long result = LONG_MAX;
    if (target == 0) {
        result = 0;
    }
    else {
        for (int i = 0; i < coin.size(); i++) {
            if (target - coin[i] >= 0) {
                result = min(result, minimum_coins(coin, target - coin[i]) + 1);
            }
        }
    }
    mm[target] = result;
    return result;
}


int main() {
    vector<int> coins = {1, 4, 5};
    int target = 13;
    cout << minimum_coins(coins, target) << endl;
    return 0;
}