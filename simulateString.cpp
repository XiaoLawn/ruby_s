#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <numeric>
#include <algorithm>

using namespace std;

class SimulateString {
public:
    /*
     * 6. Zigzag Conversion
     * turn string s into a zigzag format with numRows rows, return the new string by reading line by line.
     * e.g.
     * s = "PAYPALISHIRING", numRows = 3
     *
     * P   A   H   N
     * A P L S I I G
     * Y   I   R
     *
     * -> "PAHNAPLSIIGYIR"
     */
    string convert(string s, int numRows) {
        int n = 2 * numRows - 2;
        if (numRows == 1) {
            n = 1;
        }
        vector<vector<char>> grid;
        vector<char> vec;
        for (char& c : s) {
            vec.push_back(c);
            if (vec.size() == n) {
                grid.push_back(vec);  // push_back() stores a copy, never a reference
                vec.clear();
            }
        }
        grid.push_back(vec);

        string ans = "";
        for (int i = 0; i < numRows; i++) {
            for (auto& vec : grid) {
                if (i < vec.size()) {
                    ans += vec[i];
                }
                if (i != 0 && i != numRows - 1) {
                    if (n - i < vec.size()) ans += vec[n - i];
                }
            }
        }
        return ans;
    }
};