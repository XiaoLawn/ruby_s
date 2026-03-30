class EventManager {
public:
    // id -> rank
    set<pair<int, int>> st; // {rank, id}
    unordered_map<int, int> mp; // id -> rank

    EventManager(vector<vector<int>>& events) {
        for(vector<int> ev : events) {
            int id = ev[0];
            int rk = ev[1];
            st.insert({rk, -id});
            mp[id] = rk;
        }
    }

    void updatePriority(int id, int rk) {
        int oldRk = mp[id];
        st.erase({oldRk, -id});

        st.insert({rk, -id});
        mp[id] = rk;
    }

    int pollHighest() {
        if(st.size() == 0) {
            return -1;
        }
        auto p = prev(st.end());
        int ans = -p -> second;
        mp.erase(ans);
        st.erase(p);
        return ans;
    }

};

/**
 * Your EventManager object will be instantiated and called as such:
 * EventManager* obj = new EventManager(events);
 * obj->updatePriority(eventId,newPriority);
 * int param_2 = obj->pollHighest();
 */