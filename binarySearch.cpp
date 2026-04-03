#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;


class BinarySearch {
public:
    // lower_bound return the index of first item >= u
    int lower_bound(vector<int> vec, int u) {
        int l = 0, r = vec.size(); // r = vec.size()
        while (l < r) {
            // l < r
            int m = (l + r) / 2;
            if (vec[m] >= u) {
                // vec[m] >= u, if descending sequence vec <= u
                r = m;
            } else {
                l = m + 1; // l = m + 1, l = m might go into an infinite loop
            }
        }
        return l;
    }

    /**
     * Binary search in solution space
     */

    // 3296. Minimum Number of Seconds to Make Mountain Height Zero
    // A mountain with height h, and a group of workers dig simultaneously
    // worker[i] digs the 1st unit in worker[i] second, then the 2nd unit costs 2*worker[i], third 3*worker[i]...
    // return the min number of second that can dig the whole mountain
    //
    // Binary search in solution space
    //
    // e.g.
    // mountainHeight = 4, workerTimes = [2,1,1]
    // -> 3,
    // worker[0] digs 1 in 2,
    // worker[1] digs 2 in 1 + 2 = 3,
    // worker[2] digs 1 in 1
    // max(2,3,1) = 3
    //
    // mountainHeight = 10, workerTimes = [3,2,2,4]
    // -> 12,
    // worker[0] digs 2 unit in 3 + 6 = 9,
    // worker[1] digs 3 in 2 + 4 + 6 = 12,
    // worker[2] digs 3 in 2 + 4 + 6 = 12,
    // worker[3] digs 2 in 4 + 8 = 12.
    // max(9,12,12,12) = 12
    using ll = long long;

    ll minNumberOfSeconds(int h, vector<int>& workers) {
        ll l = 0, r = 1e16; // or LLONG_MAX
        while (l < r) {
            ll m = (l + r) >> 1;
            if (canDo(h, workers, m)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }


    bool canDo(int h, vector<int>& workers, ll t) {
        int n = workers.size();
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            // how many h a worker can dig in t time?
            ll h1 = sqrt(2 * t / workers[i] + 0.25) - 0.5;
            sum += h1;
            if (sum >= h) return true;
        }
        return false;
    }

    /*
     * 2187. Minimum Time to Complete Trips
     * time[i] denotes the time taken by the ith bus to complete one trip.
     * Each bus can make multiple trips one after another, and buses don't effect each other.
     * return the minimum time to complete total number of trips.
     *
     * Binary search in solution space
     *
     * e.g.
     * time = [1,2,3], totalTrips = 5
     * -> 3, 1th bus 3 trips, 2nd 1 trip, 3rd 1 trip, total 5 trips
     *
     */
    ll minimumTime(vector<int>& time, int totalTrips) {
        int n = time.size();
        ll r = LLONG_MAX;
        for (int i = 0; i < n; i++) {
            ll t = (ll) time[i] * totalTrips;
            r = min(r, t);
        }
        ll l = 1;
        while (l < r) {
            ll m = (l + r) >> 1;
            if (isGood(time, m, totalTrips)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }

    bool isGood(vector<int>& time, ll totalTime, int totalTrips) {
        int n = time.size();
        for (int i = 0; i < n; i++) {
            int t = totalTime / time[i];
            totalTrips -= t;
            if (totalTrips <= 0) return true;
        }
        return false;
    }

    // 2071. 你可以安排的最多任务数目
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(), tasks.end()); // 事情难度，从小到大
        sort(workers.begin(), workers.end(), [](int a, int b) { return a > b; }); // 工人能力从大到小
        int n = min(tasks.size(), workers.size());
        int l = 0, r = n + 1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (canDo(tasks, workers, pills, strength, m)) {
                l = m + 1; // 注意，l最终是"上层"的第一个
            } else {
                r = m;
            }
        }
        return l - 1;
    }


    bool canDo(vector<int>& tasks, vector<int>& workers, int pills, int strength, int num) {
        // 找出最好的num个人，做最简单的num个事情
        // 给最弱的几个吃药丸，然后重新排序；如果这样，结果会是错的，因为 "为了完成所有任务，药丸不一定给最弱的人吃"
        vector<int> curWorkers(num);
        for (int i = 0; i < num; i++) {
            curWorkers[i] = workers[i]; // 力量最大的num个人
        }
        for (int i = num - 1; i >= 0; i--) {
            int curTask = tasks[i];
            bool found = false;
            for (int j = 0; j < num; j++) {
                if (curWorkers[j] >= curTask) {
                    curWorkers[j] = -1;
                    found = true;
                    break;
                }
            }
            if (found) continue;
            if (pills == 0) return false;
            for (int j = num - 1; j >= 0; j--) {
                int curW = curWorkers[j];
                if (curW < 0) continue;
                if (pills > 0 && curW + strength >= curTask) {
                    curWorkers[j] = -1;
                    pills--;
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }

    // 2064. minimized-maximum-of-products-distributed-to-any-store
    int minimizedMaximum(int stores, vector<int>& qty) {
        int low = 1, high = *max_element(qty.begin(), qty.end());
        while (low < high) {
            int mid = (low + high) / 2;
            int needed = 0;
            for (int q : qty) {
                needed += (q + mid - 1) / mid;
            }
            if (needed <= stores) {
                high = mid;
            } else
                low = mid + 1;
        }
        return low;
    }
};
