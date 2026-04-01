#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <unordered_set>

using namespace std;


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {
    }
};

class DFS {
public:
    // Back Track
    // model
    void backTrack(TreeNode* root, vector<int> vec) {
        if (root == nullptr) {
            return;
        }

        vec.push_back(root->val);

        backTrack(root->left, vec);
        backTrack(root->right, vec);

        vec.pop_back(); // backtrack
    }

    void backTrack1(vector<int> nums, int k, int index, vector<int> cur) {
        if (cur.size() == k) {
            return;
        }
        for (int i = index; i < nums.size(); i++) {
            cur.push_back(i);  // DO IT WITHIN THE LOOP !!!
            backTrack1(nums, k, i + 1, cur);
            cur.pop_back();
        }
    }

    // 77. Combinations
    // pick k from [1,2 ... n], return the picked result in any order
    // e.g.
    // n = 4, k = 2
    // -> [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]]
    //
    // Permutations Ank: pick k from n, "order it in different ways", Ank = n! / (n - k)!
    // Combinations Cnk: pick k from n, "order doesn't matter", Cnk = n! / (k! * (n - k)!)
    //
    vector<vector<int>> ans;

    vector<vector<int>> combine(int n, int k) {
        vector<int> vec;
        dfs(n, k, 1, vec);
        return ans;
    }

    void dfs(int n, int k, int index, vector<int>& vec) {
        if (vec.size() == k) {
            ans.push_back(vec);
            return;
        }
        for (int i = index; i <= n; i++) {
            vec.push_back(i); // DO IT WITHIN THE LOOP
            dfs(n, k, i + 1, vec);
            vec.pop_back();
        }
    }

