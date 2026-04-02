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

class dpPath {
public:
    // 3418. Maximum Amount of Money Robot Can Earn
    int maximumAmount(vector<vector<int>>& coins) {
        int n = coins.size();
        int m = coins[0].size();
        vector<vector<int>> n0(n, vector<int>(m));
        vector<vector<int>> n1(n, vector<int>(m));
        vector<vector<int>> n2(n, vector<int>(m));
        n0[0][0] = coins[0][0];
        if (n0[0][0] > 0) {
            n1[0][0] = n0[0][0];
            n2[0][0] = n0[0][0];
        }
        for(int i = 0;i<n;i++) {
            for(int j = 0;j<m;j++) {
                if(i == 0 && j == 0) continue;
                int up = INT_MIN, left = INT_MIN;
                if(i > 0) {
                    up = n0[i - 1][j];
                }
                if(j > 0) {
                    left = n0[i][j - 1];
                }
                n0[i][j] = max(up, left) + coins[i][j];
            }
        }

        // n0 -> n1
        for(int i = 0;i<n;i++) {
            for(int j = 0;j<m;j++) {
                if(i == 0 && j == 0) continue;
                int u1 = INT_MIN, l1 = INT_MIN;

                if(i > 0) u1 = n0[i - 1][j];
                if(j > 0) l1 = n0[i][j - 1];
                int c1 = max(u1, l1);  // ignore current to 0

                int u2 = INT_MIN, l2 = INT_MIN;
                if(i > 0) u2 = n1[i - 1][j];
                if(j > 0) l2 = n1[i][j - 1];
                int c2 = max(u2, l2) + coins[i][j];  // accept current

                n1[i][j] = max(c1, c2);
            }
        }

        for(int i = 0;i<n;i++) {
            for(int j = 0;j<m;j++) {
                if(i == 0 && j == 0) continue;
                int u1 = INT_MIN, l1 = INT_MIN;

                if(i > 0) u1 = n1[i - 1][j];
                if(j > 0) l1 = n1[i][j - 1];
                int c1 = max(u1, l1);

                int u2 = INT_MIN, l2 = INT_MIN;
                if(i > 0) u2 = n2[i - 1][j];
                if(j > 0) l2 = n2[i][j - 1];
                int c2 = max(u2, l2) + coins[i][j];

                n2[i][j] = max(c1, c2);
            }
        }
        return n2[n - 1][m - 1];
    }

    // 1594. Maximum Non Negative Product in a Matrix
    // return the maximum non negative product of the path, from the top left of the grid to bottom right
    // e.g.
    // grid = [
    //   -1, 2, 1
    //   1, -2, 1
    //   3, -4, 1
    // ]
    // -> 8
    // path is
    // 1 -> 1 -> -2 -> -4 -> 1
    // 1 * 1 * -2 * -4 * 1 = 8
    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<long long>> dpMin(m, vector<long long>(n, 0));
        vector<vector<long long>> dpMax(m, vector<long long>(n, 0));
        dpMin[0][0] = grid[0][0];
        dpMax[0][0] = grid[0][0];
        for(int i = 1;i<m;i++) {
            long long t = grid[i][0] * dpMin[i-1][0];
            dpMin[i][0] = t;
            dpMax[i][0] = t;
        }
        for(int j = 1;j<n;j++) {
            long long t = grid[0][j] * dpMin[0][j-1];
            dpMin[0][j] = t;
            dpMax[0][j] = t;
        }
        for(int i = 1;i<m;i++) {
            for(int j = 1;j<n;j++) {
                int cur = grid[i][j];
                long long a1 = cur * dpMin[i - 1][j];
                long long a2 = cur * dpMin[i][j - 1];
                long long a3 = cur * dpMax[i - 1][j];
                long long a4 = cur * dpMax[i][j - 1];
                dpMin[i][j] = min(a1, min(a2, min(a3,a4)));
                dpMax[i][j] = max(a1, max(a2, max(a3,a4)));
            }
        }
        if(dpMax[m - 1][n - 1] < 0) return -1;
        return (int)(dpMax[m - 1][n - 1] % 1000000007);
    }
};