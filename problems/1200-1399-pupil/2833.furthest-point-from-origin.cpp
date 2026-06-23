class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int LR = 0, add = 0;
        for(auto& i : moves) {
            if(i == 'L') LR++;
            else if(i == 'R') LR--;
            else add++;
        }
        return abs(LR) + add;
    }
};
