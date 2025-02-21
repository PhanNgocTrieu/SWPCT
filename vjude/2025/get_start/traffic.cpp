// https://vjudge.net/contest/690982#problem/E
#include <bits/stdc++.h>

using namespace std;

#define ll long long

class Compare {
public:
    bool operator() (pair<ll,ll> a, pair<ll,ll> b) {
        return a.first >= b.first;
    }
};

/*
    Algorithm:

    Case:
        [1] on 1 1
        [2] none 10 14      - highway
        [3] none 11 15      - highway
        [4] off 2 3

    Solved:
        enter on-ramps:
            [1;1] -> only one car
        from [2] and [3], we can see
            rate for [2] -> from 10 cars to 14 cars
            rate for [3] -> from 11 cars to 15 cars

            => highway: can contains [11;14] cars
               => if 11 cars -> consistent with both cases
               => if 10 cars -> not consistent with [3]
               => if 15 cars -> not consistent with [2]
            => so the suitable is [11;14]

        And when on-ramps are on [1;1] -> only one car

        Before going main highway, we should has less than 1 car
            [11;14] - [1;1] = [10;13]

        Exit on off-ramps: [2;3]
            Minimum cars on off-ramps: 2 cars
            Maximum cars on off-ramps: 3 cars

            To get maximum of cars after getting out from highway
                we do:
                    [14] cars (highway) - [2] cars (off-ramps) = [12] cars

            To get minimum of cars after getting out from highway
                we do:
                    [11] cars (highway) - [3] cars (off-ramps) = [8] cars

            => range(8;12)


    Case:
        [1] on 2 3
        [2] none 10 14      - highway
        [3] none 11 15      - highway
        [4] off 1 3

    Solved:
        enter on-ramps:
            [2] and [3] -> [11;14]
            [11;14] - [2;3] = [9;11]

        Exit on off-ramps: [1;3]
            [2] and [3] -> [11;14]
            -> [11] - [3] = [8]
            -> [14] - [1] = [13]

*/

void solve() {
    ll n; cin >> n;
    vector<pair<string, pair<ll,ll>>> v;
    for (int i = 0; i < n; i++) {
        string s; ll a, b; cin >> s >> a >> b;
        v.push_back({s, {a, b}});
    }

    pair<ll,ll> near_on = {0, 0};
    pair<ll,ll> near_off = {0, 0};
    pair<ll,ll> hw = {0, 1e9};
    ll first_min = 0, first_max = 1e9;
    ll second_min = 1e9, second_max = 0;

    for (auto x : v) {
        if (x.first == "on") {
            near_on = {x.second.first, x.second.second};
        }
        else if (x.first == "none") {
            hw = {
                max(x.second.first, hw.first),
                min(x.second.second, hw.second)
            };
            first_min = max(hw.first - near_on.first, first_min);
            first_max = min(hw.second - near_on.second, first_max);
            // cout << "hw: " << hw.first << " " << hw.second << endl;
        }
        else {
            hw = {
                0,
                1e9
            };
        }
    }

    // cout << "pri: (" << first_min << "," << first_max << ")" << endl;
    cout << first_min << " " << first_max << endl;


    for (auto x : v) {
        if (x.first == "off") {
            near_off = {x.second.first, x.second.second};
            second_min = min(hw.first - near_off.second, second_min);
            second_max = max(hw.second - near_off.first, second_max);
        }
        else if (x.first == "none") {
            hw = {
                max(x.second.first, hw.first),
                min(x.second.second, hw.second)
            };
            // cout << "hw: " << hw.first << " " << hw.second << endl;
        }
        else {
            hw = {
                0,
                1e9
            };
        }
    }

    // cout << "after: (" << second_min << "," << second_max << ")" << endl;
    cout << second_min << " " << second_max << endl;
}

#define READ_FILE
// #define ASSIGNMENT

#ifndef ASSIGNMENT
#define FILE_I "./file/traffic.in"
#define FILE_O "./file/traffic.out"
#else
#define FILE_I "traffic.in"
#define FILE_O "traffic.out"
#endif

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#ifdef READ_FILE
    auto f_i = freopen(FILE_I, "r", stdin);
    auto f_o = freopen(FILE_O, "w", stdout);
#endif

    // int t; cin >> t;
    // while (t--) {
        solve();
    // }

#ifdef READ_FILE
    fclose(f_i);
    fclose(f_o);
#endif
    return 0;
}