/**
 * @file test_main.cpp  
 * @brief Test program for ZipCodeRecord and CSVBuffer classes
 * @author Group 2
 * @version 0.1
 * @date 2025-09-11
 */

#include "ZipCodeRecord.h"
#include "CSVBuffer.h"
#include "DataManager.h"   // <<< ADDED
#include <iostream>

int main() 
{
    std::cout << "Testing ZipCodeRecord and CSVBuffer classes" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    // Test 1: ZipCodeRecord basic functionality
    std::cout << "Test 1: ZipCodeRecord creation and comparison" << std::endl;;
    ZipCodeRecord record1(1001, 42.0702, -72.6227, "Agawam", "MA", "Hampden");
    ZipCodeRecord record2(501, 40.8154, -73.0451, "Holtsville", "NY", "Suffolk");
    
    std::cout << "Record 1: " << record1 << std::endl;
    std::cout << "Record 2: " << record2 << std::endl;
    
    // Test comparison methods
    std::cout << "Comparison tests:" << std::endl;
    std::cout << "Record 1 is north of Record 2: " 
              << (record1.isNorthOf(record2) ? "Yes" : "No") << std::endl;
    std::cout << "Record 1 is east of Record 2: " 
              << (record1.isEastOf(record2) ? "Yes" : "No") << std::endl;
    std::cout << "Record 2 is south of Record 1: " 
              << (record2.isSouthOf(record1) ? "Yes" : "No") << std::endl;
    std::cout << "Record 2 is west of Record 1: " 
              << (record2.isWestOf(record1) ? "Yes" : "No") << std::endl;
    
    // Test 2: CSV Buffer functionality  
    std::cout << "Test 2: CSV File Reading" << std::endl;
    CSVBuffer buffer;
    
    // Try to open the CSV file
    if (buffer.openFile("CSV_ZipCode_Sort.csv")) 
    {
        std::cout << "Successfully opened CSV file" << std::endl;
        
        ZipCodeRecord record;
        int count = 0;
        
        // Read first few records to test
        std::cout << "First 5 records from CSV: ";
        while (buffer.getNextRecord(record) && count < 5) 
        {
            std::cout << "Record " << (count + 1) << ": " << record << std::endl;
            count++;
        }
        
        std::cout << "Total records processed: " << buffer.getRecordsProcessed() << std::endl;
        std::cout << "Current line number: " << buffer.getCurrentLineNumber() << std::endl;
        
        buffer.closeFile();
    } 
    else 
    {
        std::cout << "Failed to open CSV file: " << buffer.getLastError() << std::endl;
        std::cout << "Make sure 'zipcode_data.csv' exists in the current directory" << std::endl;
    }
    
    // Test 3: Error handling
    std::cout << "Test 3: Error Handling";
    ZipCodeRecord invalidRecord;
    
    std::cout << "Testing invalid zip code: " 
              << (invalidRecord.setZipCode(-1) ? "Success" : "Failed (expected)") << std::endl;
    std::cout << "Testing invalid latitude: " 
              << (invalidRecord.setLatitude(100.0) ? "Success" : "Failed (expected)") << std::endl;
    std::cout << "Testing invalid state: " 
              << (invalidRecord.setState("ABC") ? "Success" : "Failed (expected)") << std::endl;

    // ===========================
    // Assignment additions (minimal)
    // ===========================
    try {
        std::cout << "\n=== Assignment Output: Per-State Extremes Table ===\n";
        DataManager mgr;
        // Use the canonical source CSV for the required table output to stdout:
        mgr.loadFromCsv("zipcode_data.csv");
        mgr.computeExtremes();
        mgr.printTable(std::cout); // REQUIRED: directed to standard output

        // Optional: demonstrate identical results across differently sorted CSVs
        bool identical = DataManager::verifyIdenticalResults(
            "CSV_ZipCode_Sort.csv",
            "CSV_County_Sort.csv"
        );
        std::cerr << "[Verification] Identical results across sorts? "
                  << (identical ? "YES" : "NO") << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "ERROR (DataManager): " << ex.what() << std::endl;
    }

    std::cout << "All tests completed!";
    return 0;
}
