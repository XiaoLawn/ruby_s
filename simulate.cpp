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


class Simulate {
public:

    // 1717. Maximum Score From Removing Substrings
    // for each round, each ab gains x points, and ba gains y points, return the maximum points
    // s = "cdbcbbaaabab", x = 4, y = 5
    // cdbcbbaaa(ba)b +5 -> cdbcb(ba)aab +5 -> cdbc(ba)ab +5 -> cdbc(ab) +4 -> cdbc
    // -> 19
    //
    // s = "aabbaaxybbaabb", x = 5, y = 4
    // a(ab)baaxybba(ab)b +10 -> (ab)aaxybb(ab) +10 -> aaxybb
    // -> 20
    int maximumGain(string s, int x, int y) {
        // c1c2 is always higher than c2c1, which is x points
        char c1 = 'a', c2 = 'b';
        if (x < y) {
            swap(x, y);
            swap(c1, c2);
        }
        int res = 0, cnt1 = 0, cnt2 = 0;
        for (char c : s) {
            if (c == c1) {
                cnt1 += 1;
            } else if (c == c2) {
                if (cnt1 > 0) {  // c1c2 pairs immediately
                    cnt1--;
                    res += x;
                } else {
                    cnt2++;
                }
            } else {  // reach another sector
                res += y * min(cnt1, cnt2); // for all c2c1 pairs
                cnt1 = 0;
                cnt2 = 0;
            }
        }
        res += y * min(cnt1, cnt2);
        return res;
    }

