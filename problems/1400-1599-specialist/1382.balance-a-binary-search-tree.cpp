class Solution {
public:
    vector<TreeNode*> nodes;

    void inorder(TreeNode* cur) {
        if (!cur) return;
        inorder(cur->left);
        nodes.push_back(cur);
        inorder(cur->right);
    }

    TreeNode* build(int l, int r) {
        if (l > r) return nullptr;
        int m = l + (r - l) / 2;
        TreeNode* root = nodes[m];
        root->left  = build(l, m - 1);
        root->right = build(m + 1, r);
        return root;
    }

    TreeNode* balanceBST(TreeNode* root) {
        if (!root) return nullptr;
        nodes.clear();
        inorder(root);
        return build(0, (int)nodes.size() - 1);
    }

};
