class Solution {
public:
    bool valid(int n, int A, int B) {
        if(A + B == n) {
            return true;
        }

        int temp = 0, pow = 1;
        while(B > 0) {
            temp = temp + (B % 10) * pow;
            pow *= 10;

            B /= 10;
            if(valid(n, A + temp, B)) return true;
        }
        return false;
    }
    int punishmentNumber(int n) {
        int res = 0;
        for(int i=1; i<=n; i++) {
            if(valid(i, 0, i*i)) res += i*i;
        }
        return res;
    }
};
