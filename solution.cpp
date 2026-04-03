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
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    const int MOD = 1e9 + 7;

    template<typename T>
    void swap(T& a, T& b) {
        T c = a;
        a = b;
        b = c;
    }

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
                preSum[i][j] = preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1];
                if (preSum[i][j] <= k) {
                    ans++;
                } else {
                    break;
                }
            }
        }
        return ans;
    }

    // 301. Remove Invalid Parentheses
    // given a string consists of parentheses and letters
    // you can remove invalid parentheses to make the string valid
    // return a list of valid string after removal of the minimum number of parentheses
    // e.g.
    // s = "()())()"
    // -> ["(())()","()()()"]
    // s = "(a)())()"
    // -> ["(a())()","(a)()()"]
    vector<string> removeInvalidParentheses(string s) {
        int l = 0, r = 0; // there are l '(' and r ')' to be removed
        int n1 = 0, n2 = 0; // n1 is the num of '(' and n2 is the num of ')'
        for (char c : s) {
            if (c == '(') {
                l++;
                n1++;
            } else if (c == ')') {
                if (l > 0) {
                    l--;
                } else {
                    r++;
                }
                n2++;
            }
        }
        int len = s.size() - l - r;
        int mx = min(n1, n2);
        int score = 0;
        dfs(s, "", 0, l, r, score, mx, len);
        vector<string> ans(st.begin(), st.end());
        return ans;
    }

    set<string> st;

    void dfs(string& s, string cur, int idx, int l, int r, int score, int mx, int len) {
        if (l < 0 || r < 0) return;
        if (cur.size() > len || score > mx || score < 0) {
            return;
        }
        if (cur.size() == len) {
            if (l == 0 && r == 0 && score == 0) {
                st.insert(cur);
            }
        }

        if (s[idx] == '(') {
            dfs(s, cur + '(', idx + 1, l, r, score + 1, mx, len); // pick '('
            dfs(s, cur, idx + 1, l - 1, r, score, mx, len); // not pick
        } else if (s[idx] == ')') {
            dfs(s, cur + ')', idx + 1, l, r, score - 1, mx, len); // pick ')'
            dfs(s, cur, idx + 1, l, r - 1, score, mx, len); // not pick
        } else {
            dfs(s, cur + s[idx], idx + 1, l, r, score, mx, len);
        }
    }
};
