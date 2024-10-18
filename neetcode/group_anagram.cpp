#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        string res = "";
        unordered_map<char, int> hash;
        for (auto c : t) {
            hash[c]++;
        }

        int index = 0;
        int size = s.length();
        while (
            index < size
        ) {
            auto get = s[index];
            if (hash.find(get) != hash.end()) {
                int _len = t.length();
                auto cpy = hash;
                int left = index;
                int right = index + 1;
                cpy[get]--;
                _len--;
                while (right < size) {
                    if (!_len) {
                        string tmp = s.substr(left, right - left);
                        if (res == "") {
                            res = tmp;
                        }
                        else {
                            res = res.length() < tmp.length() ? res : tmp;
                        }
                        cout << tmp << endl;
                        break;
                    }
                    auto get_r = s[right];
                    if (cpy.find(get_r) != cpy.end()
                    && cpy[get_r] > 0) {
                        cpy[get_r]--;
                        _len--;
                    }
                    right++;
                }
            }

            index++;
        }
        return res;
    }
};


int main() {
    auto get = Solution{}.topKFrequent({
        1, 2, 2, 3, 3
    }, 2);

    for (auto i : get) {
        cout << i << " ";
    }
    return 0;
}