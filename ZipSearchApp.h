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
    


    ZipSearchApp();

    ZipSearchApp(const ZipDataFile& dataFile);

    void setDataFile(const ZipDataFile& dataFile);
    /**
     * @brief parses command line arguments
     * @param argc size of args
     * @param argv argument array
     * @return true if args are successfully parsed
     */
    bool parseArgs(int argc, char* argv);
    /**
     * @brief run search for 
     */
    void run();
    // not finished
    void displayRecord(ZipCodeRecord record, std::ostream out);
private:
    ZipDataFile dataFile;
    PrimaryKeyIndex index;
    std::vector<int> searchZips;
};
#endif