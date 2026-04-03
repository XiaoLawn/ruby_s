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


class matrix {
public:
    // 1878. Get Biggest Three Rhombus Sums in a Grid
    // given a m x n grid, return the Biggest Three Rhombus Sums.
    // Rhombus with the same sums is considered one. Return the biggest three in descending order. If there aren't enough return the num you got.
    //
    // Rhombus problem
    //
    // e.g.
    // grid = [
    // [1,2,3],
    // [4,5,6],
    // [7,8,9]
    // ]
    // -> [20,9,8]
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int maxR = (min(m, n) - 1) / 2;
        set<int> s;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                s.insert(grid[i][j]);
            }
        }
        vector<pair<int, int>> dir = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
        for (int r = 1; r <= maxR; r++) {
            for (int i = r; i + r < m; i++) {
                for (int j = r; j + r < n; j++) {
                    int sum = 0;
                    int i1 = i, j1 = j - r;
                    // start from left -> bottom -> right -> top
                    for (auto& d : dir) {
                        for (int k = 0; k < r; k++) {
                            i1 += d.first;
                            j1 += d.second;
                            sum += grid[i1][j1];
                        }
                    }
                    s.insert(sum);
                }
            }
        }
        if (s.size() <= 3) {
            vector<int> ans(s.begin(), s.end());
            reverse(ans.begin(), ans.end());
            return ans;
        }
        vector<int> ans(prev(s.end(), 3), s.end());
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
