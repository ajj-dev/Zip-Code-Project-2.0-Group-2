#include "CSVBuffer.h"
#include "HeaderRecord.h"
#include "ZipCodeRecord.h"
#include "stdint.h"
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::string inFileName = "PT2_CSV_Randomized.csv";
    std::string outFileName = "binary_file.zcd";

    CSVBuffer csvBuffer;

    // Setup header
    HeaderRecord header;
    header.setFileStructureType("ZIPC");
    header.setVersion(1);
    header.setSizeFormatType(0);  // 0 = ASCII (CSV text)
    header.setSizeOfSizes(4);
    header.setSizeInclusionFlag(0);
    header.setIndexFileName("zipcode_data.idx");
    header.setRecordCount(0);  // Placeholder

    std::vector<FieldDef> fields; //defines fields and lengths and adds them to a vector
    fields.push_back({"zipcode", 1});
    fields.push_back({"location", 3});
    fields.push_back({"county", 3});
    fields.push_back({"state", 4});
    fields.push_back({"latitude", 2});
    fields.push_back({"longitude", 2});

    header.setFields(fields); //sets fields of the header
    header.setFieldCount(csvBuffer.EXPECTED_FIELD_COUNT);
    header.setPrimaryKeyField(0);

    std::ofstream out(outFileName, std::ios::binary);

    // Write header
    auto headerData = header.serialize();
    out.write(reinterpret_cast<char*>(headerData.data()), headerData.size());
    
    // Calculate record count offset in header
    size_t recordCountOffset = 4 + 2 + 4 + 1 + 4 + 1 + 2 + header.getIndexFileName().length();
    
    // Stream through CSV and write length-indicated CSV records
    if (!csvBuffer.openFile(inFileName)) 
    {
    std::cerr << "Failed to open CSV file: " << csvBuffer.getLastError() << std::endl;
    return 1;
    }

    std::cout << "Successfully opened " << inFileName << std::endl;
    
    ZipCodeRecord record;
    while (csvBuffer.getNextRecord(record)) 
    {
        // Convert record to CSV string
       std::string recordStr = std::to_string(record.getZipCode()) + "," +
                        record.getLocationName() + "," +
                        std::string(record.getState()) + "," +     
                        record.getCounty() + "," +                 
                        std::to_string(record.getLatitude()) + "," +
                        std::to_string(record.getLongitude());
        uint32_t len = recordStr.length();
        out.write(reinterpret_cast<char*>(&len), 4);
        out.write(recordStr.c_str(), len);
    }
    
    
    // Get actual record count and update header
    uint32_t actualRecordCount = csvBuffer.getRecordsProcessed();
    out.seekp(recordCountOffset);
    out.write(reinterpret_cast<char*>(&actualRecordCount), sizeof(uint32_t));
    
    csvBuffer.closeFile();
    out.close();
    
    std::cout << "Converted " << actualRecordCount << " records to " << outFileName << std::endl;
    return 0;
}