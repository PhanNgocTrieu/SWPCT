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

            int left = 0;
            int right = 1;
            int index = 0;
            int size = s.length();
            while (
                left < size
                && index < size
            ) {
                auto get = s[index];
                auto cpy = hash;
                int _len = t.length();
                if (find(hash.begin(), hash.end()) != hash.end()) {
                    left = index;
                    right = index + 1;
                    hash[get]--;
                    while (right < size) {
                        if (!_len) {
                            string tmp = s.substr(s.begin() + left, right - left);
                            if (res == "") {
                                res = tmp;
                            }
                            else {
                                res = res.length() < tmp.length() ? res : tmp;
                            }
                            break;
                        }
                        auto get_r = s[right];
                        
                        if (hash[get_r]) {
                            hash[get]--;
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