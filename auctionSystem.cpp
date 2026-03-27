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

// 3815. Design Auction System
// implement addBid, updateBid, removeBid, getHighestBidder
class AuctionSystem {
public:
    map<int, map<int, int>> ump;  // uid -> [itid -> bid]
    map<int, set<pair<int, int>>> itmp;  // itid -> [{bid, uid}]

    AuctionSystem() {
    }

    void addBid(int uid, int itid, int bid) {
        if(ump.count(uid)) {
            itmp[itid].erase({ump[uid][itid], uid});
        }
        ump[uid][itid] = bid;

        itmp[itid].insert({bid, uid});
    }

    void updateBid(int uid, int itid, int bid) {
        addBid(uid, itid, bid);
    }

    void removeBid(int uid, int itid) {
        int ob = ump[uid][itid];
        ump[uid].erase(itid);
        itmp[itid].erase({ob, uid});
    }

    int getHighestBidder(int itid) {
        // no bid return -1
        if(itmp[itid].empty()) {  // C++ mp[xx], if xx not exist, auto initialize it (0, "", [], {} ...)
            return -1;
        }
        return itmp[itid].rbegin()->second;
    }
};
