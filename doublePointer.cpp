#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <numeric>
#include <algorithm>
#include "utils.cpp"

using namespace std;

class DoublePointer {
public:
    // 11. Container With Most Water
    // given an array of height of vertical lines, return the max water can be contained using any two lines.
    // easier than you think
    // e.g.
    // height = [1,8,6,2,5,4,8,3,7]
    // -> 49, using height[1] = 8 and height[8] = 7
    int maxArea(vector<int>& height) {
        int i = 0;
        int j = height.size() - 1;
        int res = 0;
        while (i < j) {
            res = max(res, min(height[i], height[j]) * (j - i));
            if (height[i] < height[j]) i++;
            else j--;
        }
        return res;
    }

    // 3814. Maximum Capacity Within Budget
    // given the costs array and capacity array, allow to pick at most two items which cost < budget
    // return the max capacity
    // e.g.
    // costs = [4,8,5,3], capacity = [1,5,2,7], budget = 8
    // -> 8
    // [{3,7},{4,1},{5,2},{8,5}], 8 -> 8
    // [{2,3},{2,4},{2,5}], 5 -> 9
    // [{1,7},{3,5},{7,3}], 13 -> 12
    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget) {
        int n = costs.size();
        vector<pair<int, int>> vec(n);
        for (int i = 0; i < n; i++) {
            vec[i] = {costs[i], capacity[i]};
        }
        sort(vec.begin(), vec.end());
        vector<int> preMax(n, 0);
        int pm = 0;
        for (int i = 0; i < n; i++) {
            pm = max(pm, vec[i].second);
            preMax[i] = pm;
        }
        int ans = 0, j = n - 1;

        // from front to the end
        for (int i = 0; i < n; i++) {
            if (vec[i].first < budget) {
                ans = max(ans, vec[i].second);
            }
            while (j >= 0 && vec[i].first + vec[j].first >= budget) {
                j--;
            }
            // if you select ith, there is a range you are able to select. Which is [0, min(j, i-1)]
            int t = min(j, i - 1);
            if (t >= 0) {
                ans = max(ans, vec[i].second + preMax[t]);
            }
        }
        return ans;
    }

    // 1498. Number of Subsequences That Satisfy the Given Sum Condition
    // return the number of non-empty sequences which min + max <= target
    // double pointer
    // nums = [3,5,6,7], target = 9
    // -> 4
    // [3], [3,5], [3,6], [3,5,6]
    //
    // nums = [2,3,3,4,6,7], target = 12
    // -> 61
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        int mod = 1e9 + 7; // how to deal with mod?
        int res = 0;
        sort(nums.begin(), nums.end());
        vector<int> power(n, 1);
        for (int i = 1; i < n; i++) {
            // priority: */  >  %  >  +-
            power[i] = power[i - 1] * 2 % mod; // because each element can be out of range
        }
        int l = 0, r = n - 1;
        while (l <= r) {
            if (nums[l] + nums[r] <= target) {
                res = (res + power[r - l]) % mod; // and the sum of elements can be out of range
                l++;
            } else {
                r--;
            }
        }
        return res;
    }

    // how to deal with mod? The wrong way
    int numSubseq1(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        int res = 0;
        sort(nums.begin(), nums.end());
        while (l <= r) {
            if (nums[l] + nums[r] <= target) {
                res += pow(2, r - l); // Here, not only res, but also pow(2, r - l) can easily go out of range
                l++;
            } else {
                r--;
            }
        }
        return res;
    }
};