class Solution {
public:
    bool hasMatch(string s, string p) {
        int star_pos = p.find('*');
        string prefix = p.substr(0, star_pos);
        string suffix = p.substr(star_pos + 1);

        if (prefix.length() + suffix.length() > s.length()) {
            return false;
        }

        for (int i = 0; i <= s.length() - prefix.length() - suffix.length(); i++) {
            if (s.substr(i, prefix.length()) != prefix) continue;

            for (int j = i + prefix.length(); j <= s.length() - suffix.length(); j++) {
                if (s.substr(j, suffix.length()) == suffix) {
                    return true;
                }
            }
        }

        return false;
    }
};
