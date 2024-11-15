class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        // 305ms
#ifdef COMMENT
        map<int, int> carPos;
        int s = cards.size();
        int ans = s;
        bool find = false;
        for (int i = 0; i < s; i++) {
            auto found = carPos.find(cards[i]);
            if (found != carPos.end()) {
                find = true;
                ans = min(ans,  i - found->second + 1);
            }
            carPos[cards[i]] = i;
        }
        cout << (find ? ans : -1) << "\n";
        return find ? ans : -1;
#else
        int lastSeen[1000005] = {};
        int ans = INT_MAX;
        for (int i = 0; i < cards.size(); i++) {
            if (lastSeen[cards[i]]){
                ans = min(ans, i - lastSeen[cards[i]] + 2);
            }
            lastSeen[cards[i]] = i + 1;
        }
        return ans == INT_MAX ? -1 : ans;
#endif
    }
};