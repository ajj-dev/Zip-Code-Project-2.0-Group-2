#ifndef ZIP_SEARCH_APP
#define ZIP_SEARCH_APP

#include "PrimaryKeyIndex.h"
#include "CSVBuffer.h"
#include "ZipCodeRecord.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

class ZipSearchApp {
public:
    


    ZipSearchApp();

    ZipSearchApp(std::string file);

    void setDataFile(std::string file);
    /**
     * @brief parses command line arguments
     * @param argc size of args
     * @param argv argument array
     * @return true if args are successfully parsed
     */
    bool search(int argc, char* argv[]){
        
    }
    
private:
    std::string fileName;
    PrimaryKeyIndex index;
};
#endif