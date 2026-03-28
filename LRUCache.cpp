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
        this->capacity = capacity;  // member reference type 'LRUCache *' is a pointer;
    }

    int get(int key) {
        if (mp.find(key) == mp.end()) {
            return -1;
        }

        // Move accessed node to front (most recent)
        auto it = mp[key];
        int value = it->second;

        cache.erase(it);
        cache.push_front({key, value});
        mp[key] = cache.begin();

        return value;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            // Remove old node
            cache.erase(mp[key]);
        }

        // Insert new node at front
        cache.push_front({key, value});
        mp[key] = cache.begin();

        // If over capacity, remove LRU (back)
        if (cache.size() > capacity) {
            auto last = cache.back();  // .back() return the object, not the pointer
            mp.erase(last.first);
            cache.pop_back();
        }
    }
};