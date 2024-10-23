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
#include <bits/stdc++.h>
using namespace std;
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
        long long kthLargestLevelSum(TreeNode* root, int k) {
            queue<TreeNode*> q;
            vector<long long> v;
            q.push(root);
            while(!q.empty()){
                int n = q.size();
                long long val = 0;
                while(n--){
                    auto node = q.front();
                    q.pop();
                    val += node -> val;
                    if(node -> left) q.push(node -> left);
                    if(node -> right) q.push(node -> right);
                }
                v.push_back(val);
            }
            if(v.size() < k) return -1;
            sort(v.rbegin(), v.rend());
            return v[k - 1];
        }
};

auto init = []()
{ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();