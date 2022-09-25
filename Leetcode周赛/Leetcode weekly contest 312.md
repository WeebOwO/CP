# Leetcode weekly conetest 312
## 1.[按身高排序](https://leetcode.cn/problems/sort-the-people/)
**解法**: 直接利用STL中的sort来自定义排序规则即可。
**Tag**: 自定义排序

**Code**:
```cpp

class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        vector<pair<string, int>> cnt;
        vector<string> res;
        for(int i = 0; i < names.size(); ++i) {
            cnt.push_back(make_pair(names[i], heights[i]));
        }
        auto cmp = [&](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        };
        sort(cnt.begin(), cnt.end(), cmp);
        for(auto&& [name, height] : cnt) {
            res.push_back(name);
        }
        return res;
    }
};
```

## 2.[按位与最大的最长子数组](https://leetcode.cn/problems/longest-subarray-with-maximum-bitwise-and/)
**解法**：这道题最重要的一个观察点就是，a & b < min(a, b), 也就是说任何数与其他数进行按位与操作，其值绝不会变大，因此这道题的最终答案就是最大数字的最长连续出现次数。
**Tag**: 脑筋急转弯， 位运算

**Code**:
```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int max_num = *max_element(nums.begin(), nums.end());
        int ans = 1;
        for(int i = 0; i < nums.size(); ++i) {
            // 利用双指针来进行记录
            if(nums[i] == max_num) {
                int fast = i;
                while(fast < nums.size() && nums[fast] == nums[i]) {
                    ++fast;
                }
                ans = max(ans, fast - i);
                i = fast;
            }
        }
        return ans;
    }
};
```

## 3.[找到所有好下标](https://leetcode.cn/problems/find-all-good-indices/)
**解法**：这道题首先能想到一个简单的暴力解法，即在每个候选点都去看它的前k个字符以及后k个字符是否满足条件，但是这么做的问题在于，随着候选点不断前进，我们的候选区间其实并没有变化太多，但是却要从头开始遍历，这毫无疑问造成了许多重复计算。所以我们可以考虑用动态规划来降低整个计算的复杂度，我们预处理出以每个字符结尾的前缀个数和后缀个数，并在计算中加以利用。

**Tag**: 前缀和，后缀和，以及动态规划

**Code**:
```cpp
class Solution {
public:
    vector<int> goodIndices(vector<int>& nums, int k) {
        vector<int> prefix(nums.size()), postfix(nums.size());
        vector<int> ans;
        prefix[0] = 1;
        for(int i = 1; i < nums.size(); ++i) {
            if(nums[i] <= nums[i - 1]) {
                prefix[i] = prefix[i - 1] + 1; 
            } else {
                prefix[i] = 1;
            }
        }
        postfix[nums.size() - 1] = 1;
        for(int i = nums.size() - 2; i >= 0; --i) {
            if(nums[i] <= nums[i + 1]) {
                postfix[i] = postfix[i + 1] + 1;
            } else {
                postfix[i] = 1;
            }
        }
        for(int i = k; i < nums.size() - k; ++i) {
            if(prefix[i - 1] >= k && postfix[i + 1] >= k) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```

## 4.[好路径的个数](https://leetcode.cn/problems/number-of-good-paths/)
**解法**: 先按照权值进行排序，这样的话我们就可以将值相同的节点打包在一起进行处理，并且利用并查集来进行合并以及查询点与点之间的连通性。

**Tag**: 并查集

**Code**:
```cpp
class Solution {
private:
    vector<int> parent;
    unordered_map<int,vector<int>> graph;
public:
    // C++ Version
    size_t find(size_t x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }

    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        auto len = vals.size();
        parent.resize(len);
        vector<int> idx(len);
        int ans = 0;
        for(auto&& edge : edges) {
            int from = edge[0], to = edge[1];
            graph[from].push_back(to);
            graph[to].push_back(from);
        }
        for(size_t i = 0; i < vals.size(); ++i) {
            parent[i] = i, idx[i] = i;
        }
        auto cmp = [&](int i, int j) {
            return vals[i] < vals[j];
        };
        sort(idx.begin(), idx.end(), cmp);
        for(int left = 0; left < idx.size(); ++left) {
            int right = left + 1;

            while(right < idx.size() && vals[idx[left]] == vals[idx[right]]) {
                ++right;
            }
            unordered_map<int, int> cnt;
            for(int k = left; k < right; ++k) {
                int target_node = idx[k];
                for(auto&& next : graph[target_node]) {
                    if(vals[next] <= vals[target_node]) {
                        unite(target_node, next);
                    }
                }
            }
            for(int k = left; k < right; ++k) {
                cnt[find(idx[k])]++;
            }

            for(auto&& [key, value] : cnt) {
                ans += value;
                if(value != 1) {
                    ans += value * (value - 1) / 2;
                }
            }

            left = right - 1;
        }
        return ans;
    }
};
```
