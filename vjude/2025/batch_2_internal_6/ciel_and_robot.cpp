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

unordered_map<char, function<void(ll& x, ll& y)>> operations = {
    {'U', [](ll& a, ll& b) { b++; }},
    {'L', [](ll& a, ll& b) { a--; }},
    {'R', [](ll& a, ll& b) { a++; }},
    {'D', [](ll& a, ll& b) { b--; }}
};

int g[110][2];
char s[110];
void solve()
{
    int i,n,u,v,x,y,dx,dy,k;
    scanf("%d%d%s",&u,&v,s);
    x=y=0;k=2000000000;
    for(i=0;s[i];i++)
    {
        if(s[i]=='U')
        {
            y++;
        }
        if(s[i]=='D')
        {
            y--;
        }
        if(s[i]=='L')
        {
            x--;
        }
        if(s[i]=='R')
        {
            x++;
        }
        g[i+1][0]=x;
        g[i+1][1]=y;
        // cout << "g[" << i+1 << "][0] = " << g[i+1][0] << ", g[" << i+1 << "][1] = " << g[i+1][1] << endl;
    }

    // for (ll j=0;j<=n;j++)
    // {
        // cout << "g[" << j << "][0] = " << g[j][0] << ", g[" << j << "][1] = " << g[j][1] << endl;
        // dx=u-g[j][0];
        // dy=v-g[j][1];
        // cout << "\tdx = " << dx << ", dy = " << dy << endl;
    // }

    n=i;
    for(i=0;i<=n;i++)
    {
        dx=u-g[i][0];
        dy=v-g[i][1];
        // cout << "\tdx = " << dx << ", dy = " << dy << endl;
        if(x)
        {
            k=dx/x;
            // cout << "\t[x] k = " << k << endl;
        }
        else if(y)
        {
            k=dy/y;
            // cout << "\t[y] k = " << k << endl;
        }
        else
        {
            k=1;
            // cout << "\t[else] k = " << k << endl;
        }
        if(k>=0&&x*k==dx&&y*k==dy)
            break;
    }
    cout << (i<=n?"Yes":"No");
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