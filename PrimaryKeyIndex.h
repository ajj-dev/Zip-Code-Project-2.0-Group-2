#ifndef PRIMARY_KEY_INDEX
#define PRIMARY_KEY_INDEX

#include "CSVBuffer.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

/**
 * @file PrimaryKeyIndex.h
 * @author Group 2
 * @brief PrimaryKeyIndex for storing 
 * @version 0.1
 * @date 2025-10-12
 */

/**
 * @class PrimaryKeyIndex
 * @brief Represents the primary key index of a file
 * @details maps zipcodes and there memory offsets
 */
class PrimaryKeyIndex {
public:
    //struct representation of an index entry
    struct IndexEntry {
        int zip; //zip code
        size_t offset; //byte offset of the record
    };
    /**
     * @brief reads data from a zip data file and creates a map from it
     * @param dataFile the dataFile being read from
     */
    void createFromDataFile(CSVBuffer& buffer);
    /**
     * @brief saves the index to a binary index file
     * @return true if successful write to file
     */
    bool write(std::string filename);
    /**
     * @brief reads index from a binary index file
     * @return true if successfuly reads from file
     */
    bool read(std::string filename);
    /**
     * @brief finds zip code in entries and returns memory offsets with the matching zip
     * @param zip zip code being searched for
     * @return memory offset of zip code (-1 if not in memory)
     */
    std::vector<size_t> find(int zip);
    /**
     * @brief searches if a zip code is in the map
     * @param zip zip code being searched for
     * @return returns true if in the map
     */
    bool contains(int zip);
    /**
     * @brief getter for size of map
     * @return returns size of the map
     */
    size_t size() const;
    
private:
    std::vector<IndexEntry> entries; //map of zip codes and byte offsets
};
#endif