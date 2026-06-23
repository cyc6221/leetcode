/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        vector<TreeNode*> st;
        int i = 0, n = traversal.size();

        while (i < n) {
            int depth = 0;
            while (i < n && traversal[i] == '-') {
                ++depth;
                ++i;
            }

            int val = 0;
            while (i < n && isdigit(traversal[i])) {
                val = val * 10 + (traversal[i] - '0');
                ++i;
            }

            TreeNode* node = new TreeNode(val);

            while ((int)st.size() > depth) st.pop_back();

            if (!st.empty()) {
                TreeNode* parent = st.back();
                if (!parent->left) parent->left = node;
                else parent->right = node;
            }

            st.push_back(node);
        }

        return st.empty() ? nullptr : st.front();
    }
};
