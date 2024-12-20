#include <bits/stdc++.h>
using namespace std;

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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        bool reversed=0;
        while(!q.empty()){
            int qz=q.size();
            vector<TreeNode*> arr(qz);
            for(int i=0; i<qz; i++){
                auto Node=q.front();
                q.pop();
                if (Node->left) q.push(Node->left);
                if (Node->right) q.push(Node->right);
                if (reversed){
                    arr[i]=Node;
                    if (i>=qz/2)
                        swap(arr[i]->val, arr[qz-1-i]->val);
                }
            }
            reversed=!reversed;
        }
        return root;
    }
};

void printRoot(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    printRoot(root->right);
    printRoot(root->left);
}

int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(3);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(8);
    root->left->right = new TreeNode(13);
    root->right->left = new TreeNode(21);
    root->right->right = new TreeNode(34);

    auto r = Solution().reverseOddLevels(root);
    printRoot(r);
    return 0;
}