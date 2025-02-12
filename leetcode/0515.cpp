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
    vector<int> ans;
    void bfs(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            int maxVal = INT_MIN;
            while (size--) {
                auto n = q.front();
                q.pop();
                maxVal = max(n->val, maxVal);
                if (n->left != nullptr) {
                    q.push(n->left);
                }
                if (n->right != nullptr) {
                    q.push(n->right);
                }
            }
            if (size <= 0) {
                ans.push_back(maxVal);
            }
        }
    }
public:
    Solution() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);  
        cout.tie(NULL);
    }
    vector<int> largestValues(TreeNode* root) {
        if (!root) return vector<int>{};
        bfs(root);
        return ans;
    }
};
