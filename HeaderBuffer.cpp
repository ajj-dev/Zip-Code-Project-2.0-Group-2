#include "HeaderBuffer.h"
#include <fstream>
#include <vector>

HeaderBuffer::HeaderBuffer() : errorState(false), lastError("") {}

bool HeaderBuffer::readHeader(const std::string& filename, HeaderRecord& header)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        setError("Cannot open file: " + filename);
        return false;
    }
    
    // Read file into buffer
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<uint8_t> buffer(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    file.close();
    
    // Deserialize header
    header = HeaderRecord::deserialize(buffer.data(), fileSize);
    return true;
}

bool HeaderBuffer::writeHeader(const std::string& filename, const HeaderRecord& header)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) 
    {
        setError("Cannot create file: " + filename);
        return false;
    }
    
    auto headerData = header.serialize();
    file.write(reinterpret_cast<char*>(headerData.data()), headerData.size());
    file.close();
    
    return true;
}

bool HeaderBuffer::hasError() const 
{
    return errorState;
}

std::string HeaderBuffer::getLastError() const 
{
    return lastError;
}

void HeaderBuffer::setError(const std::string& message) 
{
    errorState = true;
    lastError = message;
}