    // 78. Subsets
    // backtrack
    // return all subsets of the given vector
    // e.g.
    // nums = [1,2,3]
    // -> [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
    // nums = [0]
    // -> [[],[0]]
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> vec;
        dfs(nums, ans, vec, -1);
        return ans;
    }

    void dfs(vector<int>& nums, vector<vector<int>>& ans, vector<int>& vec, int cur) {
        ans.push_back(vec);
        int n = nums.size();
        for (int i = cur + 1; i < n; i++) {
            vec.push_back(nums[i]);
            dfs(nums, ans, vec, i);
            vec.pop_back();
        }
    }

    /*
     * 可信 3
     * back track + subset
     *
     * dfs is often related to subset
     *
     * there are 2 * nums teams, each program requires two teams to perform, each team must and only perform once
     * given a list of programs, you can choose any of them to make sure each team performed once and the cost is minimum, return the minimum cost.
     * {0,1,250} means this can be performed by team 0 and 1, and the cost will be 250
     *
     * e.g.
     * num：2
     * program：[{0,1,250},{0,3,10},{1,2,25},{1,3,80},{2,3,90}]
     * -> 25, perform {0,3,10} and {1,2,25}
     */
    int ans3 = 1e9;

    int cooperativePerformance(int num, vector<vector<int>>& program) {
        unordered_set<int> st;
        dfs3(program, num, 0, 0, st);
        return ans3;
    }

    void dfs3(vector<vector<int>>& program, int num, int cur, int sum, unordered_set<int>& st) {
        if (sum >= ans3) {
            // cut branch
            return;
        }
        if (st.size() == 2 * num) {
            ans3 = max(sum, ans3);
        }
        int n = program.size();
        for (int i = cur + 1; i < n; i++) {
            if (st.count(program[i][0]) || st.count(program[i][1])) {
                continue;
            }
            st.insert(program[i][0]);
            st.insert(program[i][1]);
            sum += program[i][2];
            dfs3(program, num, i, sum, st);
            st.erase(program[i][0]);
            st.erase(program[i][1]);
        }
    }


    /*
     * 2267. 检查是否有合法括号字符串路径
     *
     * 给出一个由 "(" ")" 组成的矩阵，现在要从矩阵的左上角到右下角，每一步可往下或往右
     * 求经过路径上的所有符号，是否组成一个合法的括号序列
     *
     * 记忆化搜索
     */
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        bool state = false;
        vector<vector<vector<int>>> visited(m, vector<vector<int>>(n, vector<int>(100))); // 记忆化矩阵

        // 定义内部函数
        // function<void(int, int, int)> —— 定义函数，输入为 (int, int, int)
        // [&dfs, &grid, &state, &visited, mp, n] —— 引用外部的元素
        function<void(int, int, int)> dfs = [&dfs, &grid, &state, &visited, m, n](int i, int j, int cnt) {
            if (state) {
                return;
            }
            if (visited[i][j][cnt] != 0) {
                return;
            }
            visited[i][j][cnt] = 1;
            if (grid[i][j] == '(') {
                cnt++;
            } else {
                cnt--;
            }
            if (cnt < 0 || cnt > (m - 1 - i) + (n - 1 - j)) {
                // 此处 cnt > (mp - 1 - i) + (n - 1 - j) 条件不能少，否则超空间复杂度
                return;
            }
            if (i + 1 == m && j + 1 == n) {
                state = true;
                return;
            }
            if (i + 1 < m) {
                dfs(i + 1, j, cnt);
            }
            if (j + 1 < n) {
                dfs(i, j + 1, cnt);
            }
        };

        dfs(0, 0, 0);
        return state;
    }

    /*
     * 2246. 相邻字符不同的最长路径
     *
     * n 个节点编号 0 - n-1，parent 长为 n 记录每个节点的父节点，s 为每个节点的值。
     * 求最长"不"同值路径，带返回，并非从上到下。
     *
     * p.s.
     * a -> b -> c 路径长为 3
     */
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> tree(n);
        for (int i = 1; i < n; i++) {
            int p = parent[i];
            tree[p].push_back(i);
        }
        int ret = 1;
        int st = 0;
        dfs(st, s, tree, ret);
        return ret;
    }

    // here，string should use reference '&' or it will copy every time and become very slow
    int dfs(int& cur, string& s, vector<vector<int>>& tree, int& ret) {
        // 此处，string 记得使用地址 '&'，否则会严重影响速度导致超时
        int m0 = 0, m1 = 0;
        for (int u : tree[cur]) {
            // 此处，如果把这个提出来 vector<int> children = tree[cur] 会影响速度
            int t = dfs(u, s, tree, ret);
            if (s[u] == s[cur]) continue;
            if (t > m0) {
                m1 = m0;
                m0 = t;
            } else if (t > m1) {
                m1 = t;
            }
        }
        ret = max(ret, m0 + m1 + 1);
        return m0 + 1;
    }

    /*
     * 687. Longest Univalue Path
     *
     * Given the root of a binary tree
     * return the length of the longest path, where each node in the path has the same value.
     * This path may or may not pass through the root.
     *
     * e.g.
     *
     * 1
     * |\
     * 3 4
     * | |\
     * 2 4 4
     *   |  \
     *   4   7
     *
     * -> 3, 4-4-4-4
     */
    int longestUnivaluePath(TreeNode* root) {
        if (root == nullptr) return 0;
        dfs(root);
        return ret - 1;
    }

    int ret = 0;

    int dfs(TreeNode* tn) {
        if (tn == nullptr) return 0;
        int l = dfs(tn->left);
        int r = dfs(tn->right);
        l = tn->left != nullptr && tn->val == tn->left->val ? l : 0;
        r = tn->right != nullptr && tn->val == tn->right->val ? r : 0;
        ret = max(ret, l + r + 1);
        return max(l, r) + 1;
    }


    // 2458. height-of-binary-tree-after-subtree-removal-queries
    unordered_map<int, int> mp1; // val -> id
    unordered_map<int, int> mp2; // id -> height
    unordered_map<int, int> mp3; // id -> subtree nodes num

    int id = 0;

    int dfs(TreeNode* tn, int height) {
        // return subtree nodes num
        if (tn == NULL) {
            return 0;
        }
        mp1[tn->val] = id;
        mp2[id] = height;
        id++;
        int nl = dfs(tn->left, height + 1);
        int nr = dfs(tn->right, height + 1);
        mp3[mp1[tn->val]] = nl + nr + 1;
        return nl + nr + 1;
    }

    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        dfs(root, 0);
        vector<int> left(id, 0); // when node ID is removed, the max height of nodes where id < ID
        vector<int> right(id, 0); // when node ID is removed, the max height of nodes where id > ID
        for (int i = 0; i < id; i++) {
            right[i] = mp2[i];
            if (i > 0) {
                left[i] = max(right[i], left[i - 1]);
            }
        }
        for (int i = id - 1; i >= 0; i--) {
            right[i] = mp2[i];
            if (i < id - 1) {
                right[i] = max(right[i], right[i + 1]);
            }
        }
        vector<int> ans;

        for (int i = 0; i < queries.size(); i++) {
            int nodeId = mp1[queries[i]];
            int hl = left[nodeId - 1];
            int hr = nodeId + mp3[nodeId] < id ? right[nodeId + mp3[nodeId]] : 0;
            ans.push_back(max(hl, hr));
        }
        return ans;
    }

    // 417. Pacific Atlantic Water Flow
    // given a matrix heights, water can only flow to the surface equal to or lower than current surface, water can flow up, down, left, right.
    // pacific is at the left and up of the matrix, while atlantic at the right and bottom
    // return the vec of point that water from which can flow to both pacific and atlantic
    // e.g.
    // heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
    // -> [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
    // directions dfs
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // i row of m, j col of n
        int m = heights.size();
        int n = heights[0].size();

        vector<vector<int>> pacific(m, vector<int>(n, 0));
        vector<vector<int>> atlantic(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            dfs_417(i, 0, heights, pacific);
        }
        for (int j = 0; j < n; j++) {
            dfs_417(0, j, heights, pacific);
        }
        for (int i = 0; i < m; i++) {
            dfs_417(i, n - 1, heights, atlantic);
        }
        for (int j = 0; j < n; j++) {
            dfs_417(m - 1, j, heights, atlantic);
        }
        vector<vector<int>> res;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (atlantic[i][j] && pacific[i][j]) {
                    res.push_back({i, j}); // simple pushing back a vector
                }
            }
        }
        return res;
    }

    void dfs_417(int i, int j, vector<vector<int>>& heights, vector<vector<int>>& visited) {
        visited[i][j] = 1;
        for (auto& d : directions) {
            int x = i + d[0]; // x row, [0, m-1]
            int y = j + d[1];
            if (x < 0 || y < 0 || x >= heights.size() || y >= heights[0].size()) continue;
            if (visited[x][y]) continue;
            if (heights[x][y] < heights[i][j]) continue;
            dfs_417(x, y, heights, visited);
        }
    }
};
