#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iosfwd>   // std::ostream
#include "ZipCodeRecord.h"
#include "CSVBuffer.h"

/**
 * @file DataManager.h
 * @brief Orchestrates loading ZIP data and producing per-state extremes.
 *
 * Output table columns (in this order):
 *   State, EasternmostZIP, WesternmostZIP, NorthernmostZIP, SouthernmostZIP
 * Rows are sorted alphabetically by 2-letter state ID.
 */
class DataManager {
public:
    struct Extremes {
        ZipCodeRecord easternmost;  // least longitude
        ZipCodeRecord westernmost;  // greatest longitude
        ZipCodeRecord northernmost; // greatest latitude
        ZipCodeRecord southernmost; // least latitude
        bool initialized = false;
    };

    DataManager() = default;

    /**
     * @brief Load records from a CSV using CSVBuffer.
     * @param csvPath path to CSV file
     * @return number of records loaded
     * @throws std::runtime_error if file open fails or zero records loaded
     */
    std::size_t loadFromCsv(const std::string& csvPath);

    /**
     * @brief Compute per-state extremes (E/W/N/S) from loaded records.
     */
    void computeExtremes();

    /**
     * @brief Print header + per-state rows to the provided stream.
     * @param os output stream (e.g., std::cout)
     */
    void printTable(std::ostream& os) const;

    /**
     * @brief Canonical signature for equality checking across inputs.
     * @details Returns a deterministic string of "STATE:E|W|N|S" lines
     *          sorted by state; useful to verify identical results across
     *          differently sorted CSV inputs.
     */
    std::string signature() const;

    /**
     * @brief Convenience: load, compute, signature (single CSV).
     */
    static std::string signatureFromCsv(const std::string& csvPath);

    /**
     * @brief Verify identical results when using two differently sorted CSVs.
     * @return true if the signatures match; false otherwise
     */
    static bool verifyIdenticalResults(const std::string& csvA,
                                       const std::string& csvB);

private:
    std::vector<ZipCodeRecord> records_;
    std::unordered_map<std::string, Extremes> stateExtremes_;

    static void updateExtremes(Extremes& ex, const ZipCodeRecord& rec);
};
#endif