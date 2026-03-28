#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
private:
    int capacity;

    // Doubly linked list: (key, value)
    list<pair<int, int>> cache;

    // Map: key -> iterator pointing to list node
    unordered_map<int, list<pair<int, int>>::iterator> mp;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (mp.find(key) == mp.end()) {
            return -1;
        }
        auto it = mp[key];
        int value = it->second;  // this is when an iterator acts like a pointer
        cache.erase(it);
        cache.push_front({key, value});
        mp[key] = cache.begin();
        return value;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            auto it = mp[key];
            cache.erase(it);
            mp.erase(key);
        }
        cache.push_front({key, value});
        mp[key] = cache.begin();
        if (cache.size() > capacity) {
            auto back = cache.back();
            mp.erase(back.first);
            cache.pop_back();
        }
    }
};