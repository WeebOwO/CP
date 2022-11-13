# Leetcode weekly conetest
## 1.[温度转换](https://leetcode.cn/problems/convert-the-temperature/)
**解法**: 单纯的模拟题，估计应该可以竞争周赛史上最简单的题目了。

**Tag**: 模拟

**Code**:
```cpp
class Solution {
public:
    vector<double> convertTemperature(double celsius) {
        double k = celsius + 273.15, h = celsius * 1.80 + 32.00;
        return {k, h};
    }
};
```

## 2.[最小公倍数为 K 的子数组数目](https://leetcode.cn/problems/number-of-subarrays-with-lcm-equal-to-k/)
**解法**: 这题感觉还是挺有意思的，关键公式在于最小公倍数=(两数乘积 / 两数最大公约数)

**Tag**: 数学

**Code**:
```cpp
class Solution {
public:
    int subarrayLCM(vector<int>& nums, int k) {
        int ans = 0;
        for(int i = 0; i < nums.size(); ++i) {
            if(nums[i] == k) ++ans;
            unsigned long long last_lcm = nums[i];
            for(int j = i + 1; j < nums.size(); ++j) {
                unsigned long long gcd_num = gcd(nums[j], last_lcm);
                unsigned long long mul = last_lcm * nums[j];
                if(mul / gcd_num == k) {
                    ++ans;
                }
                last_lcm = mul / gcd_num;
            }
        }
        return ans;
    }
};
```

## 3.[逐层排序二叉树所需的最少操作数目](https://leetcode.cn/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/)
**解法**: 首先将每层的数值保存下来，然后找到最小交换次数即可。

**Tag**: 模拟

**Code**:
```cpp
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
    int getMinSwaps(vector<int> &nums){
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        unordered_map<int, int> pos;
        for(int i = 0; i < sorted_nums.size(); ++i) pos[sorted_nums[i]] = i;
        vector<bool> flags(nums.size(), false);
        int loop = 0;
        for(int i = 0; i < nums.size(); ++i) {
            if(!flags[i]) {
                flags[i] = true;
                int j = pos[nums[i]];
                while(!flags[j]) {
                    flags[j] = true;
                    j = pos[nums[j]];
                }
                loop++;
            }
        }
        return nums.size() - loop;
    }
    
    int minimumOperations(TreeNode* root) {
        queue<TreeNode*> qu;
        qu.push(root);
        int ans = 0;
        while(!qu.empty()) {
            int len = qu.size();
            vector<int> nums(len);
            for(int i = 0; i < len; ++i) {
                auto current_root = qu.front();
                nums[i] = current_root->val;
                qu.pop();
                if(current_root->left) qu.push(current_root->left);
                if(current_root->right) qu.push(current_root->right);
            }
            ans += getMinSwaps(nums);
        }
        return ans;
    }
};
```

## 4.[不重叠回文子字符串的最大数目](https://leetcode.cn/problems/maximum-number-of-non-overlapping-palindrome-substrings/)
**解法**: 首先通过动态规划预处理出来每个子串是不是回文子串，然后将符合条件的每个子串的开始和结束位置放入一个数组中，最后在对这个数组进行区间调度的经典贪心算法即可。

**Tag**: 贪心，动态规划

**Code**:
```cpp
class Solution {
public:
    int maxPalindromes(string s, int k) {
        int ans = 1;
        int len = s.size();
        vector<pair<int, int>> segs;
        vector<vector<bool>> dp(len, vector<bool>(len, false));
        for(int i = 0; i < len; ++i) dp[i][i] = true;
        
        for(int i = 2; i <= len; ++i) {
            for(int j = 0; j + i <= len ; ++j) {
                if(s[j] == s[i + j - 1]) {
                    if(i == 2) {
                        dp[j][j + i - 1] = true;
                    } else {
                        dp[j][j + i - 1] = dp[j + 1][j + i - 2];
                    }
                }
            }
        }
        
        for(int i = 0; i < len; ++i) {
            for(int j = 0; j < len; ++j) {
                // cout << dp[i][j] << " ";
                if(dp[i][j] && j -i + 1 >= k) {
                    segs.push_back({i, j});
                }
            }
        }
        
        auto cmp = [&](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        };
        
        if(segs.size() == 0) {
            return 0;
        }
        sort(segs.begin(), segs.end(), cmp);
        int end = segs[0].second;
        for(auto seg : segs) {
            int start_time = seg.first, end_time = seg.second;
            if(start_time > end) {
                end = end_time;
                ++ans;
            }
        }
        
        return ans;
    }
};
```



