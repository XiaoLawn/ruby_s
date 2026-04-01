class EventManager {
public:
    // 3885. Design Event Manager
    // initialize with multiple events, [[id, priority], [id, priority], [id, priority]]
    //
    // void updatePriority(int id, int pt)
    // update event by id, set priority to `pt`
    //
    // int pollHighest()
    // Removes and returns the id of the event with the highest rank, for the same rank, return the smallest id
    //
    // the use of set (ordered)
    set<pair<int, int>> st; // {priority, id}
    unordered_map<int, int> mp; // id -> priority

    EventManager(vector<vector<int>>& events) {
        for (vector<int> ev : events) {
            int id = ev[0];
            int pt = ev[1];
            st.insert({pt, -id}); // pt from low to high, id from high to low so we put negative
            mp[id] = pt;
        }
    }

    void updatePriority(int id, int pt) {
        int oldPt = mp[id];
        st.erase({oldPt, -id});  // erase by value
        st.insert({pt, -id});
        mp[id] = pt;
    }

    int pollHighest() {
        if (st.size() == 0) {
            return -1;
        }
        auto p = prev(st.end());  // prev(st.end()) returns the iterator of the last value
        int ans = -p->second;
        mp.erase(ans);
        st.erase(p);  // set can erase by iterator, vector can't
        return ans;
    }
};

/**
 * Your EventManager object will be instantiated and called as such:
 * EventManager* obj = new EventManager(events);
 * obj->updatePriority(eventId,newPriority);
 * int param_2 = obj->pollHighest();
 */
