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


class dpLCS {
public:
    // 712. Minimum ASCII Delete Sum for Two Strings
    // Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.
    // e.g.
    // s1 = "sea", s2 = "eat"
    // -> delete 's' from "sea", 't' from "eat", we get "ea"
    int minimumDeleteSum(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();
        // dp[i][j] is the max sum we can get from substr s1[0,i] and s2[0,j]
        vector<vector<int>> dp(n1+1, vector<int>(n2+1, 0));
        int sum = 0;
        for(char c : s1) sum += c;
        for(char c : s2) sum += c;
        for(int i = 1;i<=n1;i++) {
            for(int j = 1;j <= n2;j++) {
                if(s1[i-1] == s2[j-1]) {
                    dp[i][j] = max(dp[i-1][j-1] + s1[i-1], dp[i][j-1]);
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }

            }
        }
        return sum - 2 * dp[n1][n2];
    }
};