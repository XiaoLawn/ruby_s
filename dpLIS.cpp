#include "dfs.cpp"
#include "linkedLst.cpp"
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

class dpLIS {
public:
    // 300. Longest Increasing Subsequence
    // nums = [10,9,2,5,3,7,101,18]
    // -> 4, [2,5,7,18]
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr(n);
        int len = 0;
        for (int u : nums) {
            int idx = lowerBound(arr, 0, len, u);
            arr[idx] = u;
            if (idx == len) {
                len++;
            }
        }
        return len;
    }

    int lowerBound(vector<int> arr, int left, int right, int u) {
        while (left < right) {
            int mid = (right + left) / 2;
            if (arr[mid] >= u) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};