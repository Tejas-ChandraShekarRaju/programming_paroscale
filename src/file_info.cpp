#include "file_info.h"
#include <iostream>
#include <stdexcept>

using namespace std;



FileInfo::FileInfo(const string& file_path) : path(file_path) {
    struct stat file_stat;
    
    stat(file_path.c_str(), &file_stat);
    
    size = file_stat.st_size;
    modified_time = file_stat.st_mtime;
    inode = file_stat.st_ino;
    cached_time = time(nullptr);
}

void FileInfo::print() {
    cout << "File: " << path << endl;
    cout << "Size: " << size << " bytes" << endl;
    cout << "Inode: " << inode << endl;
    cout << "Modified: " << ctime(&modified_time);
    cout << "Cached: " << ctime(&cached_time);
}