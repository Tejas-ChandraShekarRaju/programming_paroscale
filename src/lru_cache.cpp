#include "lru_cache.h"
#include <iostream>

using namespace std;

LRUCache::LRUCache(int cap) : capacity(cap) {
    cout << "Created cache with capacity: " << capacity << endl;
}

// Here I'm making sure to move the recently accessed item to the front of the list and updating the lookup map.

void LRUCache::moveToFront(CacheList::iterator it) {
    if (it == items.begin()) return;
    
    cout << "Moving to front: " << it->first << endl;

    items.splice(items.begin(), items, it);
    lookup[it->first] = items.begin();
}

// here im removing from map and list from behind. 
void LRUCache::evictLRU() {
    if (items.empty()) return;
    
    auto& lru = items.back();
    cout << "Evicting: " << lru.first << endl;
    
    lookup.erase(lru.first); 
    items.pop_back();
}

bool LRUCache::add(const string& filename) {
    
    auto it = lookup.find(filename);
    
    if (it != lookup.end()) {
        // File exists - update and move to front
        try {
            // only updating time - 
            it->second->second->cached_time = time(nullptr); // Update cached time
            moveToFront(it->second);
            return true;
        } catch (...) {
            return false;
        }
    }
    
    // New file
    try {
        auto file_info = make_shared<FileInfo>(filename);
        
        if ((int)items.size() >= capacity) {
            evictLRU();
        }
        
        items.emplace_front(filename, file_info);
        lookup[filename] = items.begin();
        
        cout << "Added! Cache size: " << items.size() << "/" << capacity << endl;
        return true;
        
    } catch (...) {
        cout << "Error adding file" << endl;
        return false;
    }
}

shared_ptr<FileInfo> LRUCache::search(const string& filename) {
    cout << "\nSearching: " << filename << endl;
    
    auto it = lookup.find(filename);
    
    if (it == lookup.end()) {
        cout << "Not found" << endl;
        return nullptr;
    }
    
    cout << "Found!" << endl;
    moveToFront(it->second);
    return it->second->second;
}

bool LRUCache::remove(const string& filename) {
    cout << "\nRemoving: " << filename << endl;
    
    auto it = lookup.find(filename);
    if (it == lookup.end()) {
        cout << "Not found" << endl;
        return false;
    }
    
    items.erase(it->second);
    lookup.erase(it);
    cout << "Removed!" << endl;
    return true;
}

int LRUCache::size() {
    return (int)items.size();
}

void LRUCache::printCache() {
    cout << "\nCache contents (" << size() << "/" << capacity << "):" << endl;
    
    if (items.empty()) {
        cout << "Empty" << endl;
        return;
    }
    
    int i = 1;
    for (auto& item : items) {
        cout << i++ << ". " << item.first 
                  << " (" << item.second->size << " bytes)" 
                  << " [refs:" << item.second.use_count() << "]" << endl;
    }
}

void LRUCache::clear() {
    items.clear();
    lookup.clear();
    cout << "Cache cleared" << std::endl;
}