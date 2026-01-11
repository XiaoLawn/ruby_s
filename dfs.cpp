#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

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
    // examples:
    // 78. Subsets
    void backTrack(TreeNode* root, vector<int> vec) {
        if (root == nullptr) {
            return;
        }

        vec.push_back(root->val);

        backTrack(root->left, vec);
        backTrack(root->right, vec);

        vec.pop_back(); // backtrack
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

    // 此处，string 记得使用地址 '&'，否则会严重影响速度导致超时
    // 尽量用 '&' ，能提速不少
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
     * 687. 最长同值路径
     *
     * 二叉树，求最长同值路径，带返回，并非从上到下。
     *
     * p.s.
     * a -> b -> c 路径长为 2
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
