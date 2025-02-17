#include <bits/stdc++.h>
#define ll long long
using namespace std;
bool count(long long m, long long n, ll c) {
    ll  ans = 0, l = n, s1 = 0, s2;
    cout << "m: " << m << " - n: " << n << " c: " << c << endl;
    while(l > 0 ) {
        s2 = min(n,m / l);
        if(s2 ==  s1) break;
        ans += l * (s2 - s1);
        cout << l << " * " << s2-s1 << " = " << l * (s2 - s1) << endl;
        s1 = s2;
        s2++;
        l = m/s2;
    }
    return ans >= c;
}
int main()
{
    cin.tie(0) -> sync_with_stdio(0);
    long long N, l, r, M, m;
    cin >> N;
    if( N > 1) {
        l = N;
        r = N * N / 2;
        M = N * N / 2 + 1;
        while(l < r - 1) {
            m =  (l + r) / 2;
            if(count(m, N, M))
                r = m;
            else
                l = m;
        }
        if(count(l, N, M)) cout << l;
        else cout << r;

    }
    else cout << 1 << endl;
    return 0;
}