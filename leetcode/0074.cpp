/*
    Links: https://leetcode.com/problems/search-a-2d-matrix/description/?envType=problem-list-v2&envId=binary-search
*/

#include <bits/stdc++.h>

using namespace std;

#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f
#define ll long long

using s = std::string;
using vll = vector<ll>;
using vb = vector<bool>;
using mll = map<ll, ll>;
using umll = unordered_map<ll, ll>;
using pll = pair<ll, ll>;
using pls = pair<ll, s>;
using vpll = vector<pair<ll, ll>>;

// loop templates
#define F_OR(i, a, b, s) for (ll i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define EACH(x, a) for (auto &x : a)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)

#define loop_1(s) for (ll i = 0; i < s; ++i)
#define loop_se(st, en) for (ll i = st; i <= en; ++i)

#define loop(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)

#define p_m(m)       \
    for (auto v : m) \
        cout << "(" << v.first << ", " << v.second << ")" << endl;

// debug templates
#define debugln cout << __FUNCTION__ << __LINE__ << endl;
#define debug(x) cout << #x << ": " << x << endl;
#define debugas(a, n)                         \
    for (int i = 0; i < n; ++i)               \
    {                                         \
        cout << #a << "[i]: " << a[i] << " "; \
    }                                         \
    cout << endl;
#define debugv(v)                        \
    cout << #v << " [ ";                 \
    for (int i = 0; i < (v).size(); ++i) \
        cout << v[i] << " ";             \
    cout << "]" << endl;
#define debugm(m)                                                             \
    cout << #m << " = [ " << endl;                                            \
    EACH(x, m) { cout << "(" << x.first << ", " << x.second << ")" << endl; } \
    cout << "]" << endl;
#define debugmp(m)                                                                                               \
    cout << #m << " = [ " << endl;                                                                               \
    EACH(x, m) { cout << "(" << x.first << ", {" << x.second.first << ", " << x.second.second << "})" << endl; } \
    cout << "]" << endl;
#define debugia(a, f, s) cout << "(" << f << "," << s << "): (" << a[f] << ", " << a[s] << ")" << endl;
#define debugvp(v)                                                              \
    cout << #v << " [" << endl;                                                 \
    EACH(x, v) { cout << " (" << x.first << ", " << x.second << ") " << endl; } \
    cout << "] " << endl;
#define debugvtp(v)                                                                                   \
    cout << #v << "[ " << endl;                                                                       \
    EACH(e, v) { cout << "(" << get<0>(e) << ", " << get<1>(e) << ", " << get<2>(e) << ")" << endl; } \
    cout << "]" << endl;
#define debugset(s)                  \
    cout << #s << "[ ";              \
    EACH(e, s) { cout << e << " "; } \
    cout << "] " << endl;

#define pb push_back
#define ppb pop_back

struct type_t {
    ll k;
    ll v{0};
};

bool check(const vector<ll>& times, const ll m, const ll target) {
    ll products = 0;
    for (const auto& t : times) {
        products += (m / t);
        if (products >= target) {
            return true;
        }
    }
    return false;
}

class Solution {
    bool bs(const vector<int>& array,int target) {
        int s = 0;
        int e = array.size();
        while (s < e - 1) {
            int m = (e + s) / 2;
            if (array[m] == target) { return true; }
            else if (array[m] < target) {
                s = m;
            }
            else {
                e = m;
            }
        }
        return false;
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int r = matrix.size();
        int c = matrix[0].size();
        if (c == 1 && r == 1) {
            return matrix[r-1][c-1] == target;
        }
        for (int i = 0; i < r; ++i) {
            auto getRowVector = matrix[i];
            if (getRowVector[0] == target
            || getRowVector[getRowVector.size() - 1] == target) {
                return true;
            }
            if (bs(getRowVector,target)) {
                return true;
            }
        }
        return false;
    }
};

// #define TESTCASE
// #define READ_FILE
void process()
{
    ll ans = 0;
    vector<vector<int>> matrix = {
        // {1,3,5,7},
        // {10,11,16,20},
        // {23,30,34,60}
        {1,3}
    };
    ans = Solution{}.searchMatrix(matrix, 3);
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifdef READ_FILE
    freopen("gymnastics.in", "r", stdin);
    freopen("gymnastics.out", "w", stdout);
#endif

#ifdef TESTCASE
    ll ts;
    cin >> ts;
    while (ts--)
    {
        process();
    }
#else
    process();
#endif

#ifdef READ_FILE
    // fclose(f_in);
    // fclose(f_out);
#endif
    return 0;
}
