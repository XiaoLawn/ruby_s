#include "dfs.cpp"
#include "linkedLst.cpp"
// #include "utils.cpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

class subset {
public:
    // See
    // 78. Subsets
    // 可信3
    // in dfs.cpp

    // 2311. Longest Binary Subsequence Less Than or Equal to K
    // This question looks confusing but actually it's not. Just think further.
    // s = "1001010", k = 5
    // -> 5
    // can be "00010", "00100", "00101" all 5 characters
    // s = "00101001", k = 1
    // -> 6
    int longestSubsequence(string s, int k) {
        int cnt0 = 0;
        for (char c : s) {
            if (c == '0') {
                cnt0++;
            }
        }
        int cnt1 = 0;
        int n = s.size();
        long long sum = 0, pow = 1;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '1') {
                if (sum + pow > k) break;
                sum += pow;
                cnt1++;
            }
            pow <<= 1;
            if (pow > k) break; // necessary bc binary number can easily be bigger than long long
        }
        return cnt0 + cnt1;
    }

    // 368. Largest Divisible Subset
    // nums = [1,2,3,4,6,8]
    // -> [1,2,4,8]
    // [4,8,10,240] -> [4,8,240]
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int mx = 1;
        int maxIdx = 0;
        vector<int> dp(n, 1); // dp[i]: length of largest subset ending at nums[i]
        vector<int> prev(n, -1); // prev[i]: index of previous element in the subset
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0) {
                    if (dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1;
                        prev[i] = j;
                        if (dp[i] > mx) {
                            mx = dp[i];
                            maxIdx = i;
                        }
                    }
                }
            }
        }
        vector<int> ans;
        while (maxIdx >= 0) {
            ans.push_back(nums[maxIdx]);
            maxIdx = prev[maxIdx];
        }
        return ans;
    }
};
