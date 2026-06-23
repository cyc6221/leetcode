class Solution {
public:
    bool canAliceWin(int n) {
        int turn = 10, sum = 0, who = 1;
        while(sum <= n) {
            sum += turn;
            turn--;
            who = (who + 1) % 2;
        }
        return who == 1;
    }
};
