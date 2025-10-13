#include "PrimaryKeyIndex.h"
#include "ZipDataFile.h"
#include "ZipCodeRecord.h"
#include <iostream>

#include <fstream>
#include <string>
#include <cstring>
#include <vector>

/**
 * @file PrimaryKeyIndex.cpp
 * @author Group 2
 * @brief PrimaryKeyIndex for storing 
 * @version 0.1
 * @date 2025-10-12
 */

void PrimaryKeyIndex::createFromDataFile(CSVBuffer& buffer){
    ZipCodeRecord record;
    size_t dataOffset = buffer.getMemoryOffset();
    while (buffer.getNextLengthIndicatedRecord(record)) {
        IndexEntry entry; 
        entry.zip = record.getZipCode();
        entry.offset = dataOffset; 
        entries.push_back(entry);
        dataOffset = buffer.getMemoryOffset();
    }
}

bool PrimaryKeyIndex::write(std::string filename){
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) return false;
    for (const auto& entry : entries) {
        outFile.write(reinterpret_cast<const char*>(&entry.zip), sizeof(entry.zip));
        outFile.write(reinterpret_cast<const char*>(&entry.offset), sizeof(entry.offset));
        if (!outFile) return false; 
    }
    outFile.close();
    return true;
}

bool PrimaryKeyIndex::read(std::string filename){
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) return false; //fail
    
    // figure out file size
    inFile.seekg(0, std::ios::end);
    std::streampos fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    // how many entries
    size_t entryCount = fileSize / sizeof(IndexEntry);
    entries.clear();
    entries.reserve(entryCount);

    for(size_t i = 0; i < entryCount; i++){
        IndexEntry entry;
        inFile.read(reinterpret_cast<char*>(&entry.zip), sizeof(entry.zip));
        inFile.read(reinterpret_cast<char*>(&entry.offset), sizeof(entry.offset));
        if (!inFile) return false; //fail
        entries.push_back(entry);
    }
    return true; //success
}

std::vector<long> PrimaryKeyIndex::find(int zip){
    std::vector<long> addressOffsets;
    for(int i = 0; i < size(); i++){
        if(entries[i].zip == zip){
            addressOffsets.push_back(entries[i].offset);
        }
    }
    return addressOffsets;
}

bool PrimaryKeyIndex::contains(int zip){
    for(int i = 0; i < size(); i++){
        if(entries[i].zip == zip){
            return true;
        }
    }
    return false;
}

    
size_t PrimaryKeyIndex::size() const{
    return entries.size();
}