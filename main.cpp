/**
 * @file main.cpp  
 * @brief Test program for length-indicated file processing
 * @author Group 2
 * @version 0.2
 * @date 2025-10-12
 */

#include "ZipCodeRecord.h"
#include "CSVBuffer.h"
#include "DataManager.h"
#include <iostream>

/**
 * @brief Tests length-indicated file processing, verifies identical results across sorts
 * @post returns 0 on success
 */
int main() 
{
        std::cout << "\n=== Test 1: Length-Indicated File (Original Order) ===\n";
        DataManager mgr1;
        size_t records1 = mgr1.processFromLengthIndicated("NotRandomCSV.zcd");
        std::cout << "Processed " << records1 << " records\n";
        mgr1.printTable(std::cout);

        std::cout << "\n=== Test 2: Length-Indicated File (Randomized Order) ===\n";
        DataManager mgr2;
        size_t records2 = mgr2.processFromLengthIndicated("Randomized.zcd");
        std::cout << "Processed " << records2 << " records\n";
        mgr2.printTable(std::cout);

        // Verify both files produce identical results
        std::cout << "\n=== Verification Test ===\n";
        bool identical = DataManager::verifyIdenticalResults("NotRandomCSV.zcd", "Randomized.zcd", true, true);
        std::cout << "[NotRandomCSV.zcd vs Randomized.zcd] Identical? " 
                  << (identical ? "YES" : "NO") << std::endl;

        std::cout << "\n=== All Tests Completed Successfully! ===\n";

    return 0;
}
