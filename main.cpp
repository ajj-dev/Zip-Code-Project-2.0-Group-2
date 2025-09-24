/**
 * @file test_main.cpp  
 * @brief Test program for ZipCodeRecord and CSVBuffer classes
 * @author Group 2
 * @version 0.1
 * @date 2025-09-11
 */

#include "ZipCodeRecord.h"
#include "CSVBuffer.h"
#include "DataManager.h"
#include <iostream>

/**
 * @brief The main function loads the zipcodes from a csv file, computes the north south east and west extremes and then prints a table. 
 * @post returns 0 on success.
 */
int main() 
{
    try {
        std::cout << "\n=== Assignment Output: Per-State Extremes Table ===\n";
        DataManager mgr;
        // Use the canonical source CSV for the required table output to stdout:
        mgr.loadFromCsv("CSV_ZipCode_Sort.csv");
        mgr.computeExtremes();
        mgr.printTable(std::cout); // REQUIRED: directed to standard output

        // Optional: demonstrate identical results across differently sorted CSVs
        bool identical = DataManager::verifyIdenticalResults(
            "CSV_ZipCode_Sort.csv",
            "CSV_County_Sort.csv"
        );
        //prints weather the data is identical accross sorts
        std::cerr << "[Verification] Identical results across sorts? "
                  << (identical ? "YES" : "NO") << std::endl;
    } catch (const std::exception& ex) { 
        //prints error message on exception
        std::cerr << "ERROR (DataManager): " << ex.what() << std::endl;
    }

    std::cout << "All tests completed!"; //success message
    return 0;
}
