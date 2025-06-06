#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <string>
#include <sys/stat.h>
#include <ctime>

using namespace std;

class FileInfo {
public:
    string path;
    size_t size;
    time_t modified_time;
    time_t cached_time;
    ino_t inode;

    FileInfo(const string& file_path);
    void print();
};

#endif