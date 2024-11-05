#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> array_(m * n);
        int i = 0;
        for (auto m : matrix) {
            for (auto v : m) {
                array_[i++] = v;
            }
        }
        // debug
        for(auto a : array_) {
            cout << a << " ";
        }
        cout << endl;

        int s = 0;
        int e = (m * n) - 1;
        while (s <= e) {
            int m = (e + s) / 2;
            // debug
            cout << "m: " << m << " -> " << array_[m] << endl;
            if (array_[m] == target) {
                cout << "return true" << endl;
                return true;
            }
            else if (target > array_[m])  {
                s = m + 1;
            }
            else {
                e = m - 1;
            }
        }
        cout << "return false" << endl;
        return false;
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    vector<vector<int>> matrix = {
        {1,3,5,7},
        {10,11,16,20},
        {23,30,34,60}
    };

    Solution{}.searchMatrix(matrix, 10);

    return false;
}