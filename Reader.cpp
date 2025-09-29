#include "HeaderRecord.h"
#include "CSVBuffer.h"
#include "ZipCodeRecord.h"
#include <iostream>

int main()
{
    std::string inFileName = "binary_file.zcd";

    CSVBuffer buffer;
    
    // Open the length-indicated file (which reads header internally)
    if (!buffer.openLengthIndicatedFile(inFileName)) 
    {
        std::cerr << "Failed to open file: " << buffer.getLastError() << std::endl;
        return 1;
    }
    
    std::cout << "Successfully opened " << inFileName << std::endl;
    std::cout << "Reading first 5 records:\n" << std::endl;

    // Read records using the new method
    ZipCodeRecord record;
    int count = 0;
    while (buffer.getNextLengthIndicatedRecord(record) && count < 5) 
    {
        std::cout << "Record " << count << ": "
                  << "ZIP=" << record.getZipCode() 
                  << ", Location=" << record.getLocationName() 
                  << ", County=" << record.getCounty()
                  << ", State=" << record.getState() 
                  << ", Lat=" << record.getLatitude()
                  << ", Lon=" << record.getLongitude() << std::endl;
        count++;
    }
    
    std::cout << "\nTotal records processed: " << buffer.getRecordsProcessed() << std::endl;
    buffer.closeFile();

    return 0;
}