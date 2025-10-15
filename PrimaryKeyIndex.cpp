#include "PrimaryKeyIndex.h"
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
        listMangerAdd(record, dataOffset);
    }
}

bool PrimaryKeyIndex::write(std::string filename){
    
}

bool PrimaryKeyIndex::read(std::string filename){
    
}

std::vector<size_t> PrimaryKeyIndex::find(int zip){
    
}

bool PrimaryKeyIndex::contains(int zip){
    
}

    
size_t PrimaryKeyIndex::size() const{

}

void PrimaryKeyIndex::listMangerAdd(const ZipCodeRecord& zipRecord, const size_t& memoryOffset){
    SecondaryIndexEntry sEntry;
    PrimaryIndexEntry pEntry;
    if((secondaryContains(zipRecord.getZipCode()) == -1)){
        sEntry.zip = zipRecord.getZipCode();
        sEntry.arrayIndex = -1; //temp value
        addSecondarySorted(sEntry); //adds entry to secondary array and gets index
    }
    int sIndex = secondaryContains(zipRecord.getZipCode());
    pEntry.offset = memoryOffset;
    pEntry.nextIndex = -1; //end of list
    addPrimary(secondaryEntries[sIndex], pEntry); //add entry to primary array
}

int PrimaryKeyIndex::secondaryContains(int zip){
    if (secondaryEntries.size() == 0) return false; //if list is empty not found
    int left = 0;
    int right = secondaryEntries.size() - 1;

    //basic binary search
    while (left <= right) {
        int mid = left + (right - left) / 2; // avoid overflow

        if (secondaryEntries[mid].zip == zip) {
            return mid; // found
        }
        else if (secondaryEntries[mid].zip < zip) {
            left = mid + 1; // search right half
        }
        else {
            right = mid - 1; // search left half
        }
    }
    return -1; // not found
}

int PrimaryKeyIndex::addSecondarySorted(const SecondaryIndexEntry& entry){
    int size = secondaryEntries.size();
    if (size == 0){ //if empty add to list
        secondaryEntries.push_back(entry);
        return size;
    }
    //if not empty add into list sorted
    int index = 0;
    while(index < secondaryEntries.size()){
        
        if(secondaryEntries[index].zip > entry.zip){
            secondaryEntries.insert(secondaryEntries.begin() + index, entry); //
            return index;
        }
        index++;
    }
    secondaryEntries.push_back(entry);
}

int PrimaryKeyIndex::addPrimary(SecondaryIndexEntry& sEntry, const PrimaryIndexEntry& pEntry){
    int size = primaryEntries.size();
    if (size == 0 || sEntry.arrayIndex == -1){ //if list is empty or secondary index chain hasn't started push back and update sEntry
        primaryEntries.push_back(pEntry);
        sEntry.arrayIndex = size;
        return size;
    }

    //if not empty and chain has started traverse to end of chain of primary indexs and adds to the end of list
    int index = sEntry.arrayIndex;
    while(primaryEntries[index].nextIndex != -1){
        index = primaryEntries[index].nextIndex;
    }
    primaryEntries.push_back(pEntry);
    primaryEntries[index].nextIndex = size;
    return size;
}