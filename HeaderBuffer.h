#ifndef HEADER_BUFFER_H
#define HEADER_BUFFER_H

#include "HeaderRecord.h"
#include <string>

class HeaderBuffer 
{
public:
    HeaderBuffer();
    
    bool readHeader(const std::string& filename, HeaderRecord& header);
    bool writeHeader(const std::string& filename, const HeaderRecord& header);
    
    bool hasError() const;
    std::string getLastError() const;
    
private:
    bool errorState;
    std::string lastError;
    
    void setError(const std::string& message);
};

#endif