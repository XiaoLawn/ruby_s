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

class binaryTree {
public:

    // 865. Smallest Subtree with all the Deepest Nodes
    // return the TreeNode of the smallest subtree which contains all the deepest nodes
    /*
     * e.g.
     * 1
     * |\
     * 3 4
     * | |\
     * 2 6 5
     *   |  \
     *   8   7
     *
     * -> 4
     *
     *
     */

    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        queue<TreeNode *> q;
        int curSize = 1, nextSize = 0;
        q.push(root);
        vector<TreeNode *> snapShot;
        unordered_map<TreeNode *, TreeNode *> mp;
        while (!q.empty()) {
            for (int i = 0; i < curSize; i++) {
                TreeNode* tn = q.front();
                snapShot.push_back(tn);
                q.pop();
                if (tn->left) {
                    mp[tn->left] = tn;
                    q.push(tn->left);
                    nextSize++;
                }
                if (tn->right) {
                    mp[tn->right] = tn;
                    q.push(tn->right);
                    nextSize++;
                }
            }
            if (nextSize == 0) {
                break;
            }
            curSize = nextSize;
            nextSize = 0;
            snapShot.clear();
        }
        unordered_set<TreeNode *> st(snapShot.begin(), snapShot.end()); // initialize set from vector
        while (st.size() > 1) {
            unordered_set<TreeNode *> next;
            for (auto& u : st) {  // & means it's a reference, not a copy
                next.insert(mp[u]);
            }
            st = next;
        }
        return *st.begin(); // return
    }

    /*
     * 236. Lowest Common Ancestor of a Binary Tree
     * e.g.
     * 1
     * |\
     * 3 4
     * | |\
     * 2 6 5
     *   |  \
     *   8   7
     * p = 8, q = 5
     * -> 4
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left != nullptr && right != nullptr) {
            return root;
        }
        if (left) return left;
        if (right) return right;
        return nullptr;
    }

    // 235. Lowest Common Ancestor of a Binary Search Tree
    TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            if (p->val > root->val && q->val > root->val) {
                root = root->right;
            } else if (p->val < root->val && q->val < root->val) {
                root = root->left;
            } else {
                return root;
            }
        }
        return nullptr;
    }

    /*
     * 1123. Lowest Common Ancestor of Deepest Leaves
     * e.g.
     * 1
     * |\
     * 3 4
     * | |\
     * 2 6 5
     *   |  \
     *   8   7
     * -> 4
     */
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        pair<TreeNode *, int> p = dfs1123(root, 0);
        return p.first;
    }

    pair<TreeNode *, int> dfs1123(TreeNode* tn, int depth) {
        if (tn == nullptr) {
            return {nullptr, depth}; // new way to return pair()
        }
        auto pl = dfs1123(tn->left, depth + 1);
        auto pr = dfs1123(tn->right, depth + 1);

        if (pl.second > pr.second) {
            return pl;
        }
        if (pl.second < pr.second) {
            return pr;
        }
        return {tn, pl.second};
    }
};
