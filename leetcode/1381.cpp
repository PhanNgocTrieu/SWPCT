//https://leetcode.com/problems/design-a-stack-with-increment-operation/?envType=daily-question&envId=2024-09-30

#include <bits/stdc++.h>
using namespace std;

class CustomStack {
    int m_maxSize;
    int m_curSize;
    vector<int> m_data;
public:
    CustomStack(int maxSize) {
        m_maxSize = maxSize;
    }
    
    void push(int x) {
        if (m_data.size() >= m_maxSize) {
            cerr << "Size is maximum!" << endl;
            return;
        }
        m_data.push_back(x);
    }
    
    int pop() {
        if (m_data.size() < 1) {
            return -1;
        }
        auto get = m_data.back();
        m_data.pop_back();
        return get;
    }
    
    void increment(int k, int val) {
        if (m_data.size() < k) {
            for (auto& d : m_data) {
                d += val;
            }
        }
        else {
            for (auto i = 0; i < k; ++i) {
                m_data[i] += val;
            }
        }
    }

    void print_customerStack() {
        if (m_data.size() < 1) {
            return;
        }

        for (auto d : m_data) {
            cout << d << " ";
        }
        cout << endl;
    }
};

int main() {
    CustomStack csStack(3);
    csStack.push(1);
    csStack.push(2);
    csStack.print_customerStack();
    csStack.pop();
    csStack.print_customerStack();
    csStack.push(2);
    csStack.push(3);
    csStack.push(4);
    csStack.print_customerStack();
    csStack.increment(5, 100);
    csStack.print_customerStack();
    csStack.increment(2, 100);
    csStack.print_customerStack();
    return 0;
}