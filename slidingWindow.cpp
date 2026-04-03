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

class slidingWindow {
public:
    // 2962. Count Subarrays Where Max Element Appears at Least K Times
    // 2302. Count Subarrays With Score Less Than K
    // 2537. Count the Number of Good Subarrays
    // in subarray.cpp


    // 3. Longest Substring Without Repeating Characters
    // return the length of the longest substring without duplicate characters
    // e.g.
    // s = "abcabcbb"
    // -> 3
    // s = "pwwkew"
    // -> 3
    // s = "bbbbb"
    // -> 1
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        unordered_map<int, int> mp;
        int r = 0, l = 0, ans = 0;
        while (r < n) {
            int cur = s[r] - 'a';
            mp[cur]++;
            while (mp[cur] > 1 && l < r) {
                int t = s[l] - 'a';
                mp[t]--;
                l++;
            }
            ans = max(ans, r - l + 1);
            r++;
        }
        return ans;
    }

    // 3439. Reschedule Meetings for Maximum Free Time I
    // Total event time is [0, eventTime], you can reschedule k meetings, but the order of the meeting should be kept
    // return the maximum free time(time between meetings)
    // e.g.
    // eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
    // -> 2
    // eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
    // -> 6
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        vector<int> free;
        int n = startTime.size();
        int start = 0, end;
        for (int i = 0; i < n; i++) {
            end = startTime[i];
            free.push_back(end - start);
            start = endTime[i];
        }
        free.push_back(eventTime - start);
        n = free.size();
        int sum = 0, res = 0;
        for (int i = 0; i < k + 1 && i < n; i++) {
            sum += free[i];
        }
        res = sum;
        for (int i = k + 1; i < n; i++) {
            sum += free[i];
            sum -= free[i - k - 1];
            res = max(res, sum);
        }
        return res;
    }

    // 3440. Reschedule Meetings for Maximum Free Time II
    // Total event time is [0, eventTime], you can reschedule 1 meeting, the order of the meeting can be changed
    // e.g.
    // eventTime = 5, startTime = [1,3], endTime = [2,5]
    // -> 2
    // eventTime = 10, startTime = [0,3,7,9], endTime = [1,4,8,10]
    // -> 6
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int n = startTime.size();
        vector<int> gaps;
        int start = 0, end = 0;
        for (int i = 0; i < n; i++) {
            end = startTime[i];
            gaps.push_back(end - start);
            start = endTime[i];
        }
        gaps.push_back(eventTime - start);

        vector<int> rightMax(n - 1);
        int mx = 0;
        for (int i = n - 2; i >= 0; i--) {
            mx = max(mx, gaps[i + 2]);
            rightMax[i] = mx;
        }

        int res = 0, leftMax = 0;
        for (int i = 0; i < n; i++) {
            if (i > 0) leftMax = max(leftMax, gaps[i - 1]);
            int event = endTime[i] - startTime[i];
            if (rightMax[i] >= event || leftMax >= event) {
                res = max(res, gaps[i] + gaps[i + 1] + event);
            } else {
                res = max(res, gaps[i] + gaps[i + 1]);
            }
        }
        return res;
    }
};
