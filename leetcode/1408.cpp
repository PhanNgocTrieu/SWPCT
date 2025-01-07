class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> matching_words;
        for (auto w : words) {
            for (auto w_ : words) {
                if (w_.length() < w.length()) {
                    auto _l = w.find(w_);
                    if (_l != std::string::npos 
                    && std::find(matching_words.begin(), matching_words.end(), w_) == matching_words.end()) {
                        matching_words.push_back(w_);
                    }
                }
            }
        }
        return matching_words;
    }
};
