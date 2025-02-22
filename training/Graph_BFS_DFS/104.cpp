/**
 * Problem: 104.Maximum Depth of Binary Tree
 *
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
    int _maxDepth = 0;
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        if (!root->left && !root->right) {
            return 1;
        }

        _maxDepth = max(1 + maxDepth(root->left), 1 + maxDepth(root->right));
        return _maxDepth;
    }
};
