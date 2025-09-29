#ifndef HEADER_RECORD
#define HEADER_RECORD

#include "stdint.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

// Field definition
struct FieldDef 
{
    std::string name; // Name of the field
    uint8_t type;     // 1=int, 2=float, 3=string, etc.
};

class HeaderRecord
{
public:
    HeaderRecord(); // Default Constructor
    std::vector<uint8_t> serialize() const; // Convert to binary format
    static HeaderRecord deserialize(const uint8_t* data); // Read from binary format

    // Getters
     const char* getFileStructureType() const;
    uint16_t getVersion() const;
    uint32_t getHeaderSize() const; 
    uint8_t getSizeFormatType() const;
    uint32_t getSizeOfSizes() const;
    uint8_t getSizeInclusionFlag() const;
    const std::string& getIndexFileName() const;
    uint32_t getRecordCount() const;
    uint16_t getFieldCount() const;
    const std::vector<FieldDef>& getFields() const; 
    uint8_t getPrimaryKeyField() const;

    // Setters
    void setFileStructureType(const char* type);
    void setVersion(uint16_t ver);
    void setHeaderSize(uint32_t size);
    void setSizeFormatType(uint8_t type);
    void setSizeOfSizes(uint32_t size);
    void setSizeInclusionFlag(uint8_t flag);
    void setIndexFileName(const std::string& filename);
    void setRecordCount(uint32_t count);
    void setFieldCount(uint16_t count);
    void setFields(const std::vector<FieldDef>& fieldDefs);
    void setPrimaryKeyField(uint8_t field);

    // Utility Methods
    void addField(const FieldDef& field);

private:
    char fileStructureType[4]; // "ZIPC"
    uint16_t version; // File format version
    uint32_t headerSize; // Size of the header record
    uint8_t sizeFormatType; // 0 for Ascii 1 for Binary
    uint32_t sizeOfSizes; // How many bytes are used to represent the length field (IE: 1 = 255 bytes, 2 = 65,535 bytes)
    uint8_t sizeInclusionFlag; // Boolean flag that detrmines if [this] is also included in the size. 
    std::string indexFileName; // Name of the key index file
    uint32_t recordCount; // Total number of records
    uint16_t fieldCount; // Count of fields per record
    std::vector<FieldDef> fields;
    uint8_t primaryKeyField; // Unique Identifier for each field (IE: 0 = Zip Code, 1 = State, 2 = County, etc.)
};

#endif