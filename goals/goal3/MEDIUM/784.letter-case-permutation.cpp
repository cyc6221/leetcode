// # **Key Idea**

// This is a **backtracking / DFS (Depth-First Search)** problem.
// For each character in the string:

// * If it's a **letter**, we branch into **two recursive calls**: one for lowercase, one for uppercase.
// * If it's a **digit**, we only continue with the current character (no branching).

// This way, we explore all combinations of letter case transformations.

// ---

// # **Algorithm**

// 1. Start from index `0` and an empty string `cur`.
// 2. If we reach the end of the string (`i == s.length()`), we add the current combination `cur` to the result list.
// 3. Otherwise:

//    * If `s[i]` is a letter:

//      * Add its lowercase form to `cur`, recurse to the next index.
//      * Change that character to uppercase, recurse again.
//      * Backtrack by removing the character.
//    * If `s[i]` is a digit:

//      * Just add the digit to `cur` and recurse once.
// 4. Return the result list after all recursive calls finish.

// ---

// # **Complexity Analysis**

// * **Time Complexity**:
//   ( O(2^L) ), where ( L ) is the number of letters. Each letter doubles the number of combinations.
// * **Space Complexity**:
//   ( O(L) ) for the recursion stack and current string. The result array holds ( 2^L ) strings.

// ---

// # Code
// ```cpp []
class Solution {
public:
    void dfs(vector<string>& res, string &s, int i, string &cur) {
        if(i == s.length()) {
            res.push_back(cur);
            return;
        }

        int a = s[i] - 'a', A = s[i] - 'A';
        if(A >= 0 && A < 26) s[i] = A + 'a', a = A;

        cur.push_back(s[i]);
        dfs(res, s, i+1, cur);
        cur.pop_back();
        
        if(a >= 0 && a < 26) {
            cur.push_back(a + 'A');
            dfs(res, s, i+1, cur);
            cur.pop_back();
        }
    }
    vector<string> letterCasePermutation(string s) {
        vector<string> res;
        string cur = "";
        dfs(res, s, 0, cur);
        return res;
    }
};
// ```