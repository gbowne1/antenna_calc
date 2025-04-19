#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <vector>
#include <utility>
#include <string>

// Spectrum class for managing and retrieving frequency ranges for bands
class Spectrum {
public:
    Spectrum();
    std::vector<std::pair<double, double>> getFrequencyRanges() const;
    std::string getBandName(const std::pair<double, double>& range) const;
};

#endif
