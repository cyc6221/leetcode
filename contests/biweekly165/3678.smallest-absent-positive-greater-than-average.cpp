class Solution {
public:
    int smallestAbsent(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int sum = 0;
        set<int> s;
        for(auto& i : nums) {
            sum += i;
            s.insert(i);
        }
        int avg = sum / nums.size();
        int i = (nums[0] < 1) ? 1 : nums[0];

        while(sum > 0 && i <= avg) i++;

        while(s.count(i)) i++;
        return i;
    }
};
