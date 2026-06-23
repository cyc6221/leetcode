class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int res = 0;
        for(int i=0; i < arr.size(); i++) {
            for(int j=i+1; j < arr.size(); j++) {
                for(int k=j; k < arr.size(); k++) {
                    int a = arr[i], b = arr[j];
                    for(int l=i+1; l < j; l++) {
                        a ^= arr[l];
                    }
                    for(int l=j+1; l <= k; l++) {
                        b ^= arr[l];
                    }
                    if(a == b) res++;
                }
            }
        }
        return res;
    }
};
