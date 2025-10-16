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
        listAddManager(record, dataOffset);
    }
}

bool PrimaryKeyIndex::write(const std::string& filename){
    std::ofstream out(filename, std::ios::binary);
    if (!out) return false; //if file cannot be opened return false

    for (auto& s : secondaryEntries) //write all the secondary entries
        out.write(reinterpret_cast<const char*>(&s), sizeof(s));

    //end of list denoter (impossible zip code)
    SecondaryIndexEntry sentinel{-9999999, -1}; // end of first list
    out.write(reinterpret_cast<const char*>(&sentinel), sizeof(sentinel)); //write end of list denoter

    for (auto& p : primaryEntries)
        out.write(reinterpret_cast<const char*>(&p), sizeof(p));

    out.close();
    return true;
}

bool PrimaryKeyIndex::read(const std::string& filename){
    std::ifstream in(filename, std::ios::binary);
    if (!in) return false; //if file cannot be opened return false

    //clear first 2 lists
    secondaryEntries.clear();
    primaryEntries.clear();

    //read until end of list denoter
    SecondaryIndexEntry temp;
    while (in.read(reinterpret_cast<char*>(&temp), sizeof(temp))) {
        if (temp.zip == -9999999) break; //if end of first list break
        secondaryEntries.push_back(temp); //if not add entries to vector
    }

    //read the rest into the primary vector
    PrimaryIndexEntry ptemp;
    while (in.read(reinterpret_cast<char*>(&ptemp), sizeof(ptemp))) {
        primaryEntries.push_back(ptemp); 
    }

    return true;
}

std::vector<size_t> PrimaryKeyIndex::find(const uint32_t zip) const{
    std::vector<size_t> addresses;
    int index = secondaryContains(zip); //get index of the zipcode
    if (index != -1){ //if zip is in secondary key list
        int index = secondaryEntries[index].arrayIndex;
        while(primaryEntries[index].nextIndex != -1){
            addresses.push_back(primaryEntries[index].offset);
            index = primaryEntries[index].nextIndex;
        }
        addresses.push_back(primaryEntries[index].offset);
        return addresses;
    }
}

bool PrimaryKeyIndex::contains(const uint32_t zip) const{
    return (secondaryContains(zip) != -1);
}



void PrimaryKeyIndex::listAddManager(const ZipCodeRecord& zipRecord, const size_t& memoryOffset){
    SecondaryIndexEntry sEntry;
    PrimaryIndexEntry pEntry;
    int sIndex = secondaryContains(zipRecord.getZipCode());
    if((sIndex == -1)){
        sEntry.zip = zipRecord.getZipCode();
        sEntry.arrayIndex = -1; //temp value
        addSecondarySorted(sEntry); //adds entry to secondary array and gets index
    }
    
    pEntry.offset = memoryOffset;
    pEntry.nextIndex = -1; //end of list
    addPrimary(secondaryEntries[sIndex], pEntry); //add entry to primary array
}

int PrimaryKeyIndex::secondaryContains(const uint32_t zip) const{
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