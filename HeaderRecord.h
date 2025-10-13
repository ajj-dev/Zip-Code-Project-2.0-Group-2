#ifndef HEADER_RECORD
#define HEADER_RECORD

#include "stdint.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
/**
 * @file HeaderRecord.h
 * @author Group 2
 * @brief HeaderRecord class for storing header information
 * @version 0.1
 * @date 2025-10-02
 */


// Field definition
struct FieldDef 
{
    std::string name; // Name of the field
    uint8_t type;     // 1=int, 2=float, 3=string, etc.
};

/**
 * @class ZipCodeRecord
 * @brief Represents the information in the header of a file
 * @details Stores file structure type, file version, header size, size Format Type, size of sizes, size inclusion flags, index file names, record count, field count, fields and the primary key field
 */
class HeaderRecord
{
public:
    /**
     * @brief Default constructor
     * @details Initializes all fields to default values
     */
    HeaderRecord(); // Default Constructor
    
    ~HeaderRecord();
    /**
     * @brief serialize
     * @details returns the header in binary format
     */
    std::vector<uint8_t> serialize() const;
    /**
     * @brief deserialize
     * @details converts data vetctor into Header record format and returns it
     * @param data serialized header
     * @returns deserialized data in the form of a HeaderRecord
     */
    static HeaderRecord deserialize(const uint8_t* data); // Read from binary format

    
    /**
     * @brief File Structure Type Getter
     * @returns fileStructureType[4]
     */
    const char* getFileStructureType() const;
    /**
     * @brief Version Getter
     * @returns version
     */
    uint16_t getVersion() const;
    /**
     * @brief HeaderSize Getter
     * @returns headerSize
     */
    uint32_t getHeaderSize() const; 
    /**
     * @brief Size Format Type Getter
     * @returns sizeFormatType
     */
    uint8_t getSizeFormatType() const;
    /**
     * @brief Size of Sizes Getter
     * @returns sizeOfSizes
     */
    uint32_t getSizeOfSizes() const;
    /**
     * @brief Size Inclusion Flag Getter
     * @returns sizeInclusionFlag
     */
    uint8_t getSizeInclusionFlag() const;
    /**
     * @brief Get Index File Name Getter
     * @returns indexFileName
     */
    const std::string& getIndexFileName() const;
    /**
     * @brief Record Count Getter
     * @returns recordCount
     */
    uint32_t getRecordCount() const;
    /**
     * @brief Field Count Getter
     * @returns fieldCount
     */
    uint16_t getFieldCount() const;
    /**
     * @brief Fields Getter
     * @returns fields
     */
    const std::vector<FieldDef>& getFields() const; 
    /**
     * @brief Primary Key Field Getter
     * @returns primaryKeyField
     */
    uint8_t getPrimaryKeyField() const;
    /**
     * @brief Has Valid Index File Getter
     * @returns hasValidIndexFile
     */
    uint8_t getHasValidIndexFile() const;

    /**
     * @brief File Structure Type Setter
     * @details sets fileStructureType[4] to type
     * @param Type new File structure type
     */
    void setFileStructureType(const char* type);
    /**
     * @brief Version Setter
     * @details sets version to ver
     * @param ver new version
     */
    void setVersion(uint16_t ver);
    /**
     * @brief Header Size Setter
     * @details sets headerSize to size
     * @param size new headerSize value
     */
    void setHeaderSize(uint32_t size);
    /**
     * @brief Size Format Type Setter
     * @details sets sizeFormatType to type
     * @param type new sizeFormatType value
     */
    void setSizeFormatType(uint8_t type);
    /**
     * @brief Size Of Sizes Setter
     * @details sets sizeOfSizes to size
     * @param size new sizeOfSizes value
     */
    void setSizeOfSizes(uint32_t size);
    /**
     * @brief Size Inclusion Flag Setter
     * @details sets sizeInclusionFlag to flag
     * @param flag new sizeInclusionFlag value
     */
    void setSizeInclusionFlag(uint8_t flag);
    /**
     * @brief Index File Name Setter
     * @details sets indexFileName to filename
     * @param filename new indexFileName value
     */
    void setIndexFileName(const std::string& filename);
    /**
     * @brief Record Count Setter
     * @details sets recordCount to count
     * @param count new recordCount value
     */
    void setRecordCount(uint32_t count);
    /**
     * @brief Field Count Setter
     * @details sets fieldCount to count
     * @param count new fieldCount value
     */
    void setFieldCount(uint16_t count);
    /**
     * @brief Field Setter
     * @details sets fields to fieldDefs
     * @param fieldDefs new fields value
     */
    void setFields(const std::vector<FieldDef>& fieldDefs);
    /**
     * @brief Primary Key Field Setter
     * @details sets primaryKeyField to field
     * @param field new primaryKeyField value
     */
    void setPrimaryKeyField(uint8_t field);

    /**
     * @brief Adds field to header record
     * @details pushs back fields vector with the new field and updates header size
     * @param field new field to be added
     */
    void addField(const FieldDef& field);
    /**
     * @brief Has Valid Index File Setter
     * @details sets hasValidIndexFile to hasValid
     * @param hasValid new hasValidIndexFile value
     */
    void setHasValidIndexFile(uint8_t hasValid);

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
    uint8_t hasValidIndexFile;
};

#endif