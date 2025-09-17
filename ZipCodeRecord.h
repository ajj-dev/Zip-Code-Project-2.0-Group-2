#ifndef ZIP_CODE_RECORD_H
#define ZIP_CODE_RECORD_H

#include <string>
#include <iostream>

/**
 * @file ZipCodeRecord.h
 * @author Andrew Johnson
 * @brief ZipCodeRecord class for storing individual zip code information
 * @version 0.1
 * @date 2025-09-11
 */

/**
 * @class ZipCodeRecord
 * @brief Represents a single zip code record with geographic data
 * @details Stores zip code, coordinates, and location information.
 */
class ZipCodeRecord
{
public:
    /**
     * @brief Default constructor
     * @details Initializes all fields to default values
     */
    ZipCodeRecord();
    
    /**
     * @brief Parameterized constructor
     * @param inZipCode [IN] 5-digit zip code
     * @param inLatitude [IN] Latitude coordinate (-90 to 90)
     * @param inLongitude [IN] Longitude coordinate (-180 to 180)
     * @param inLocationName [IN] Place name
     * @param inState [IN] Two-character state code
     * @param inCounty [IN] County name
     * @pre All parameters must be valid (zip code > 0, coordinates in range)
     * @post Object is initialized with provided values
     */
    ZipCodeRecord(const int inZipCode, const double inLatitude, const double inLongitude, 
                  const std::string& inLocationName, const std::string& inState, 
                  const std::string& inCounty);
    
    /**
     * @brief Copy constructor
     * @param other [IN] ZipCodeRecord to copy
     */
    ZipCodeRecord(const ZipCodeRecord& other);
    
    /**
     * @brief Assignment operator
     * @param other [IN] ZipCodeRecord to assign from
     * @return Reference to this object
     */
    ZipCodeRecord& operator=(const ZipCodeRecord& other);
    
    /**
     * @brief Destructor
     */
    ~ZipCodeRecord();

    // Setters
    /**
     * @brief Set zip code value
     * @param inZipCode [IN] 5-digit zip code
     * @return true if valid zip code, false otherwise
     * @pre inZipCode must be positive
     * @post zipCode is updated if valid
     */
    bool setZipCode(const int inZipCode);
    bool setLatitude(const double inLatitude);
    bool setLongitude(const double inLongitude);
    bool setLocationName(const std::string& inLocationName);
    bool setState(const std::string& inState);
    bool setCounty(const std::string& inCounty);

    // Getters
    int getZipCode() const;
    double getLatitude() const;
    double getLongitude() const;
    std::string getLocationName() const;
    const char* getState() const;
    std::string getCounty() const;
    
    /**
     * @brief Check if this record is further north than another
     * @param other [IN] Record to compare against
     * @return true if this record has higher latitude
     */
    bool isNorthOf(const ZipCodeRecord& other) const;
    
    /**
     * @brief Check if this record is further east than another
     * @param other [IN] Record to compare against
     * @return true if this record has smaller longitude (more eastward)
     */
    bool isEastOf(const ZipCodeRecord& other) const;
    
    /**
     * @brief Check if this record is further south than another
     * @param other [IN] Record to compare against
     * @return true if this record has lower latitude
     */
    bool isSouthOf(const ZipCodeRecord& other) const;
    
    /**
     * @brief Check if this record is further west than another
     * @param other [IN] Record to compare against
     * @return true if this record has larger longitude (more westward)
     */
    bool isWestOf(const ZipCodeRecord& other) const;
    
    /**
     * @brief Output stream operator
     * @param outputStream [IN,OUT] Output stream
     * @param record [IN] Record to output
     * @return Reference to output stream
     */
    friend std::ostream& operator<<(std::ostream& outputStream, const ZipCodeRecord& record);

private:
    int zipCode; // 5-digit zip code
    double latitude; // Latitude coordinate
    double longitude; // Longitude coordinate  
    std::string locationName; // Town name
    char state[3]; // Two-character state code + null terminator
    std::string county; // County name
    
    /**
     * @brief Validate latitude range
     * @param inLatitude [IN] Latitude to validate
     * @return true if latitude is between -90 and 90
     */
    bool isValidLatitude(const double inLatitude) const;
    
    /**
     * @brief Validate longitude range
     * @param inLongitude [IN] Longitude to validate
     * @return true if longitude is between -180 and 180
     */
    bool isValidLongitude(const double inLongitude) const;
};

#endif // ZIP_CODE_RECORD_H