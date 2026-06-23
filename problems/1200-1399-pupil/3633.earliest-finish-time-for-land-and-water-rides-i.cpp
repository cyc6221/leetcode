class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int res = INT_MAX;

        int m = landStartTime.size();
        int n = waterStartTime.size();

        for(int i=0; i<m; i++) {
            int land = landStartTime[i] + landDuration[i];
            for(int j=0; j<n; j++) {
                if(land <= waterStartTime[j]) {
                    res = min(res, waterStartTime[j] + waterDuration[j]);
                }
                else {
                    res = min(res, land + waterDuration[j]);
                }
            }
        }

        for(int j=0; j<n; j++) {
            int water = waterStartTime[j] + waterDuration[j];
            for(int i=0; i<m; i++) {
                if(water <= landStartTime[i]) {
                    res = min(res, landStartTime[i] + landDuration[i]);
                }
                else {
                    res = min(res, water + landDuration[i]);
                }
            }
        }

        return res;
    }
};