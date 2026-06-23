class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        vector<int> res(deck.size());
        queue<int> q;
        for(int i=0; i<deck.size(); i++) q.push(i);

        sort(deck.begin(), deck.end());
        int i=0, j;
        while(!q.empty()) {
            j = q.front();
            q.pop();
            res[j] = deck[i++];

            if(!q.empty()) {
                q.push(q.front());
                q.pop();
            }
        }
        return res;
    }
};
