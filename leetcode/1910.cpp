class Solution {
public:
    string removeOccurrences(string s, string part) {
        auto found = s.find_first_of(part[0]);
        while (found!=std::string::npos) {
            auto sub_str = s.substr(found, part.length());
            // cout << "sub: " << sub_str << endl;
            if (sub_str == part) {
                s.erase(found, part.length());
                found = s.find_first_of(part[0]);
            }
            else {
                found = s.find_first_of(part[0], found + 1);
            }
        }

        return s;
    }
};
