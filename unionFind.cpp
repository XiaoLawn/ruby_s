#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <numeric>
#include <algorithm>
#include "utils.cpp"

using namespace std;

class UnionFind {
public:
    vector<int> parent;

    UnionFind(int size) : parent(size + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        int u = find(parent[i]);
        parent[i] = u;
        return u;
    }

    void unite(int i, int j) {
        parent[j] = find(i);
    }
};

class UnionFindSolution {
    // 1488. Avoid Flood in The City
    // given an array of rains
    // when rains[i] > 0 means on i day it rains on rains[i] river
    // when rains[i] = 0 means it's a dry day, and we can find a river to dry
    // if there are consecutive rains on the same river, there will be a flood.
    // return the plans to dry the river to avoid flood, return an empty array if flood is unavoidable
    // e.g.,
    // rains = [1,2,3,4]
    // -> [-1,-1,-1,-1]
    // rains = [1,2,0,0,2,1]
    // -> [-1,-1,2,1,-1,-1]
    // rains = [1,2,0,1,2]
    // -> []
    // rains = [69,0,0,0,69]
    // -> [-1,69,1,1,-1]
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        UnionFind uf(n);
        unordered_map<int, int> mp;
        vector<int> res(n, 1);
        for (int i = 0; i < n; i++) {
            int river = rains[i];
            if (river == 0) {
                // it's a dry day
                continue;
            }
            // today isn't a dry day, it rains on "river"
            res[i] = -1;
            uf.unite(i, i + 1); // we unite i and i + 1
            if (mp.count(river)) {
                // river has rained before
                int u = uf.find(mp[river]); // day u is the dry day
                if (u >= i) {
                    return {};
                }
                uf.unite(u, u + 1);
                res[u] = river;
            }
            mp[river] = i;
        }
        return res;
    }
};