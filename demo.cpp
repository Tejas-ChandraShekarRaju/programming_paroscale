#include "lru_cache.h"  
#include "file_info.h"   
#include <iostream>
#include <fstream>

void createTestFiles() {
    std::ofstream("file1.txt") << "Small file content";
    std::ofstream("file2.txt") << "Medium file with more content here";
    std::ofstream("file3.txt") << "Large file with lots of content and data";
    std::ofstream("file4.txt") << "Another file";
    std::cout << "Created test files" << std::endl;
}

void cleanup() {
    system("rm -f file*.txt");
    std::cout << "Cleaned up test files" << std::endl;
}

int main() {
    std::cout << "=== LRU Cache Demo ===" << std::endl;
    
    createTestFiles();
    
    // Create cache
    LRUCache cache(3);
    
    std::cout << "\n--- Adding files ---" << std::endl;
    cache.add("file1.txt");
    cache.add("file2.txt");
    cache.add("file3.txt");
    cache.printCache();
    
    std::cout << "\n--- Adding 4th file (evicts oldest) ---" << std::endl;
    cache.add("file4.txt");
    cache.printCache();
    
    std::cout << "\n--- Searching files ---" << std::endl;
    auto file = cache.search("file2.txt");
    if (file) {
        std::cout << "Found file2.txt:" << std::endl;
        file->print();
    }
    cache.printCache();
    
    std::cout << "\n--- Shared pointer demo ---" << std::endl;
    auto saved_file = cache.search("file3.txt");
    std::cout << "Saved pointer to file3.txt (refs: " << saved_file.use_count() << ")" << std::endl;
    
    // Force eviction
    cache.add("file1.txt");  // This will evict file3.txt from cache
    cache.printCache();
    
    std::cout << "\nBut our saved pointer still works:" << std::endl;
    if (saved_file) {
        std::cout << "File size: " << saved_file->size << " bytes" << std::endl;
        std::cout << "Refs: " << saved_file.use_count() << std::endl;
    }
    
    std::cout << "\n--- Removing file ---" << std::endl;
    cache.remove("file2.txt");
    cache.printCache();
    
    cleanup();
    std::cout << "\nDemo complete!" << std::endl;
    return 0;
}