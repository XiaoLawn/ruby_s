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

// 11. Container With Most Water
// given an array of height of vertical lines, return the max water can be contained using any two lines.
// e.g.
// height = [1,8,6,2,5,4,8,3,7]
// -> 49, using height[1] = 8 and height[8] = 7
int maxArea(vector<int>& height) {
    int i = 0;
    int j = height.size() - 1;
    int res = 0;
    while (i < j) {
        res = max(res, min(height[i], height[j]) * (j - i));
        if (height[i] < height[j]) i++;
        else j--;
    }
    return res;
}
