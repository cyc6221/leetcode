class Solution {
public:
    string generateTag(string caption) {
        string res = "#";
        for(int i=0; i<caption.length(); i++) {
            if(i == 0 && caption[i] == ' ') {
                while(i < caption.length() && caption[i] == ' ')
                    i++;
            }
            if(caption[i] == ' ' && i+1 < caption.length() && caption[i+1] != ' ') {
                res += toupper(caption[i+1]);
                i++;
            }
            else if(caption[i] >= 'a' && caption[i] <= 'z') {
                res += caption[i];
            }
            else if(caption[i] >= 'A' && caption[i] <= 'Z') {
                res += tolower(caption[i]);
            }

            if(res.length() >= 100) return res;
        }
        return res;
    }
};
