class Solution {
public:
    int maxBottlesDrunk(int A, int B) {
        int res = A;
        while(A >= B) {
            res ++;
            A -= B-1;
            B++;
        }
        return res;
    }
};