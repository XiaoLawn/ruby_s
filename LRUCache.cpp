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
    }

    int get(int key) {
    }

    void put(int key, int value) {
    }
};