# Leetcode weekly conetest 315
## 1.[与对应负数同时存在的最大正整数](https://leetcode.cn/problems/largest-positive-integer-that-exists-with-its-negative/)
**解法**: 碰到这种查询数字是否存在的时候，用哈希表就可以很好的解决，我们首先将所有数字都插入到哈希表中，然后按照题目要求进行查询即可。

**Tag**: 哈希

**Code**:
```cpp
class Solution {
public:
    int findMaxK(vector<int>& nums) {
        unordered_set<int> exist;
        for(auto&& val : nums) {
            exist.insert(val);
        }
        int ans = -1;
        for(int i = 0; i < nums.size(); ++i) {
            if(exist.find(nums[i]) != exist.end() && exist.find(-nums[i]) != exist.end()) {
                ans = max(ans, abs(nums[i]));
            }
        }
        return ans;
    }
};
```

## 2.[反转之后不同整数的数目](https://leetcode.cn/contest/weekly-contest-315/problems/count-number-of-distinct-integers-after-reverse-operations/)
**解法**: 和第一题类似，我们将数组中每个数字以及他们的反转插入到哈希表中，然后返回哈希表的大小即可。

**Tag**: 哈希

**Code**:
```cpp
class Solution {
private:
    vector<int> sup;
public:
    int m_reverse(int t) {
        int cnt = 0;
        int res = 0;
        while(t) {
            sup[cnt++] = t % 10;
            t /= 10;
        }
        for(int i = 0; i < cnt; ++i) {
            res = res * 10 + sup[i];
        }
        return res;
    }
    int countDistinctIntegers(vector<int>& nums) {
        unordered_set<int> cnt;
        sup.resize(10);
        for(auto val : nums) {
            cnt.insert(val);
            cnt.insert(m_reverse(val));
        }
        return cnt.size();
    }
};
```

## 3.[反转之后的数字和](https://leetcode.cn/contest/weekly-contest-315/problems/sum-of-number-and-its-reverse/)
**解法**: 裸题，直接按照题目进行模拟即可，数据量$10^5$并不大，直接输出即可。

**Tag**: 模拟

**Code**:
```cpp
class Solution {
private:
    vector<int> sup;
public:
    int m_reverse(int t) {
        int cnt = 0;
        int res = 0;
        while(t) {
            sup[cnt++] = t % 10;
            t /= 10;
        }
        for(int i = 0; i < cnt; ++i) {
            res = res * 10 + sup[i];
        }
        return res;
    }
    
    bool sumOfNumberAndReverse(int num) {
        if(num == 0) return true;
        sup.resize(10);
        for(int i = 0; i < num; ++i) {
            if(i + m_reverse(i) == num) {
                return true;
            }
        }
        return false;
    }
};
```

## 4.[统计定界子数组的数目](https://leetcode.cn/contest/weekly-contest-315/problems/count-subarrays-with-fixed-bounds/)
**解法**: 我们可以通过统计所有不符合条件的值的个数，假设有$k$个的话，我们可以将整个区间分为$k + 1$个区间，然后分别统计每个区间里符合要求的个数即可，这道题关键的便是如何统计区间内符合要求的子数组的个数，在统计时，我们可以利用双指针的方法，在$O(n)$的复杂度内完成。

**Tag**: 双指针

**Code**:
```cpp
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        auto calc = [&](int left, int right) {
            int min_cnt = 0, max_cnt = 0;
            long long cnt = 0;
            for(int i = left, j = left; j <= right; ++j) {
                if(nums[j] == minK) ++min_cnt;
                if(nums[j] == maxK) ++max_cnt;
                
                while(i <= j && min_cnt > 0 && max_cnt > 0) {
                    if(nums[i] == minK) --min_cnt;
                    if(nums[i] == maxK) --max_cnt;
                    ++i;
                }
                cnt += (j - left + 1) - (j - i + 1);
            }
            return cnt;
        };
        long long ans = 0;
        int cnt = 0;
        for(int i = 0; i < nums.size(); ++i) {
            if(nums[i] < minK || nums[i] > maxK) {
                ans += calc(i - cnt, i - 1);
                cnt = 0;  
            } else {
                cnt++;
            }
        }
        ans += calc(nums.size() - cnt, nums.size() - 1);
        return ans;
    }
};
```