    // 1493. Longest Subarray of 1's After Deleting One Element
    // given an array of 0 and 1, calculate forward for 1 num in the left of 0, backward for the right of 0
    // nums = [1,1,0,1]
    // -> 3
    // nums = [0,1,1,1,0,1,1,0,1]
    // -> 5
    // nums = [1,1,1]
    // -> 2
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> vec(n, 0);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                cnt++;
            } else {
                vec[i] = cnt;
                cnt = 0;
            }
        }
        if (cnt == n) {
            return n - 1;
        }
        cnt = 0;
        int res = 0;
        for (int j = n - 1; j >= 0; j--) {
            if (nums[j] == 1) {
                cnt++;
            } else {
                res = max(vec[j] + cnt, res);
                cnt = 0;
            }
        }
        return res;
    }

    // 781. Rabbits in Forest
    // Given answers of rabbits saying how many other rabbits that have the same color as it
    // e.g.
    // [1,1,2]
    // -> 5
    int numRabbits(vector<int>& answers) {
        int ans = 0;
        sort(answers.begin(), answers.end());
        int n = answers.size();
        int pre = 0;
        int tmp = 0;
        for (int i = 0; i < n; i++) {
            int cur = answers[i];
            if (cur == pre && tmp > 0) {
                tmp--;
            } else {
                tmp = cur;
                ans += cur + 1;
            }
            pre = cur;
        }
        return ans;
    }

    // 1861. Rotating the Box
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        vector<vector<char>> grid;
        for (auto& vec : box) {
            vector<char> newVec = sortVec(vec);
            grid.push_back(newVec);
        }
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<char>> ans(m, vector<char>(n));
        for (int i = 0; i < n; i++) {
            vector<char> row;
            for (int j = 0; j < m; j++) {
                ans[j][n - i - 1] = grid[i][j];
            }
        }
        return ans;
    }

    vector<char> sortVec(vector<char> vec) {
        int cntIt = 0;  // stone
        int cntSp = 0;  // empty
        vector<char> res;
        for (char c : vec) {
            if (c == '#') {  // stone
                cntIt++;
            } else if (c == '.') {  // empty
                cntSp++;
            } else {  // obstacle
                for (int i = 0; i < cntSp; i++) res.push_back('.');
                for (int i = 0; i < cntIt; i++) res.push_back('#');
                res.push_back('*');
                cntIt = 0;
                cntSp = 0;
            }
        }
        for (int i = 0; i < cntSp; i++) res.push_back('.');
        for (int i = 0; i < cntIt; i++) res.push_back('#');
        return res;
    }

    /*
     * 2271. 毯子覆盖的最多白色砖块数
     *
     * 给定数组 vector<vector<int>> &tiles，每一个 tile 为一块白色砖块，覆盖 [a, b] 区域
     * 有一块长度为 carpetLen 的毯子，求这块毯子最多覆盖多少快白色砖块？
     *
     * e.g.
     * tiles = [[1,5],[10,11],[12,18],[20,25],[30,32]], carpetLen = 10
     * -> 9
     * 毯子从 10 开始，最多可覆盖 9 块砖块
     *
     * 不要轻易将 区间 化为 实际 进行模拟。
     * 前缀和 + 二分查找
     *
     */
    int maximumWhiteTiles1(vector<vector<int>> &tiles, int carpetLen) {
        sort(tiles.begin(), tiles.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[0] < b[0];
        });
        const int n = tiles.size();
        vector<long long> p(n + 1);  // 记录 从 0 到 当前 tile 之前有多少个砖
        for (int i = 1; i <= n; i++) p[i] = p[i - 1] + tiles[i - 1][1] - tiles[i - 1][0] + 1;
        int ans = 0;
        vector<int> v(n);  // 如果 vector 自己有序递增的话，可以直接用 lower_bound 来二分查找
        for (int i = 0; i < n; i++) v[i] = tiles[i][0];
        for (int i = 0; i < n; i++) {
            // 二分查找 —— 毯子结束后 的第一个砖块
            int idx = lower_bound(v.begin(), v.end(), v[i] + carpetLen) - v.begin();  // lower_bound 要减去 v.begin()
            int t = p[idx - 1] - p[i] +
                    min(
                            tiles[idx - 1][1] - tiles[idx - 1][0] + 1,  // 最后一个砖块的总长
                            v[i] + carpetLen - v[idx - 1]  // 最后一块砖并没有盖完
                    );
            ans = max(ans, t);
        }
        return ans;
    }

    /*
     * 2272. 最大波动的子字符串
     * 求 最大波动的子字符串
     *
     * s = "aababbb"
     * -> 3
     * 最大波动的子字符串为 "babbb"，b 比 a 多 3 个
     *
     */
    int largestVariance(string &s) {
        int ans = 0;
        for (char a = 'a'; a <= 'z'; ++a)
            for (char b = 'a'; b <= 'z'; ++b) {
                if (a == b) continue;
                int diff = 0;
                int diff_with_b = -2e9;
                for (char ch: s) {  // 计算 a 比 b 多多少个
                    if (ch == a) {
                        diff++;
                        diff_with_b++;
                    } else if (ch == b) {  // 遇到 b 才激活记录。。。
                        diff--;
                        diff_with_b = diff;
                        diff = max(diff, 0);
                    }
                    ans = max(ans, diff_with_b);
                }
            }
        return ans;
    }

    /*
     * 2264. 字符串中最大的 3 位相同数字
     */
    string largestGoodInteger(string num) {
        char c = 0;
        // 字符串中连续三个的组合判断，只需判断中间那个
        for (int i = 1, n = num.size() - 1; i < n; ++i) {
            if (num[i - 1] == num[i] && num[i] == num[i + 1]) {
                c = max(c, num[i]);
            }
        }
        return c == 0 ? "" : string(3, c);  // string(3, c) 表示由 3 个 c 字符组成的 string
    }

    /*
     * 5987. 删除元素后和的最小差值
     * 给出数组 nums 共有 3n 个元素，现删掉数组中的 n 个元素（元素顺序不变）
     * 使剩下 2n 个元素 "前 n 个之和 - 后 n 个之和" 最小，求该最小值
     *
     * e.g.
     * nums = [7,9,5,8,1,3]
     * -> 1
     * 删除 9, 1 剩余 7, 5, 8, 3 此时 (7 + 5) - (8 + 3) 最小
     *
     * 与动态规划类似 —— 枚举分割点 + 堆
     * 问题等价于：枚举数组的分割点，将数组分成两半，在左侧取最小的 n/3 个元素，在右侧取最大的 n/3 个元素，然后计算左侧的和与右侧的和，取它们的差的最小值
     */
    long long minimumDifference(vector<int>& nums) {
        int m = nums.size(), n = m / 3;
        long long l = 0, r = 0;  // l是左边的和，r是右边的和
        priority_queue<int> left;  // 小顶堆
        priority_queue<int, vector<int>, greater<>> right;  // 大顶堆
        vector<long long> arr(n + 1);  // arr[i] 是分割点为 nums[i + n] 时右侧(包括分割点)最大的和；分割点可为 nums[n] 到 nums[2n - 1]
        for (int i = 0; i < n; ++i) {
            l += nums[i];
            left.push(nums[i]);
            r += nums[i + 2 * n];
            right.push(nums[i + 2 * n]);
        }
        arr[n] = r;
        for (int i = 2 * n - 1; i >= n; --i) {  // 分割点为 i 时右侧(包括分割点)最大的和，存入 arr
            if (nums[i] > right.top()) {
                r += nums[i] - right.top();
                right.pop();
                right.push(nums[i]);
            }
            arr[i - n] = r;
        }
        long long ret = l - arr[0];
        for (int i = n; i < n * 2; ++i) {  // 求分割点为 i 时左侧最小的和
            if (nums[i] < left.top()) {
                l += nums[i] - left.top();
                left.pop();
                left.push(nums[i]);
            }
            ret = min(ret, l - arr[i - n + 1]);  // 左侧已经包括了分割点，所以取右侧时要 + 1
        }
        return ret;
    }

    /*
     * 5977. 最少交换次数来组合所有的 1 II
     * 给出一个由 0, 1 组合而成的环形数组，每次可以交换 0 和 1 位置，最终使得 0, 1 聚在一起，求最少交换次数
     *
     * [0,1,0,1,1,0,0] -> 1
     * [0,1,1,1,0,0,1,1,0] -> 2
     * [1,0,1,1,1,0,0,1,1,0,1] -> 2
     * 1,1,0,1,1,0,1,1,1,0,0 -> 1,1,2 留一个最大的，求最小的的和
     *
     * [0,1,0,0,1,0,0,0,1] -> 1,2,3
     * 最终状态，0需要聚集在一起，1需要聚集在一起，0和1对等
     */
    int minSwaps(vector<int>& nums) {
        int k = 0;
        for (int t: nums) {
            if (t == 1) k++;
        }
        if (k == 0) return 0;
        vector<int> ring = nums;  // 拼接数组
        ring.insert(ring.end(), nums.begin(), nums.end());  // vector insert 的用法
        int n = ring.size();
        int cnt = 0;  // cnt 为滑动窗口中 1 的个数
        int ans = INT_MAX;  // 最大的 int
        for (int i = 0; i < n; i++) {
            if (ring[i] == 1) {
                cnt++;
            }
            if (i >= k - 1) {
                ans = min(ans, k - cnt);
                if (ring[i - k + 1] == 1) {
                    cnt--;
                }
            }
        }
        return ans;
    }

    /*
     * 5983. 同时运行 N 台电脑的最长时间
     */
    long long maxRunTime(int n, vector<int>& batteries) {
        sort(batteries.begin(), batteries.end(), [](int a, int b) { return a > b; });
        // 除了电量最多的n个电池，其他电池包里的电池，是可以任意加的
        int num = batteries.size();
        long long extra = 0;
        for (int i = n; i < num; i++) {
            extra += batteries[i];
        }
        int w = 1;
        long long ans = 0;
        for (int i = n - 1; i > 0; i--) {
            int h = batteries[i - 1] - batteries[i];
            int m = w * h;
            if (extra >= m) {
                extra -= m;
            } else {
                ans = batteries[i] + extra / w;
                break;
            }
            w++;
        }
        if (ans == 0) {
            ans = batteries[0] + extra / w;
        }
        return ans;
    }

    /*
     * 5982. 解决智力问题
     */
    long long mostPoints(vector<vector<int>>& questions) {
        long long ans = 0;
        int n = questions.size();
        vector<long long> dp(n);  // 选该问题 时 最大总得分
        vector<long long> gets(n);
        long long get = 0;
        for (int i = 0; i < n; i++) {
            get = max(get, dp[i]);

            vector<int> question = questions[i];
            dp[i] = get + question[0];
            ans = max(ans, dp[i]);

            if (i + question[1] + 1 < n) {
                dp[i + question[1] + 1] = max(dp[i], dp[i + question[1] + 1]);
            }
        }
        return ans;
    }

    /*
     * 5194. 得到目标值的最少行动次数
     */
    int minMoves(int target, int maxDoubles) {
        // 加倍都要用；且都要用在后面，否则毫无意义
        int cnt = 0;
        while (target > 1) {
            if (maxDoubles == 0) {
                return cnt + target - 1;
            }
            if ((target & 1) == 1) {
                target -= 1;
            } else {
                if (maxDoubles > 0) {
                    target >>= 1;
                    maxDoubles--;
                } else {
                    target -= 1;
                }
            }
            cnt++;
        }
        return cnt;
    }

    /*
     * 2136. 全部开花的最早一天
     *
     * 先种 花生长期长的 绝对没错
     */
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        int n = plantTime.size();
        vector<int> id(n);
        iota(id.begin(), id.end(), 0);  // 使用iota将结构体数组填满
        sort(id.begin(), id.end(), [&growTime](int a, int b) { return growTime[a] > growTime[b]; });
        int now = 0;
        int ans = 0;
        for (int u: id) {
            now += plantTime[u];
            ans = max(ans, now + growTime[u]);
        }
        return ans;
    }

    /*
     * 2100. 适合打劫银行的日子
     * 你和一群强盗准备打劫银行。给你一个下标从 0 开始的整数数组 security ，其中 security[i] 是第 i 天执勤警卫的数量。日子从 0 开始编号。同时给你一个整数 time 。
     * 如果第 i 天满足以下所有条件，我们称它为一个适合打劫银行的日子：
     * 第 i 天前和后都分别至少有 time 天。
     * 第 i 天前连续 time 天警卫数目都是 递减 的。
     * 第 i 天后连续 time 天警卫数目都是 递增 的。
     *
     * e.g.
     * security = [5,3,3,3,5,6,2], time = 2
     * -> [2,3]
     *
     * security = [1,1,1,1,1], time = 0
     * -> [0,1,2,3,4]
     *
     * security = [1,2,3,4,5,6], time = 2
     * -> []
     */
    vector<int> goodDaysToRobBank(vector<int> &security, int time) {
        int n = security.size();
        vector<int> left(n);  // vector 用作 Java 中的有界数组
        for (int i = 1; i < n; i++) {
            if (security[i - 1] >= security[i]) {
                left[i] = left[i - 1] + 1;
            }
        }
        vector<int> right(n);
        for (int i = n - 2; i >= 0; i--) {
            if (security[i + 1] >= security[i]) {
                right[i] = right[i + 1] + 1;
            }
        }
        vector<int> ans;  // vector 用作 Java 中的 ArrayList
        for (int i = 0; i < n; i++) {
            if (left[i] >= time && right[i] >= time) {
                ans.push_back(i);
            }
        }
        return ans;
    }

    /*
     * 2099. 找到和最大的长度为 K 的子序列
     */
    vector<int> maxSubsequence(vector<int> &nums, int k) {
        vector<pair<int, int>> vec;
        for (int i = 0; i < nums.size(); i++) {
            vec.push_back(make_pair(i, nums[i]));  // pair(下标, 值)
        }
        sort(vec.begin(), vec.end(), [](pair<int, int> &a, pair<int, int> &b) {  // 自定义结构体排序
            return a.second > b.second;
        });

        while (vec.size() > k) {
            vec.pop_back();
        }
        sort(vec.begin(), vec.end(), [](pair<int, int> &a, pair<int, int> &b) {
            return a.first < b.first;
        });
        vector<int> ans;
        for (auto &it: vec) ans.push_back(it.second);
        return ans;
    }

    // 2051. longest-square-streak-in-an-array
    int longestSquareStreak(vector<int> &nums) {
        map<int, int> mp; // num -> number of nums that are it's square
        sort(nums.begin(), nums.end());
        int res = -1;
        for (int num: nums) {
            int sq = sqrt(num); // square root or num
            if (sq * sq == num && mp.find(sq) != mp.end()) {
                int t = mp[sq];
                mp[num] = t + 1;
                res = max(res, t + 1);
            } else {
                mp[num] = 1;
            }
        }
        return res;
    }

};