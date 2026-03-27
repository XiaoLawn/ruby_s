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

class dpBag {
public:
    /**
     * --------------------------------------- 01背包 ---------------------------------------
     *
     * 0-1 背包问题，不可重复选<br>
     *
     * 选取物品总量 不能超过 规定数量，问最多物品数<br>
     * 选取物品总量 恰好等于 规定数量，问最小物品数<br>
     * 选取物品总量 恰好等于 规定数量，问可行性<br>
     * 选取物品总量 恰好等于 规定数量，问方案总数<br>
     *
     *
     * ------------------------------------- 01Knapsack -------------------------------------
     *
     * 0-1 knapsack, no repeat selection
     *
     * total item picked 'cannot exceed' specific number, Ask the maximum number of items
     * total item picked 'just equal to' specific number, Ask the maximum number of items
     * total item picked 'just equal to' specific number, Ask the minimum number of items
     * total item picked 'just equal to' specific number, Ask if possible
     * total item picked 'just equal to' specific number, Ask the number of total possible plans
     *
     */

    // 416. Partition Equal Subset Sum
    // return true if there exists a subset that sums to half of the total sum
    // dpBag - total item picked 'just equal to' specific number, Ask the number of total possible plans
    //
    // e.g.
    // nums = [1,5,11,5]
    // -> true [1,5,5] [11]
    // nums = [1,2,3,5]
    // -> false
    bool canPartition(vector<int>& nums) {
        int sum2 = accumulate(nums.begin(), nums.end(), 0);
        if (sum2 % 2 == 1) return false;
        int sum = sum2 / 2;
        vector<bool> f(sum + 1); // f[i] = true means there are subset that sums i
        f[0] = true;
        for (int u : nums) {
            for (int i = sum; i >= u; i--) {
                // dp from end to front, because it's 01 knapsack stuffs aren't allowed to reuse
                f[i] = f[i] || f[i - u];
                if (f[sum]) {
                    return true;
                }
            }
        }
        return f[sum];
    }

    // 2787. Ways to Express an Integer as Sum of Powers
    // return the total ways to express n using numbers to the power of x, numbers are unique
    // dpBag - total item picked 'just equal to' specific number, Ask the number of total possible plans
    // e.g.
    // n = 10, x = 2
    // -> 1, 10 = 1^2 + 3^2
    //
    // n = 4, x = 1
    // -> 2, 4 = 1^1 + 3^1, 4 = 4^1
    int numberOfWays(int n, int x) {
        vector<int> nums;
        for (int i = 1; pow(i, x) <= n; i++) {
            nums.push_back(pow(i, x));
        }
        // now the question turns into:
        // return the "total ways" to pick from nums that sum into n, no repeat selection.
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int u : nums) {
            for (int i = n; i >= u; i--) {
                dp[i] = (dp[i] + dp[i - u]) % (1e9 + 7);
                // not dp[i] = max(dp[i], dp[i - u] + 1), because we want the "total ways"
            }
        }
        return dp[n];
    }

    /**
     * --------------------------------------- 完全背包问题 ---------------------------------------<p>
     * <p>
     * 完全背包问题，元素允许重用<br>
     *
     * -------------------------------- Complete knapsack problem ----------------------------------
     *
     *
     * where repetitive use of item is allowed
     *
     */

    // 518. Coin Change II
    // Return the ways to make up to amount, using coins, can repeat
    // amount = 5, coins = [1,2,5]
    // -> 4, [1,1,1,1,1], [1,1,1,2], [1,2,2], [5]
    int change(int amount, vector<int>& coins) {
        vector<int> f(amount + 1, 0);  // f[i] means the "total ways" that sums up to amount
        f[0] = 1;
        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                f[i] = f[i] + f[i - coin];
            }
        }
        return f[amount];
    }

    // 279. Perfect Squares
    // return the least number of perfect square numbers that sum to n
    // perfect square numbers are 1, 4, 9, 16, 25...
    //
    // e.g.
    // n = 12
    // -> 3, 12 = 4 + 4 + 4
    // n = 13
    // -> 2, 13 = 4 + 9
    int numSquares(int n) {
        vector<int> dp(n + 1, 0x3f3f3f3f); // dp[i] means the "least number" of psn that sums to i
        dp[0] = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};
