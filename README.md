# ZipCode Group Project 2.0

## Part 1 Requirements

### 1. CSV File Creation & Testing:
- Create CSV from original XLSX file:
- Create CSV from row-randomized XLSX file (remove column G first):
- Verify Project 1.0 works with both CSV files (sequential processing):
- Confirm identical results between original and randomized data:

### 2. Binary File Format Development:
- HeaderRecord class - Complete with serialization/deserialization: Done
- ZipCodeRecord serialization - Add serialize()/deserialize() methods:
- CSV to binary converter - Tool to convert CSV files to length-indicated format (.zcd files):
- LengthIndicatedBuffer class - New buffer to read/write length-indicated records:
- HeaderBuffer class - Buffer specifically for reading/writing header records:

### 3. Buffer Class Modifications:
- Modify existing CSVBuffer or create new buffer for length-indicated files:
- Ensure buffer can read and unpack ZipCodeRecord from binary format:
- Handle variable-length records with size prefixes:

### 4. Integration & Testing:
- Convert both CSV files to binary format (.zcd files):
- Repeat Project 1.0 extremes calculation using binary files:
- Verify identical results across all formats (CSV original, CSV randomized, binary original, binary randomized):
- Generate demonstration scripts showing equivalency:

## Part 2 Requirements

### 1. Primary Key Index System:
- In-memory index creation (ZIP code → file offset mapping):
- Index file writing/reading capabilities:
- Command line interface (-Z flag for ZIP code searches):
- Record lookup and display functionality:
- Handle invalid ZIP code searches with appropriate messages:

### 2. Documentation & Testing:
- Extensive Doxygen documentation:
- User guide creation:
- Design document completion:
- Test document with demonstration scripts:

- PDF generation from Doxygen:
