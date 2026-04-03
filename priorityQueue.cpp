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


class PriorityQueue {
public:
    // 1353. Maximum Number of Events That Can Be Attended
    // given an array of events, each [start_day, end_day], one day can attend one event
    // events = [[1,2],[2,3],[3,4]]
    // -> 3
    // events = [[1,2],[2,3],[3,4],[1,2]]
    int maxEvents(vector<vector<int>>& events) {
        // sort two-dimension array
        sort(events.begin(), events.end(), [](auto& a, auto& b) { return a[0] < b[0]; });
        priority_queue<int, vector<int>, greater<int>> pq; // ascending
        int id = 0, day = 1, res = 0;
        while (!pq.empty() || id < events.size()) {
            while (id < events.size()) {
                if (events[id][0] <= day) {
                    pq.push(events[id][1]);
                    id++;
                } else {
                    break;
                }
            }
            // pop all lapsed
            while (!pq.empty() && pq.top() < day) {
                // put !q.empty judgment first to avoid q being empty
                pq.pop();
            }
            // pop one where end >= day
            if (!pq.empty()) {
                pq.pop();
                res++;
            }
            day++;
        }
        return res;
    }

    // 2233. Maximum Product After K Increments
    // given a vector of positive numbers and k
    // each time we can pick a number from nums and increase it by 1
    // return the possible maximum product of nums after k operations
    // e.g.
    // nums = [6,3,3,2], k = 2
    // -> 216, 6*4*3*3 = 216
    int maximumProduct(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq; // ascending
        for (auto i : nums) {
            pq.push(i);
        }
        for (int i = 0; i < k; i++) {
            int tmp = pq.top();
            pq.pop();
            tmp++;
            pq.push(tmp);
        }
        long ans = 1;
        while (!pq.empty()) {
            ans = ans * pq.top() % 100000007; // (a * b) % m = [(a % m) * (b % m)] % m
            pq.pop();
        }
        return ans;
    }
};
