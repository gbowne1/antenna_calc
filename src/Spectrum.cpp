#include "../include/Spectrum.h"

#include <algorithm> // For std::remove_if
#include <cctype>    // For std::isdigit
#include <cstring>   // For std::strtok
#include <iostream>
#include <stdexcept> // For std::invalid_argument
#include <string>
#include <utility>
#include <vector>

Spectrum::Spectrum() {}

std::vector<std::pair<double, double>> Spectrum::getFrequencyRanges() const
{
    return {{1.0e6, 30.0e6}, {30.0e6, 300.0e6}}; // HF and VHF example ranges
}

std::string Spectrum::getBandName(const std::pair<double, double> &range) const
{
    if (range.first >= 1.0e6 && range.second <= 30.0e6)
    {
        return "HF Band";
    }
    else if (range.first >= 30.0e6 && range.second <= 300.0e6)
    {
        return "VHF Band";
    }
    return "Unknown Band";
}
