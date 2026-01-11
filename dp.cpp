#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;


class DP {
public:
    /**
     * The things that have happened won't change, but will impose effects on the future.
     * The future will not affect the things that have happened.
     */

    // 120. Triangle
    // Given a triangle array, return the minimum path sum from top to bottom.
    // dp backwards
    // e.g.
    // triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
    // -> 11 (2,3,5,1)
    // 2
    // 3 4
    // 6 5 7
    // 4 1 8 3
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp(n, 0x3f3f3f3f); // dp[i] means the minimum sum if picked ith item
        dp[0] = triangle[0][0];
        // consider i level (starts with 0)
        // i level total i+1 items
        for (int i = 1; i < n; i++) {
            // consider jth item
            // have to start from the end to the front, because jth item depends on j-1 th item from the previous level
            for (int j = i; j >= 0; j--) {
                // j
                int mn = dp[j] + triangle[i][j];
                // j - 1
                if (j > 0) {
                    mn = min(mn, dp[j - 1] + triangle[i][j]);
                }
                dp[j] = mn;
            }
        }
        int res = dp[0];
        for (int i = 0; i < dp.size(); i++) {
            res = min(dp[i], res);
        }
        return res;
    }

    // 1277. Count Square Submatrices with All Ones
    // e.g.
    // matrix =
    // [
    //   [0,1,1,1],
    //   [1,1,1,1],
    //   [0,1,1,1]
    // ]
    // -> 15, 10 1x1, 4 2x2, 1 3x3
    //
    // matrix =
    // [
    //   [1,0,1],
    //   [1,1,0],
    //   [1,1,0]
    // ]
    // -> 7, 6 1x1, 1 2x2
    int countSquares(vector<vector<int>>& dp) {
        int n = dp.size();
        int m = dp[0].size();
        int res = 0;
        for(int i = 0;i<n;i++) {
            for(int j = 0;j<m;j++) {
                if(i == 0 || j == 0) {
                    res += dp[i][j];
                    continue;
                }
                if(dp[i][j] == 0) {
                    continue;
                }
                int mn = min(dp[i - 1][j], dp[i][j - 1]);
                mn = min(mn, dp[i - 1][j - 1]);
                dp[i][j] = mn + 1;
                res += dp[i][j];
            }
        }
        return res;
    }

    // 837. New 21 Game
    // start with n point, each time get a score between [1, maxPts], return the probability of getting res between [k, n]
    // e.g.
    // [k = 17, n = 21], maxPts = 10
    // -> 0.73278
    // [k = 1, n = 10], maxPts = 10
    // -> 1.00000
    // [k = 1, n = 6], maxPts = 10
    // -> 0.60000
    double new21Game(int n, int k, int maxPts) {
        if (k == 0 || n >= k - 1 + maxPts) return 1.0;
        vector<double> dp(n + 1, 0); // dp[i] is the possibility of getting number i
        dp[0] = 1;
        double sum = 0;
        double res = 0;
        for (int i = 1; i <= n; i++) {
            if (i <= k) {
                sum += dp[i - 1];
            }
            if (i - maxPts - 1 >= 0) {
                sum -= dp[i - maxPts - 1];
                // when not sure, use example
                // maxPts = 3, i = 5
                // [2,3,4] should be there, cut 1
            }
            double d = sum / maxPts;
            if (i >= k) {
                res += d;
            } else {
                dp[i] = d;
            }
        }
        return res;
    }

    // 198. House Robber
    int rob(vector<int> &nums) {
        int n = nums.size();
        if (n == 0) {
            return nums[0];
        }
        if (n == 1) {
            return max(nums[0], nums[1]);
        }
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[n - 1];
    }

    // dp from last to first
    //
    // 2140. Solving Questions With Brainpower
    // given a list of questions,
    // for single question [a,b], a is the score of it, but you need to skip next b questions after solving it
    // return the maximum score you can possibly get
    //
    // [1,1],[2,2],[3,3],[4,4],[5,5]]
    // -> 7
    // [3,2],[4,3],[4,4],[2,5]
    // -> 5
    long long mostPoints(vector<vector<int>>& qs) {
        // Get the number of questions
        int n = qs.size();
        vector<long long> dp(n, 0);  // dp[i] means max point you possible get after processing [i...last] questions
        dp[n - 1] = qs[n - 1][0];  // starting from the last question
        for (int i = n - 2; i >= 0; i--) {
            // pick this question and previous question
            long long pk = 0;
            if (qs[i][1] + i + 1 < n) {
                pk = (long long) qs[i][0] + dp[qs[i][1] + i + 1];
            }
            // not picking previous question, result in picking current question / go for the former one
            long long np = max((long long) qs[i][0], dp[i + 1]);
            dp[i] = max(pk, np);
        }
        return dp[0];
    }


    /*
     * 377. 组合总和 Ⅳ
     * 给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target
     * 请你从 nums 中找出并返回总和为 target 的元素组合的个数
     *
     * e.g.
     * nums = [1,2,3], target = 4
     * -> 7
     * 所有可能的组合为：
     * (1, 1, 1, 1)
     * (1, 1, 2)
     * (1, 2, 1)
     * (1, 3)
     * (2, 1, 1)
     * (2, 2)
     * (3, 1)
     * 注，顺序不同的序列被视作不同的组合
     *
     * 并非 完全背包问题，易迷惑
     */
    int combinationSum4(vector<int> &nums, int target) {
        int n = nums.size();
        vector<int> f(target + 1);
        f[0] = 1;
        for (int i = 0; i <= target; i++) {
            for (int num: nums) {
                if (i >= num && f[i - num] < INT_MAX) {  // 有毒吧
                    f[i] += f[i - num];
                }
            }
        }
        return f[target];
    }


    // 2684. maximum-number-of-moves-in-a-grid
    int maxMoves(vector<vector<int> > &grid) {
        int m = grid.size();  // m rows
        int n = grid[0].size();
        vector<vector<int> > dp(m, vector<int>(n, -1));
        for (int i = 0; i < m; i++) {
            dp[i][0] = 0;
        }
        int ans = 0;
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < m; i++) {
                // i row j col
                if (i == 0) {
                    if ((grid[i][j] > grid[i][j - 1] && dp[i][j - 1] != -1)
                        || (grid[i][j] > grid[i + 1][j - 1] && dp[i + 1][j - 1] != -1)) {
                        dp[i][j] = max(dp[i][j - 1], dp[i + 1][j - 1]) + 1;
                    }
                } else if (i == m - 1) {
                    if ((grid[i][j] > grid[i][j - 1] && dp[i][j - 1] != -1)
                        || (grid[i][j] > grid[i - 1][j - 1] && dp[i - 1][j - 1] != -1)) {
                        dp[i][j] = max(dp[i][j - 1], dp[i - 1][j - 1]) + 1;
                    }
                } else {
                    if ((grid[i][j] > grid[i][j - 1] && dp[i][j - 1] != -1)
                        || (grid[i][j] > grid[i + 1][j - 1] && dp[i + 1][j - 1] != -1)
                        || (grid[i][j] > grid[i - 1][j - 1] && dp[i - 1][j - 1] != -1)) {
                        int bigger = max(dp[i][j - 1], dp[i + 1][j - 1]);
                        dp[i][j] = max(bigger, dp[i - 1][j - 1]) + 1;
                    }
                }
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }
};
