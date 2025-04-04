#include <bits/stdc++.h>
using namespace std;


/*
    extra planks:

    Fence consist N segments:
    A1 A2 A3 A4 ... An (as the height)

    M planks:
    B1 B2 B3 B4 ... Bn (as the height of planks)

    To increate the height
    -> getting the top from stack on the car and attaches it to that segment
    => Mean: get top of planks to apply to Segments

    After applying: A[i] = A[i] + B[k]

    No segment has more than on plank attached

    To attach: Cong will choose to do
    - can use the topmost plank on cart
    - discard one or more of the topmost planks and then use the next available plank
        When plank is discard -> not use again

    Cong will process this forward only once (from A1 to An).
*/

#define ll long long

ll N, M;

bool check(vector<ll> seg, queue<ll> planks, ll m) {
    // auto pq = planks;
    for (int i = 0; i < N; ++i) {
        // cout << "finding for seg[i]: " << seg[i] << "\n";
        if (seg[i] >= m) {
            continue;
        }
        while (!planks.empty()) {
            auto p = planks.front();
            planks.pop();
            if ((p + seg[i]) >= m) {
                // cout << "-> found p: " << p << endl;
                seg[i] = seg[i] + p;
                break;
            }
        }
    }
    for (auto s : seg) {
        if (s < m) {
            // cout << "return false!" << endl;
            return false;
        }
    }
    return true;
}

void solve() {
    cin >> N >> M;
    ll max_s = -1;
    vector<ll> segments(N);
    queue<ll> planks;

    for (int i = 0; i < N; ++i) {
        cin >> segments[i];
        max_s = max(max_s, segments[i]);
    }
    for (int j = 0; j < M; ++j) {
        ll p; cin >> p;
        planks.push(p);
    }

    ll l = 0;
    ll r = max_s + 1;
    ll ans = 1;
    while (l < r) {
        ll mid = (r + l) / 2;
        // cout << "l: " << l << " - r: " << r << endl;
        // cout << "mid: " << mid << endl;
        if (!check(segments, planks, mid)) {
            r = mid;
        } else {
            l = mid + 1;
            // cout << "\tans: " << ans << endl;
            ans = max(ans, mid);
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}