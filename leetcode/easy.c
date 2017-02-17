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

//14. Longest Common Prefix 
//Write a function to find the longest common prefix string amongst an array of strings. 
//the key point is the total loop time relates the prefix len multiply total strings size
//so we'd better to begin at 1th char in very string until we find no match and made str[0] as a comparison
/*
abcdefg, abcdefgh, abc, abcd, abcdefghijk 
*/
// the trick is to check whether str[i] size is small than str[0] size
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix = "";
        int i,j;
        
        if(0 == strs.size()) return prefix;
        
        for(i=0;i<strs[0].size();i++){
            for(j=1;j<strs.size();j++) {
                if(strs[j].size() <= i || strs[0][i] != strs[j][i])
                    return prefix;
            }
            prefix +=strs[0].at(i);
        }
        
        return prefix;
    }
};


// better Solution
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix = "";
        for(int idx=0; strs.size()>0; prefix+=strs[0][idx], idx++)
            for(int i=0; i<strs.size(); i++)
                if(idx >= strs[i].size() ||(i > 0 && strs[i][idx] != strs[i-1][idx]))
                    return prefix;
        return prefix;
    }
};

//476. Number Complement 
/*Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

Note:

    The given integer is guaranteed to fit within the range of a 32-bit signed integer.
    You could assume no leading zero bit in the integer’s binary representation.
*/
//the key point is finding the mask, eg, 0b101, the mask is 0b1111 1111 1111 1111 1111 1111 1111 1000
//if get the mask, it could be used to eliminate the Complement's leading 1 bit
class Solution {
public:
    int findComplement(int num) {
        unsigned mask = ~0;
        while (num & mask) mask <<= 1;
        return ~mask & ~num;
    }
};

//496. Next Greater Element I 
/* You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number. 

//key point is using stack to find the next Greater Element,push every element in stack and pop it to hash map if next Element if bigger than it until stack is empty or no one in stack is larger 
*/
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        map<int,int> my_map;
        stack<int> my_stack;
        
        for(int i = 0; i < nums.size(); i++) {
            while(!my_stack.empty() &&  nums[i] > my_stack.top()) {
                my_map.insert(pair<int,int>(my_stack.top(), nums[i]));    
                my_stack.pop();
            }
            my_stack.push(nums[i]);
        }
        
        for(int j = 0;j < findNums.size(); j++) {
            if(my_map.find(findNums[j]) != my_map.end()) {
                findNums[j] = my_map.find(findNums[j])->second;
            } else {
                findNums[j] = -1;
            }
            
        }
        
        return findNums;
    }
};

//412. Fizz Buzz 
/* Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.
*/
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> vs;

        for(int i = 1; i <= n;i++) {
            if(i % 15 == 0) {
                vs.push_back("FizzBuzz");
                continue;
            }
                
            if(i % 5 == 0) {
                vs.push_back("Buzz");
                continue;
            }
            
            if(i % 3 == 0) {
                vs.push_back("Fizz");
                continue;
            }
            
            vs.push_back(to_string(i));
        }
        
        return vs;
    }
};

//485. Max Consecutive Ones 
/*
 
Given a binary array, find the maximum number of consecutive 1s in this array.

Example 1:

Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.

Note:

    The input array will only contain 0 and 1.
    The length of input array is a positive integer and will not exceed 10,000
 
 */

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int max = 0;
        int count = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            if(1 == nums[i]) {
                count++;
                
            } else {
                max = (count > max) ? count : max;
                count = 0;
            }
            
        }
        
        max = (count > max) ? count : max;
        
        return max;
    }
}


//463. Island Perimeter

/* You are given a map in form of a two-dimensional integer grid where 1 
 * represents land and 0 represents water. Grid cells are connected
 * horizontally/vertically (not diagonally).
 * The grid is completely surrounded by water, 
 * and there is exactly one island (i.e., one or more connected land cells). 
 * The island doesn't have "lakes" (water inside that isn't connected to the
 * water around the island). One cell is a square with side length 1. 
 * The grid is rectangular, width and height don't exceed 100. 
 * Determine the perimeter of the island.

Example:

[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

Answer: 16
Explanation: The perimeter is the 16 yellow stripes in the image below:

*/

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int sum = 0;

        for(int i = 0;i < grid.size();i++) {

            for(int j = 0;j < grid[i].size();j++) {

                if(1 == grid[i][j]) {

                    sum +=4;

                    if(i > 0 && (1 == grid[i-1][j])) sum--; //left

                    if(j > 0 && (1 == grid[i][j-1])) sum--; //up

                    if(i + 1 < grid.size() && (1 == grid[i + 1][j])) sum--;//right

                    if(j + 1 < grid[i].size()  && (1 == grid[i][j + 1])) sum--;//down


                }

            }

        }
        
        return sum;
    }
};

//better one, not to calulate the twice the border of two land part
int islandPerimeter(vector<vector<int>>& grid) {
        int count=0, repeat=0;
        for(int i=0;i<grid.size();i++)
        {
            for(int j=0; j<grid[i].size();j++)
                {
                    if(grid[i][j]==1)
                    {
                        count ++;
                        if(i!=0 && grid[i-1][j] == 1) repeat++;
                        if(j!=0 && grid[i][j-1] == 1) repeat++;
                    }
                }
        }
        return 4*count-repeat*2;
    }


//292. Nim Game 
/*
 * You are playing the following Nim Game with your friend: 
 * There is a heap of stones on the table, each time one of you take turns to
 * remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.
 * Both of you are very clever and have optimal strategies for the game. 
 * Write a function to determine whether you can win the game given the number of stones in the heap.
 * For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend. 
*/
//the key idea is you two and all clever to chose the best move, and only left 4*n to the other can make the other fail
class Solution {
public:
    bool canWinNim(int n) {
        
        return (n % 4) > 0? 1 : 0;
    }
};

