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

class simulateRectangles {
public:
    /*
     * 3047. Find the Largest Area of Square Inside Two Rectangles
     * Given n rectangles, return the max area of square that lies in the intersecting region of any two rectangles
     *
     * e.g.
     * bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
     * -> 1
     *
     * bottomLeft = [[1,1],[1,3],[1,5]], topRight = [[5,5],[5,7],[5,9]]
     * -> 4
     */
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        long long ans = 0;
        for(int i = 0;i<n;i++) {
            // rectangle i
            for(int j = 0;j < i;j++) {
                // rectangle j
                // top is the lower one of two tops
                int top = min(topRight[i][1], topRight[j][1]);
                // bottom is the higher one of two bottoms
                int bottom = max(bottomLeft[i][1], bottomLeft[j][1]);
                if(bottom >= top) continue;

                int right = min(topRight[i][0], topRight[j][0]);
                int left = max(bottomLeft[i][0], bottomLeft[j][0]);
                if(left >= right) continue;

                int a = right - left;
                int b = top - bottom;
                int mn = min(a, b);
                long long sq = (long long)mn * mn;
                ans = max(sq, ans);
            }
        }
        return ans;
    }
};