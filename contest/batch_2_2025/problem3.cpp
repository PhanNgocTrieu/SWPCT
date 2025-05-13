#include <iostream>
#include <vector>
using namespace std;

int binary_search(const vector<long long>& b, int l, int r, long long v) {
    int mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if( b[mid] == v) return mid;
        else if (b[mid] < v) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}
int main() {
    int n;
    cin >> n;
    vector<long long> b;
    b.push_back(0);
    long long x, t, k;
    int l = 1, r = 0, count = 0, p, q;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        if(x < b[r] -  b[l - 1]) {
            while (r >= l && l < b.size() && x < b[r] -  b[l - 1]) {
                p = binary_search(b, l, r, x + b[l - 1]);
                q = binary_search(b, l, r, b[r] - x);
                if (p != -1 && q == -1) {
                    r--;
                    b.pop_back();
                } else if (q != -1 && p == -1) {
                    l++;
                }
                else {
                    if(b[r] - b[r-1] >= b[l] - b[l-1]) {r--; b.pop_back();}
                    else l++;
                }
            }
        }
        if(r < l || x > b[r] - b[l - 1]) {
            b.push_back(x + b[l - 1]);
            r++;
            count++;
        }
    }
    cout << count << endl;
    return 0;
}