class Solution {
public:
    string answerString(string word, int numFriends) {
        if (numFriends == 1)
            return word;
        int n = word.length(), i;
        int split_length = n - numFriends;
        string m, cur = "";
        for (i = 0; i < n; i++) {
            cur = word.substr(i, split_length + 1);
            if (cur > m) {
                m = cur;
            }
        }
        return m;
    }
};
