#include <bits/stdc++.h>
using namespace std;

/*
    [s-e]: 5-23
        tt = 18h
        [s1]:5 - [e1]:7
        [s2]:7 - [e2]:17
        [s3]:17 - [e3]:23


    [0-7]: 400
    [7-17]: 300
    [17-24]: 350

 */
int forwardTime(int s, int e) {
    int tt = e - s;
    int s1=0,e1=0,s2=0,e2=0,s3=0,e3=0;
    int s_flag = 0;
    int e_flag = 0;
    
    if (s >= 0 && s < 7) {
        s1 = s;
        s2 = 0;
        s3 = 0;
        s_flag = 1;
    } else if (s >= 7 && s < 17) {
        s1 = 0;
        s2 = s;
        s3 = 0;
        s_flag = 2;
    }
    else {
        s3 = s;
        s2 = 0;
        s1 = 0;
        s_flag = 3;
    }

    if (e >= 0 && e < 7) {
        s2 = 0;
        s3 = 0;
        e1 = e;
        e2 = 0;
        e3 = 0;
    }
    else if (e >= 7 && e < 17) {
        if (s_flag == 1) {
            s2 = 7;
            e1 = 7;
        }
        e2 = e;
    }
    else {
        if (s_flag == 2) {
            e2 = 17;
        }
        else if (s_flag == 1) {
            s2 = 7;
            e2 = 17;
            e1 = 7;
        }
        s3 = 17;
        e3 = e;
    }
    // handle discount
    cout << (e1-s1) << " - " << (e2-s2) << " - " << (e3-s3) << endl; 

    double tt1 = (e1-s1);
    double tt2 = (e2-s2);
    double tt3 = (e3-s3);

    tt1 = (tt >= 7) ? tt1 * 0.15 * 300 : tt1 * 300;
    tt2 = (tt >= 6) ? tt2 * 0.1 * 400 : tt2 * 400;
    tt3 = (tt >= 4) ? tt3 * 0.12 * 350 : tt3 * 350;

    cout << tt1 << " - " << tt2 << " - " << tt3 << endl;

    return 0;
}

/*
    [s-e]: 23->18
        tt = 18h
        [s1]:23h - [e1]

 */
int backwardTime(int s, int e) {
    int tt = (24 - (s - e));
    int s1 = 0,e1 = 0,s2 = 0,e2 = 0,s3 = 0,e3 = 0;
    int tt1 = 0, tt2 = 0, tt3 = 0;
    int spls = 0;
    int epls = 0;
    int s_flag = 0;
    int e_flag = 0;

    if (s >= 17 && s <= 24) {
        s3 = s;
        s_flag = 3;
    } else if (s >= 7 && s > 17)  {
        s2 = s;
        s_flag = 2;
    }
    else {
        s1 = s;
        s_flag = 1;
    }

    if (e >= 17 && e <= 24) {
        e_flag = 3;
        e3 = e;
        if (s_flag == 3) {
            s1=0;
            e1=7;
            s2=7;
            e2=14;
            epls = 24;
            spls = 17;

            tt1 = (e1-s1);
            tt2 = (e2-s2);
            tt3 = (epls-s3) + (e3 - spls);
        }
    }
    else if (e >= 7 && e < 17) {
        e_flag = 2;
        e2 = e;
        if (s_flag == 3) {
            s1=0; e1=7;
            s2=7;
            e3 = 24;
            tt1 = (e1-s1);
            tt2 = (e2-s2);
            tt3 = (e3-s3);
        }
        else if (s_flag == 2) {
            spls = 7;
            s1 = 0;
            e1 = 7;
            s3 = 17;
            e3 = 24;
            epls = 17;
            tt1 = (e1-s1);
            tt2 = (epls - s2) + (e2 - spls);
            tt3 = (e3-s3);
        }
    }
    else {
        e_flag = 1;
        e1 = e;
        if (s_flag == 3) {
            s1=0;
            e3=24;
            tt1 = (e1-s1);
            tt2 = (e2-s2);
            tt3 = (e3-s3);
        }
        else if (s_flag == 2) {
            e2=17;
            s3=17;
            e3=24;
            tt1 = (e1-s1);
            tt2 = (e2-s2);
            tt3 = (e3-s3);
        }
        else {
            cout << tt1 << "-" << tt2 << "-" << tt3 << endl;
            spls = 0;
            s2 = 7; e2=14;
            s3 = 17;e3 = 24;
            epls = 7;
            tt1 = (epls - s1) + (e1 - spls);
            tt2 = (e2 - s2);
            tt3 = (e3 - s3);
        }
    }
    cout << tt1 << " - " << tt2 << " - " << tt3 << endl;
    // update discount
    tt1 = (tt >= 7) ? tt1 * 0.15 * 300 : tt1 * 300;
    tt2 = (tt >= 6) ? tt2 * 0.1 * 400 : tt2 * 400;
    tt3 = (tt >= 4) ? tt3 * 0.12 * 350 : tt3 * 350;

    cout << tt1 << " - " << tt2 << " - " << tt3 << endl;
    return 0;
}

int main() {
    int s, e;
    cin >> s >> e;
    (s < e) ? forwardTime(s,e) : backwardTime(s,e);
    return 0;
}