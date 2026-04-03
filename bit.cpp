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
#include "solution.cpp"
#include "binarySearch.cpp"
#include "linkedLst.cpp"

using namespace std;


class Bit {
public:
    // 1009. Complement of Base 10 Integer
    // return the integer when you flip every bit in n, 0 to 1, 1 to 0
    // e.g.
    // n = 5
    // -> 2, 5 = '101', 2 = '010'
    // n = 10
    // -> 5, 10 = '1010', 5 = '0101'
    int bitwiseComplement(int n) {
        vector<int> vec; // 110 -> {0,1,1} -> {1,0,0}
        if (n == 0) return 1;
        while (n > 0) {
            int b = n & 1;
            b = 1 - b;
            vec.push_back(b);
            n >>= 1;
        }
        reverse(vec.begin(), vec.end());
        int ans = 0;
        for (int i = 0; i < vec.size(); i++) {
            ans <<= 1;
            ans += vec[i];
        }
        return ans;
    }

    /*
    * 1863. Sum of All Subset XOR Totals
    *
    * e.g.
    * nums = [5,1,6]
    * -> 28
    * The empty subset has an XOR total of 0.
    * [5] has an XOR total of 5.
    * [1] has an XOR total of 1.
    * [6] has an XOR total of 6.
    * [5,1] has an XOR total of 5 XOR 1 = 4.
    * [5,6] has an XOR total of 5 XOR 6 = 3.
    * [1,6] has an XOR total of 1 XOR 6 = 7.
    * [5,1,6] has an XOR total of 5 XOR 1 XOR 6 = 2.
    * 0 + 5 + 1 + 6 + 4 + 3 + 7 + 2 = 28
    */
    int subsetXORSum(vector<int>& nums) {
        int total = 0;
        for (int num : nums) {
            total |= num;  // Step 1: Compute bitwise OR of all numbers
        }
        return total * (1 << (nums.size() - 1));  // Step 2: Multiply by 2^(n-1)
    }

    // 2275. largest combination with Bitwise AND greater than zero
    void process(vector<int>& acc, int u) {
        // turn integer into binary
        int i = 0;
        while (u > 0) {
            if (u % 2 == 1) {
                acc[i]++;
            }
            u /= 2; // u >>= 1
            i++;
        }
    }

    int largestCombination(vector<int>& candidates) {
        int n = candidates.size();
        vector<int> acc(100, 0);
        for (int i = 0; i < n; ++i) {
            process(acc, candidates[i]);
        }
        int mx = 0;
        for (int i = 0; i < 100; ++i) {
            mx = max(mx, acc[i]);
        }
        return mx;
    }

    /*
     * 2135. count-words-obtained-after-adding-a-letter
     */
    int sToInt(string s) {
        int ret = 0;
        for (int i = 0; i < s.size(); i++) {
            ret |= 1 << (s[i] - 'a');
        }
        return ret;
    }

    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        set<int> st;
        int ans = 0;
        for (auto s : startWords) {
            st.insert(sToInt(s));
        }
        for (auto s : targetWords) {
            int t = sToInt(s);
            for (int i = 0; i < s.size(); i++) {
                int t1 = t - (1 << (s[i] - 'a'));
                if (st.count(t1)) {
                    ans++;
                    break;
                }
            }
        }
        return ans;
    }

    // 3011. Find if array can be sorted
    bool canSortArray(vector<int>& nums) {
        pair<int, int> pre = {INT_MIN, INT_MIN}, cur; // {min, max}, define a pair {}
        int preBit = -1;
        for (int i = 0; i < nums.size(); i++) {
            int t = nums[i];
            int b = __builtin_popcount(t); // bit count function
            if (b != preBit) {
                // move on
                if (cur.first < pre.second) {
                    return false;
                }
                pre = cur;
                cur = {t, t};
                preBit = b;
            } else {
                cur.first = min(t, cur.first);
                cur.second = max(t, cur.second);
            }
        }
        return pre.second < cur.first;
    }

    // 1072. flip-columns-for-maximum-number-of-equal-rows
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        unordered_map<string, int> mp; // define empty map
        for (auto& row : matrix) {
            string pattern; // define empty string
            if (row[0] == 0) {
                for (int t : row)
                    pattern += to_string(t);
            } else {
                for (int t : row) {
                    pattern += to_string(t ^ 1); // ^ -- bitwise XOR
                }
            }
            mp[pattern]++;
        }
        int ans = 0;
        for (auto& pair : mp) {
            ans = max(ans, pair.second);
        }
        return ans;
    }
};
