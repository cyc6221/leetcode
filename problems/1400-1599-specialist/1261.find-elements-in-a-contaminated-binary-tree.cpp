class FindElements {
public:
    set<int> s;

    void recover(TreeNode* root, int val) {
        if (!root) return;

        root->val = val;
        s.insert(val);

        recover(root->left, 2 * val + 1);
        recover(root->right, 2 * val + 2);
    }

    FindElements(TreeNode* root) {
        if(!root) return;
        root->val = 0;
        recover(root, 0);
    }

    bool find(int target) {
        return s.count(target);
    }
};
