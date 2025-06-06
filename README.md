# programming_paroscale

### *Setup*
```bash
# Install build tools - I manually installed make previously
sudo apt install build-essential

#clone
git clone <repository-url>

cd programming_paroscale

#build and run
make           # Build library and demo
make run       # Build and run demo
make clean     # Clean build files


```

### **References**
1. Folder structure - Because I had done this recently Followed CMU Database Systems Course (15-445/645) structure from https://15445.courses.cs.cmu.edu/fall2024/ and GitHub repo https://github.com/cmu-db/bustub
2. AI-Generated Code - Used AI for Makefile, demo.cpp (test case file) and some helper print functions
3. General References - Referred internet for understanding C++ syntax, STL containers, smart pointers, and file system operations. 

### **Core Implementation and Design Choices**
- The questions says implement LRU for applications using files, but the impelementation is different for different for different kind of applications for example a build system does not need a refernce counter for eviction but a database application does. For now I've used a sharedpointer version as a middle ground for this impelementation, which means once cache is accessed even if another thread evicts it the accessed metadata is still valid.
- DUring add if file is already cached, Im only updating the cached time and not the metadata(we can update required metadata) but this will defeat the purpose if we have to call stat again. 
- LRU operations are all O(1) time complexity because of the use of hashmap for look up and doubly linked list for reordering. 



### **Output**
You'll see something like this. 
![image](https://github.com/user-attachments/assets/1ad2e3db-abf8-43c8-b773-817a6dc31991)
