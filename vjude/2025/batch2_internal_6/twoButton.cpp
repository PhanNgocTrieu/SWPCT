#include <bits/stdc++.h>
using namespace std;

#define ll long long

void setIO(const string &name) {
    if (freopen((name + ".in").c_str(), "r", stdin) == NULL) {
        cout << "Error opening input file" << endl;
        exit(1);
    }
    if (freopen((name + ".out").c_str(), "w", stdout) == NULL) {
        cout << "Error opening output file" << endl;
        exit(1);
    }
}

void solve() {
    ll m,n,x,ans,cnt=0;
    cnt=0;
    cin>>n>>m;
    while(n<m)
    {
        cnt+=m%2;
        m++;
        m/=2;
        cnt++;
    }
    x=(n-m);
    ans=x+cnt;
    cout<<ans<<endl;
}


int main() {
    // setIO("lifeguards");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ll t;
    // cin >> t;
    // while (t--)
        solve();

    return 0;
}

/*
#include <iostream>
using namespace std;

int main()
{
    int n, m, w(0);
    cin >> n >> m;
    while (n != m)
    {
        if (m > n)
            if (m % 2 == 0) m /= 2, w++;
            else m++, w++;
        else if (n > m) m++, w++;
    }
    cout << w << endl;
    return 0;
}

*/