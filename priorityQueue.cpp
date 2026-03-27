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
        priority_queue<int, vector<int>, greater<int>> q; // priority queue from small to large
        int id = 0, day = 1, res = 0;
        while (!q.empty() || id < events.size()) {
            while (id < events.size()) {
                if (events[id][0] <= day) {
                    q.push(events[id][1]);
                    id++;
                } else {
                    break;
                }
            }
            // pop all lapsed
            while (!q.empty() && q.top() < day) {
                // put !q.empty judgment first to avoid q being empty
                q.pop();
            }
            // pop one where end >= day
            if (!q.empty()) {
                q.pop();
                res++;
            }
            day++;
        }
        return res;
    }

    // 2233. Maximum Product After K Increments
    int maximumProduct(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;  // 最小堆 升序的优先队列

        for (auto i: nums) {
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
            ans = (ans * pq.top()) % 100000007;
            pq.pop();
        }
        return ans;
    }
};