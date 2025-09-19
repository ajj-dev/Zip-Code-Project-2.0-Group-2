#include "DataManager.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <map>      // for sorted output by key

// -------- Helper: update extremes for a single state --------
void DataManager::updateExtremesForState(Extremes& ex, const ZipCodeRecord& rec) {
    if (!rec.isValid()) return;

    const double lat = rec.getLatitude();
    const double lon = rec.getLongitude();

    if (!ex.initialized) {
        ex.easternmost = rec; // least lon
        ex.westernmost = rec; // greatest lon
        ex.northernmost = rec; // greatest lat
        ex.southernmost = rec; // least lat
        ex.initialized = true;
        return;
    }

    if (lon < ex.easternmost.getLongitude())  ex.easternmost = rec; // min lon
    if (lon > ex.westernmost.getLongitude())  ex.westernmost = rec; // max lon
    if (lat > ex.northernmost.getLatitude())  ex.northernmost = rec; // max lat
    if (lat < ex.southernmost.getLatitude())  ex.southernmost = rec; // min lat
}

// -------- Public API --------
std::size_t DataManager::loadFromCsv(const std::string& csvPath) {
    records_.clear();

    CSVBuffer buffer(csvPath);
    if (!buffer.good()) {
        std::ostringstream oss;
        oss << "Failed to open CSV: " << csvPath << " (" << buffer.lastError() << ")";
        throw std::runtime_error(oss.str());
    }

    ZipCodeRecord rec;
    std::size_t count = 0;
    while (buffer.readNext(rec)) {
        if (rec.isValid()) {
            records_.push_back(rec);
            ++count;
        }
        // else: silently skip invalid rows, or log via buffer.lastError() if desired.
    }

    if (count == 0) {
        throw std::runtime_error("No valid records loaded from: " + csvPath);
    }
    return count;
}

void DataManager::setRecords(std::vector<ZipCodeRecord> records) {
    records_ = std::move(records);
}

void DataManager::computeExtremes() {
    stateExtremes_.clear();
    for (const auto& rec : records_) {
        if (!rec.isValid()) continue;
        const std::string state = rec.getStateId();
        if (state.size() != 2) continue; // enforce two-letter state IDs
        Extremes& ex = stateExtremes_[state];
        updateExtremesForState(ex, rec);
    }
}

void DataManager::printTable(std::ostream& os) const {
    // Header
    os << "State, EasternmostZIP, WesternmostZIP, NorthernmostZIP, SouthernmostZIP\n";

    // Sort states alphabetically
    std::map<std::string, Extremes> sorted(stateExtremes_.begin(), stateExtremes_.end());
    for (const auto& [state, ex] : sorted) {
        if (!ex.initialized) continue;

        os << state << ", "
           << ex.easternmost.getZipCode()   << ", "
           << ex.westernmost.getZipCode()   << ", "
           << ex.northernmost.getZipCode()  << ", "
           << ex.southernmost.getZipCode()  << "\n";
    }
}

std::string DataManager::signature() const {
    // Create a canonical string of "STATE:E|W|N|S" lines sorted by state.
    std::ostringstream oss;
    std::map<std::string, Extremes> sorted(stateExtremes_.begin(), stateExtremes_.end());
    for (const auto& [state, ex] : sorted) {
        if (!ex.initialized) continue;
        oss << state << ":"
            << ex.easternmost.getZipCode()  << "|"
            << ex.westernmost.getZipCode()  << "|"
            << ex.northernmost.getZipCode() << "|"
            << ex.southernmost.getZipCode() << "\n";
    }
    return oss.str();
}

std::string DataManager::signatureFromCsv(const std::string& csvPath) {
    DataManager mgr;
    mgr.loadFromCsv(csvPath);
    mgr.computeExtremes();
    return mgr.signature();
}

bool DataManager::verifyIdenticalResults(const std::string& csvPathA,
                                         const std::string& csvPathB) {
    const std::string sigA = signatureFromCsv(csvPathA);
    const std::string sigB = signatureFromCsv(csvPathB);
    return sigA == sigB;
}
