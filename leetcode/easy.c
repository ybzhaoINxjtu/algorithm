//461 hamming Distance
class Solution {
public:
        int countTotalOnes(int a)
        {
            a = (((a & 0xAAAAAAAA) >> 1) + (a & 0x55555555));
            a = (((a & 0xCCCCCCCC) >> 2) + (a & 0x33333333));
            a = (((a & 0xF0F0F0F0) >> 4) + (a & 0x0F0F0F0F));
            a = (((a & 0xFF00FF00) >> 8) + (a & 0x00FF00FF));
            a = (((a & 0xFFFF0000) >> 16) + (a & 0x0000FFFF));

            return a;
        }

    int hammingDistance(int x, int y) {
        
        if(x == y) return 0;
        
        return countTotalOnes(x ^ y);
        
    }
};

//404 Sum of Left Leaves
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        int sumOfLeftLeaves(TreeNode* root, bool isleft = false) {
        if (!root) return 0;
        if (!root->left && !root->right) return isleft ? root->val : 0;
        return sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right, false);
}
    }
};
