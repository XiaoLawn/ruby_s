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

    int findSmallestInteger(vector<int>& nums, int value) {
        // [1,-10,7,13,6,8]
        // ->
        // [1,0,2,3,1,3]
        // [0,1,1,2,3,3]
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int t = nums[i];
            while (t < 0) {
                t += value;
            }
            nums[i] = t % value;
        }
        map<int, int> mp;
        for (int u : nums) {
            mp[u]++;
        }
        int res = 0;
        while (mp.count(res % value) && mp[res % value]) {
            mp[res % value]--;
            res++;
        }
        return res;
    }

    // Tiktok written test
    // Given the photos that track the path of a trip, return the whole trip route from beginning to the end
    // e.g.
    // photos = [[1,4], [1,5], [2,4], [3,5]]
    // 1 -> 4,5
    // 2 -> 4
    // 3 -> 5
    // 4 -> 2,1
    // 5 -> 1,3
    // -> [2,4,1,5,3] or [3,5,1,4,2]
    vector<int> findTravelPath(vector<vector<int>> photos) {
        unordered_map<int, vector<int>> mp;
        for (vector<int> p : photos) {
            int a = p[0];
            int b = p[1];
            if (mp.count(a)) {
                vector<int>& v = mp[a];
                v.push_back(b);
            } else {
                vector<int> v{b};
                mp[a] = v;
            }
            if (mp.count(b)) {
                vector<int>& v = mp[b];
                v.push_back(a);
            } else {
                vector<int> v{a};
                mp[b] = v;
            }
        }
        int cur = -1;
        for (auto& [k, v] : mp) {
            if (v.size() == 1) {
                cur = k;
                break;
            }
        }
        vector<int> res;
        set<int> visited;
        visited.insert(cur);
        res.push_back(cur);
        while (true) {
            vector<int>& v = mp[cur];
            for (int u : v) {
                if (!visited.count(u)) {
                    cur = u;
                }
            }
            visited.insert(cur);
            res.push_back(cur);
            if (res.size() == mp.size()) {
                break;
            }
        }
        return res;
    }

    // 3202. Find the Maximum Length of Valid Subsequence II
    // find the maximum length of subsequence of nums that remainder over k
    // (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[n - 2] + sub[n - 1]) % k
    // dynamic processing
    // nums = [1,2,3,4,5], k = 2
    // -> 5, [1,2,3,4,5]
    // nums = [1,4,2,3,1,4], k = 3
    // -> 4, [1,4,1,4]
    int maximumLength(vector<int>& nums, int k) {
        int res = 0;
        int n = nums.size();
        for (int j = 0; j < k; j++) {
            // for each possible value of u % k = j
            vector<int> dp(k, 0); // dp[i] is the max length of subsequence that (sub[n - 2] + sub[n - 1]) % k == j
            for (int i = 0; i < n; i++) {
                int mod = nums[i] % k;
                dp[mod] = dp[(j - mod + k) % k] + 1;
            }
            for (int u : dp) {
                res = max(res, u);
            }
        }
        return res;
    }

    // TT Hackerrank 2
    // return the number of subarray that contains k distinct elements
    // e.g.
    // k = 2, nums = [2,3,3,2,1,2,2]
    // -> 10
    int atMostKDistinct(const vector<int>& nums, int k) {
        unordered_map<int, int> count;
        int left = 0, res = 0;

        for (int right = 0; right < nums.size(); ++right) {
            if (count[nums[right]] == 0)
                --k;
            count[nums[right]]++;
            while (k < 0) {
                count[nums[left]]--;
                if (count[nums[left]] == 0)
                    ++k;
                left++;
            }

            res += right - left + 1;
        }
        return res;
    }

    int countDistinct(int k, vector<int> nums) {
        return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
    }

    bool isValid(string s) {
        int n = s.length();
        if (n < 3) return false;

        int vowels = 0, consonants = 0;
        string vowelList = "aeiouAEIOU";

        for (char c : s) {
            if (isalpha(c)) {
                if (vowelList.find(c) != string::npos) {
                    vowels++;
                } else {
                    consonants++;
                }
            } else if (!isdigit(c)) {
                return false; // invalid character
            }
        }

        return vowels >= 1 && consonants >= 1;
    }

    // 6. Zigzag Conversion
    string convert(string s, int numRows) {
        int sz = 2 * numRows - 2;
        vector<vector<char>> grid;
        int n = s.size();
        vector<char> cur;
        for (int i = 0; i < n; i++) {
            if (cur.size() == sz) {
                grid.push_back(cur);
                cur.clear();
            }
            cur.push_back(s[i]);
        }
        grid.push_back(cur);
        string ans = "";
        for (int i = 0; i < numRows; i++) {
            // print ith element of each vector
            for (vector<char> vec : grid) {
                if (i < vec.size()) ans += vec[i];
                if (i != 0 && i != numRows - 1) {
                    if (sz - i < vec.size()) ans += vec[sz - i];
                }
            }
        }
        return ans;
    }

    // 13. Roman to Integer
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

    // 2444. Count Subarrays With Fixed Bounds
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long ans = 0;
        int minIdx = -1, maxIdx = -1, badIdx = -1;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] < minK || nums[i] > maxK) {
                badIdx = i;
            }
            if (nums[i] == minK) {
                minIdx = i;
            }
            if (nums[i] == maxK) {
                maxIdx = i;
            }
            ans += max(0, min(minIdx, maxIdx) - badIdx);
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
