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
