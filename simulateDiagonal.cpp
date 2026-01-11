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

// 498. Diagonal Traverse
// return the diagonal traverse result of given matrix
// e.g.
// mat = [
// [1,2,3],
// [4,5,6],
// [7,8,9]
// ]
// -> [1,2,4,7,5,3,6,8,9]
vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
    int m = mat.size(); // for row
    int n = mat[0].size(); // for col
    vector<int> res;
    int row = 0, col = 0;
    for (int i = 0; i < m * n; i++) {
        res.push_back(mat[row][col]);
        if ((row + col) % 2 == 0) {
            if (row == 0 && col < n - 1) {
                col++;
            } else if (col == n - 1 && row < m - 1) {
                row++;
            } else {
                row--;
                col++;
            }
        } else {
            if (col == 0 && row < m - 1) {
                row++;
            } else if (row == m - 1 && col < n - 1) {
                col++;
            } else {
                col--;
                row++;
            }
        }
    }
    return res;
}


// 3446. Sort Matrix by Diagonals
vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    int row, col;
    vector<int> vec;
    for (int i = n - 1; i >= 0; i--) {
        row = i;
        col = 0;
        while (row < n) {
            vec.push_back(grid[row][col]);
            row++;
            col++;
        }
        sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });
        row = i;
        col = 0;
        int cnt = 0;
        while (row < n) {
            grid[row][col] = vec[cnt++];
            row++;
            col++;
        }
        vec.clear();
    }
    for (int j = 1; j < n; j++) {
        col = j;
        row = 0;
        while (col < n) {
            vec.push_back(grid[row][col]);
            row++;
            col++;
        }
        sort(vec.begin(), vec.end());
        col = j;
        row = 0;
        int cnt = 0;
        while (col < n) {
            grid[row][col] = vec[cnt++];
            row++;
            col++;
        }
        vec.clear();
    }
    return grid;
}
