#ifndef ZIP_DATA_FILE
#define ZIP_DATA_FILE

#include "HeaderRecord.h"
#include "ZipCodeRecord.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

class ZipDataFile {
public:
    bool open(std::string filename);
    bool readHeader();
    bool readRecord(long offset, ZipCodeRecord& out);
    void close();
    HeaderRecord& getHeader();
    
private:
    HeaderRecord header;
    std::fstream file;
};
#endif