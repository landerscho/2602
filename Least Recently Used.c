#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cacheList; // {key, value}
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) return -1;
        // 참조된 항목을 리스트 맨 앞으로 이동
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        return cacheMap[key]->second;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            cacheMap[key]->second = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            return;
        }
        if (cacheList.size() == capacity) {
            int lruKey = cacheList.back().first;
            cacheList.pop_back();
            cacheMap.erase(lruKey);
        }
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }
};

int main() {
    LRUCache lru(3);
    lru.put(1, 100);
    lru.put(2, 200);
    lru.put(3, 300);
    cout << "Key 1 조회: " << lru.get(1) << "\n"; // 1이 최신화됨
    lru.put(4, 400); // 가장 오래된 Key 2가 제거됨
    cout << "Key 2 조회 (제거됨): " << lru.get(2) << "\n";
    return 0;
}
