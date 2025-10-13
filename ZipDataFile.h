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
    
    ZipDataFile();
    /**
     * @brief open file that is the filename
     * @param filename name of file being opened
     * @return true if successfully opened
     */
    bool open(std::string filename);
    
    /**
     * @brief reads zipcode and memory offset into ZipCodeRecord out
     * @param out Zipcode record being read in
     * @return true if successfully read ZipCode Record
     */
    bool readRecord(ZipCodeRecord& out);
    /**
     * @brief closes file
     */
    void close();
     /**
     * @brief getter for header
     * @return header of files
     */
    HeaderRecord& getHeader();
    /**
     * @brief getter for memory offselt
     * @return memory offset
     */
    long tellg() { static_cast<long>(file.tellg()); }//gets the memory offset and casts it to long
    
private:
    HeaderRecord header;
    std::ifstream file;
    /**
     * @brief reads header into HeaderRecord header using a HeaderBuffer
     * @return true if successfully read header
     */
    bool readHeader();
};
#endif