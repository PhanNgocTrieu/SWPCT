// https://leetcode.com/problems/my-calendar-i/description/?envType=daily-question&envId=2024-09-26
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define max_size (unsigned long long)1e9

class MyCalendar {
    vector<long long> starts{max_size, 0};
    vector<long long> ends{max_size, 0};
public:
    MyCalendar() {
        // cout << "starts[2]: " << starts[2] << endl;
    }
    
    bool book(int start, int end) {
        if (starts.empty()) {
            starts[start] = 1;
            ends[start] = 1;
        }
        auto get = lower_bound(starts.begin(), starts.end(), start);
        // [this](int a, int b){
        //     return starts[a] == 1;
        // }
        if (get == starts.end()) {
            cout << "not found!" << endl;
        }
        else {
            cout << "found: " << *get << endl;
        }
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

int main() {
    MyCalendar * schedule = new MyCalendar();
    schedule->book(3, 5);
    schedule->book(4, 2);
    if (schedule) {
        delete schedule;
        schedule = nullptr;
    }
    return 0;
}