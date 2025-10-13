# ZipCode Group Project 2.0

## Part 1 Requirements

### 1. CSV File Creation & Testing: Done
- Create CSV from original XLSX file: Done
- Create CSV from row-randomized XLSX file (remove column G first): Done
- Verify Project 1.0 works with both CSV files (sequential processing): Done
- Confirm identical results between original and randomized data: Done

### 2. Binary File Format Development:
- HeaderRecord class - Complete with serialization/deserialization: Done
- ZipCodeRecord serialization - Add serialize()/deserialize() methods: Done
- CSV to binary converter - Tool to convert CSV files to length-indicated format (.zcd files): Done
- HeaderBuffer class - Buffer specifically for reading/writing header records: Done

### 3. Buffer Class Modifications:
- Modify existing CSVBuffer or create new buffer for length-indicated files: Done
- Ensure buffer can read and unpack ZipCodeRecord from Length Indicated Format: Done
- Handle variable-length records with size prefixes: Done

### 4. Integration & Testing:
- Convert both CSV files to .zcd format: Done
- Generate demonstration scripts showing equivalency: Done

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




