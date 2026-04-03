#include "dfs.cpp"
#include "linkedLst.cpp"
#include "utils.cpp"
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

class prefixSum {
public:
    // prefix sum template
    void prefixSumDemo(vector<int> nums) {
        int n = nums.size();
        vector<int> preSum(n + 1); // pre[i] is the sum from nums[0] to nums[i - 1]
        preSum[0] = 0;
        for (int i = 0; i < n; i++) {
            preSum[i + 1] = preSum[i] + nums[i];
        }
    }

    // prefix sum template 2D version
    void prefixSumDemo(vector<vector<int>> nums) {
        int m = nums.size();
        int n = nums[0].size();
        vector<vector<int>> preSum(m + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                preSum[i + 1][j + 1] = preSum[i][j + 1] + preSum[i + 1][j] - preSum[i][j] + nums[i][j];
            }
        }
    }

    // 3070. Count Submatrices with Top-Left Element and Sum Less Than k
    //
    // 2D prefix sum
    //
    // e.g.
    // grid = [
    //  [7,2,9],
    //  [1,5,0],
    //  [2,6,6]
    // ], k = 20
    // -> 6
    //
    // grid = [
    // [7,6,3],
    // [6,6,1]
    // ], k = 18
    // -> 4
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size(); // i
        int n = grid[0].size(); // j
        int ans = 0;
        vector<vector<int>> preSum(m, vector<int>(n, k + 1));
        preSum[0][0] = grid[0][0];
        if (grid[0][0] <= k) ans++;
        for (int j = 1; j < n; j++) {
            preSum[0][j] = preSum[0][j - 1] + grid[0][j];
            if (preSum[0][j] <= k) {
                ans++;
            } else {
                break;
            }
        }
        for (int i = 1; i < m; i++) {
            preSum[i][0] = preSum[i - 1][0] + grid[i][0];
            if (preSum[i][0] <= k) {
                ans++;
            } else {
                break;
            }
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                preSum[i][j] = grid[i][j] + preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1];
                if (preSum[i][j] <= k) {
                    ans++;
                } else {
                    break;
                }
            }
        }
        return ans;
    }

    // Fenwick tree
    // Used for prefix sum with constant update
    // Also for counting how many numbers smaller/greater than current number
    struct FenwickTree {
        vector<int> BIT;
        int n;

        FenwickTree(int n) : n(n), BIT(n + 1, 0) {
        }

        // add x to idx element (0-index)
        void add(int idx, int x) {
            idx++;
            for (; idx <= n; idx += (idx & -idx)) {
                BIT[idx] += x;
            }
        }

        // return the sum of [0, idx] elements
        int sum(int idx) {
            // Prefix sum
            int ans = 0;
            idx++;
            for (; idx > 0; idx -= (idx & -idx)) {
                ans += BIT[idx];
            }
            return ans;
        }
    };

    // Used for subarray sum with constant update
    struct SegmentTree {
        int n;
        vector<int> seg;

        SegmentTree(int n) : n(n), seg(2 * n) {
        }

        // increment the value x at position i (0-index)
        void update(int i, int x) {
            i += n;
            seg[i] += x; // Increment the value at position i
            for (i /= 2; i > 0; i /= 2) {
                seg[i] = seg[2 * i] + seg[2 * i + 1];
            }
        }

        // Return the sum of [l, r] (0-index)
        int query(int l, int r) {
            int sum = 0;
            for (l += n, r += n; l <= r; l /= 2, r /= 2) {
                if (l % 2 == 1) {
                    sum += seg[l++];
                }
                if (r % 2 == 0) {
                    sum += seg[r--];
                }
            }
            return sum;
        }
    };

    // 1314. Matrix Block Sum
    // Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
    // Output: [[12,21,16],[27,45,33],[24,39,28]]
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& nums, int k) {
        int m = nums.size();
        int n = nums[0].size();
        vector<vector<int>> preSum(m + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                preSum[i + 1][j + 1] = preSum[i][j + 1] + preSum[i + 1][j] - preSum[i][j] + nums[i][j];
            }
        }
        vector<vector<int>> ans(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int l = max(0, j - k);
                int r = min(n - 1, j + k);
                int t = max(0, i - k);
                int b = min(m - 1, i + k);
                ans[i][j] = preSum[b + 1][r + 1] - preSum[t][r + 1] - preSum[b + 1][l] + preSum[t][l];
            }
        }
        return ans;
    }

    // 2874. Maximum Value of an Ordered Triplet II
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size();
        vector<int> L(n, 0); // L[i] is max num index < i
        vector<int> R(n, 0);
        for (int i = 1; i < n; i++) {
            L[i] = max(L[i - 1], nums[i - 1]);
        }
        for (int i = n - 2; i >= 0; i--) {
            R[i] = max(R[i + 1], nums[i + 1]);
        }
        long long ans = 0;
        for (int j = 1; j < n - 1; j++) {
            ans = max(ans, (long long) (L[j] - nums[j]) * R[j]);
        }
        return ans;
    }

    // 2873. Maximum Value of an Ordered Triplet I
    // brute force approach
    long long maximumTripletValue1(vector<int>& nums) {
        int i = 0, j = 1, k = 2;
        int n = nums.size();
        long long ans = 0;
        while (i < j) {
            long long ni = nums[i];
            j = i + 1;
            while (j < k) {
                long long nj = nums[j];
                k = j + 1;
                while (k < n) {
                    long long nk = nums[k];
                    ans = max(ans, (ni - nj) * nk);
                    k++;
                }
                j++;
            }
            i++;
        }
        return ans;
    }
};
