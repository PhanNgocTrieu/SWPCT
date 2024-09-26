// https://leetcode.com/problems/my-calendar-i/description/?envType=daily-question&envId=2024-09-26
#include <bits/stdc++.h>
using namespace std;
class MyCalendar {
    map<long long, long long> m_calendar;
public:
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

int main() {
    MyCalendar * schedule = new MyCalendar();
    schedule->book(0, 2);
    if (schedule) {
        delete schedule;
        schedule = nullptr;
    }
    return 0;
}