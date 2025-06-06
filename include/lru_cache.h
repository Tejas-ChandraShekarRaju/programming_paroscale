#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "file_info.h"
#include <unordered_map>
#include <list>
#include <memory>
#include <string>

using namespace std;

class LRUCache {
private:
    using FilePtr = shared_ptr<FileInfo>;
    using CacheList = list<pair<string, FilePtr>>;
    using CacheMap = unordered_map<string, CacheList::iterator>;
    
    int capacity;
    CacheList items;
    CacheMap lookup;
    
    void moveToFront(CacheList::iterator it);
    void evictLRU();

public:
    LRUCache(int cap);
    
    bool add(const string& filename);
    shared_ptr<FileInfo> search(const string& filename);
    bool remove(const string& filename);
    
    int size();
    void printCache();
    void clear();
};

#endif