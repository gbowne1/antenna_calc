/*
 * This file is part of antenna_calc.
 *
 * <project name> is free software: you can redistribute it and/or modify
 * it under the terms of the <license name> as published by
 * the <license organization>, either version <license version> of the License, or
 * (at your option) any later version.
 *
 * <project name> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * <license name> for more details.
 *
 * You should have received a copy of the LICENSE or LICENSE.md
 * along with antenna_calc.  If not, see <license URL>.
*/

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

#include "../include/Antenna.h"
#include "../include/Spectrum.h"
#include "../include/Band.h"
#include "../include/Frequency.h"
#include "../include/Wavelength.h"

Spectrum::Spectrum() {}

std::vector<std::pair<double, double>> Spectrum::getFrequencyRanges() const {
    return { {1.0e6, 30.0e6}, {30.0e6, 300.0e6} }; // Example ranges
}

std::string Spectrum::getBandName(const std::pair<double, double>& range) const {
    // Example logic based on the range
    if (range.first >= 1000000000.0 && range.second <= 2000000000.0) {
        return "L Band";  // Just an example, adjust the ranges and band names as necessary
    }
    return "Unknown Band";
}