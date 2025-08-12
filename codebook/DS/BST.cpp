/************************************************************
 * Codebook: Binary Search Tree (BST) Utilities
 *
 * Overview:
 *   Common operations and helper functions for working
 *   with Binary Search Trees.
 *
 * Functions include:
 *   - Search
 *   - Insertion / Deletion
 *   - Traversals (recursive + iterative)
 *   - Min / Max
 *   - Height / Balance check
 *   - Inorder predecessor / successor
 *   - Lowest Common Ancestor
 ************************************************************/

#include <vector>
#include <stack>
#include <cstdlib> // for std::abs

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

/*********************** 1. Search *************************/
namespace BSTSearch {
static TreeNode* search(TreeNode* root, int key) {
    while (root && root->val != key) {
        root = (key < root->val) ? root->left : root->right;
    }
    return root;
}
}

/*********************** 2. Insertion **********************/
namespace BSTInsert {
static TreeNode* insert(TreeNode* root, int key) {
    if (!root) return new TreeNode(key);
    if (key < root->val) root->left = insert(root->left, key);
    else if (key > root->val) root->right = insert(root->right, key);
    return root; // no duplicates
}
}

/*********************** 3. Min / Max **********************/
namespace BSTMinMax {
static TreeNode* findMin(TreeNode* root) {
    while (root && root->left) root = root->left;
    return root;
}
static TreeNode* findMax(TreeNode* root) {
    while (root && root->right) root = root->right;
    return root;
}
}

/*********************** 4. Deletion ***********************/
namespace BSTDelete {
using namespace BSTMinMax;
static TreeNode* remove(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->val) root->left = remove(root->left, key);
    else if (key > root->val) root->right = remove(root->right, key);
    else {
        if (!root->left) {
            TreeNode* right = root->right;
            delete root;
            return right;
        } else if (!root->right) {
            TreeNode* left = root->left;
            delete root;
            return left;
        } else {
            TreeNode* successor = findMin(root->right);
            root->val = successor->val;
            root->right = remove(root->right, successor->val);
        }
    }
    return root;
}
}

/*********************** 5. Traversals *********************/
namespace BSTTraversal {
static void inorder(TreeNode* root, std::vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}
static void preorder(TreeNode* root, std::vector<int>& out) {
    if (!root) return;
    out.push_back(root->val);
    preorder(root->left, out);
    preorder(root->right, out);
}
static void postorder(TreeNode* root, std::vector<int>& out) {
    if (!root) return;
    postorder(root->left, out);
    postorder(root->right, out);
    out.push_back(root->val);
}
static void inorderIter(TreeNode* root, std::vector<int>& out) {
    std::stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }
        cur = st.top(); st.pop();
        out.push_back(cur->val);
        cur = cur->right;
    }
}
}

/*********************** 6. Height / Balance Check *********/
namespace BSTInfo {
static int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}
static bool isBalanced(TreeNode* root) {
    return heightOrNeg1(root) >= 0;
}
static int heightOrNeg1(TreeNode* node) {
    if (!node) return 0;
    int lh = heightOrNeg1(node->left);
    if (lh < 0) return -1;
    int rh = heightOrNeg1(node->right);
    if (rh < 0) return -1;
    if (std::abs(lh - rh) > 1) return -1;
    return 1 + std::max(lh, rh);
}
}

/*********************** 7. Predecessor / Successor ********/
namespace BSTNeighbors {
using namespace BSTMinMax;
static TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* succ = nullptr;
    while (root) {
        if (p->val < root->val) {
            succ = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return succ;
}
static TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {
    TreeNode* pred = nullptr;
    while (root) {
        if (p->val > root->val) {
            pred = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return pred;
}
}

/*********************** 8. Lowest Common Ancestor *********/
namespace BSTLCA {
static TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val)
            root = root->left;
        else if (p->val > root->val && q->val > root->val)
            root = root->right;
        else
            return root;
    }
    return nullptr;
}
}

/*********************** Example Usage *********************/
/*
TreeNode* root = nullptr;
root = BSTInsert::insert(root, 5);
root = BSTInsert::insert(root, 3);
root = BSTInsert::insert(root, 8);

TreeNode* found = BSTSearch::search(root, 3);
root = BSTDelete::remove(root, 5);

std::vector<int> vals;
BSTTraversal::inorder(root, vals);

bool balanced = BSTInfo::isBalanced(root);
TreeNode* minNode = BSTMinMax::findMin(root);
TreeNode* succ = BSTNeighbors::inorderSuccessor(root, minNode);
TreeNode* common = BSTLCA::lca(root, node1, node2);
*/
