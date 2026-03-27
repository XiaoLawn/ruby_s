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


class SimulateRoman {
public:
    // 13. Roman to Integer
    /*
     * Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
     * Symbol       Value
     * I             1
     * V             5
     * X             10
     * L             50
     * C             100
     * D             500
     * M             1000
     * I can be placed before V (5) and X (10) to make 4 and 9.
     * X can be placed before L (50) and C (100) to make 40 and 90.
     * C can be placed before D (500) and M (1000) to make 400 and 900.
     *
     * e.g.
     * s = "III"
     * -> 3, III = 3
     *
     * s = "LVIII"
     * -> 58, L = 50, V= 5, III = 3.
     *
     * s = "MCMXCIV"
     * -> 1994, M = 1000, CM = 900, XC = 90 and IV = 4.
     *
     */
    int romanToInt(string s) {
        map<char, int> mp;
        mp['M'] = 1000;
        mp['D'] = 500;
        mp['C'] = 100;
        mp['L'] = 50;
        mp['X'] = 10;
        mp['V'] = 5;
        mp['I'] = 1;
        int n = s.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (i + 1 < n && mp[s[i]] < mp[s[i + 1]]) {
                ans -= mp[s[i]];
            } else {
                ans += mp[s[i]];
            }
        }
        return ans;
    }

    // 12. Integer to Roman
    string intToRoman(int num) {
        vector<int> nums{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> rome{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        string ans = "";
        for (int i = 0; i < 13; i++) {
            while (num >= nums[i]) {
                num -= nums[i];
                ans += rome[i];
            }
        }
        return ans;
    }
};