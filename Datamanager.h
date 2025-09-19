#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iosfwd>   // for std::ostream
#include "ZipCodeRecord.h"
#include "CSVBuffer.h"

/**
 * @file DataManager.h
 * @brief Orchestrates loading ZIP code data and producing per-state extreme ZIPs.
 *
 * Responsibilities:
 * - Load records from a CSV via CSVBuffer
 * - Group by two-letter state ID
 * - For each state, compute Easternmost (min longitude), Westernmost (max longitude),
 *   Northernmost (max latitude), Southernmost (min latitude)
 * - Emit a table (header + one row per state, sorted alphabetically by state)
 * - Verify identical results when comparing two CSV sources sorted by different columns
 *
 * Usage:
 * @code
 *   DataManager mgr;
 *   mgr.loadFromCsv("zipcode_data.csv");
 *   mgr.computeExtremes();
 *   mgr.printTable(std::cout);
 * @endcode
 */
class DataManager {
public:
    /// Holds the 4 extreme records for a single state.
    struct Extremes {
        ZipCodeRecord easternmost; ///< Least longitude
        ZipCodeRecord westernmost; ///< Greatest longitude
        ZipCodeRecord northernmost; ///< Greatest latitude
        ZipCodeRecord southernmost; ///< Least latitude
        bool initialized = false;   ///< Marks whether at least one valid record has set the extremes
    };

    DataManager() = default;

    /**
     * @brief Load ZIP code records from a CSV file path.
     * @param csvPath Path to the CSV file.
     * @return Number of valid records loaded.
     * @throws std::runtime_error on unrecoverable I/O or parse errors.
     */
    std::size_t loadFromCsv(const std::string& csvPath);

    /**
     * @brief Replace internal records (useful for tests).
     */
    void setRecords(std::vector<ZipCodeRecord> records);

    /**
     * @brief Compute per-state extremes from the currently loaded records.
     */
    void computeExtremes();

    /**
     * @brief Print the required table to an output stream.
     *
     * Order:
     *  - Header row
     *  - One row per state, sorted alphabetically by state ID
     * Columns:
     *  - State, EasternmostZIP, WesternmostZIP, NorthernmostZIP, SouthernmostZIP
     *
     * @param os Output stream (e.g., std::cout).
     */
    void printTable(std::ostream& os) const;

    /**
     * @brief Build a stable, comparable signature of the current extremes map.
     * @details Generates a canonical string that is identical if and only if the
     *          extremes (state->E/W/N/S ZIPs) are identical.
     */
    std::string signature() const;

    /**
     * @brief Convenience: Load -> compute -> signature from a CSV.
     * @return canonical signature string.
     */
    static std::string signatureFromCsv(const std::string& csvPath);

    /**
     * @brief Verify identical results when using two differently-sorted CSV inputs.
     * @return true if signatures match; false otherwise.
     */
    static bool verifyIdenticalResults(const std::string& csvPathA,
                                       const std::string& csvPathB);

private:
    std::vector<ZipCodeRecord> records_;
    std::unordered_map<std::string, Extremes> stateExtremes_;

    static void updateExtremesForState(Extremes& ex, const ZipCodeRecord& rec);
};
