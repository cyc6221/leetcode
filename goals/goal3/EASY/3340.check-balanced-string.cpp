class Solution {
public:
    bool isBalanced(string num) {
        int even = 0, odd = 0;
        for(int i=0; i<num.size(); i++) {
            if(i % 2) even += num[i] - '0';
            else odd += num[i] - '0';
        }
        return even == odd;
    }
};