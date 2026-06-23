class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int unplaced = 0;
        vector<int> placed(fruits.size(), 0);
        for(int i=0; i<fruits.size(); i++) {
            int check = 0;
            for(int j=0; j<baskets.size(); j++) {
                if(placed[j]) continue;
                if(fruits[i] <= baskets[j]) {
                    placed[j] = 1;
                    check = 1;
                    break;
                }
            }
            if(!check) unplaced++;
        }
        return unplaced;
    }
};
