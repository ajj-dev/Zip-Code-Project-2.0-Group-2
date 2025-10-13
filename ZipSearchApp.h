#ifndef ZIP_SEARCH_APP
#define ZIP_SEARCH_APP

#include "ZipDataFile.h"
#include "PrimaryKeyIndex.h"
#include "ZipCodeRecord.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

class ZipSearchApp {
public:
    bool parseArgs(int argc, char* argv);
    void run();
    void displayRecord(ZipCodeRecord record, std::ostream out);
private:
    ZipDataFile dataFile;
    PrimaryKeyIndex index;
    std::vector<int> searchZips;
};
#endif