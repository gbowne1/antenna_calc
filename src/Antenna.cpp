/*
 * This file is part of antenna_calc.
 *
 * antenna_calc is free software: you can redistribute it and/or modify
 * it under the terms of the MIT License as published by
 * the Open Source Initiative, either version 2.0 of the License, or
 * (at your option) any later version.
 *
 * antenna_calc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * MIT License for more details.
 *
 * You should have received a copy of the LICENSE or LICENSE.md
 * along with antenna_calc.  If not, see https://opensource.org/licenses/MIT.
 */

#include <string>
#include <cmath>
#include <stdexcept>
#include "../include/Antenna.h"

Antenna::Antenna(double frequency, const std::string& bandType) : frequency(frequency), bandType(bandType) {
    if (frequency <= 0.0) {
        throw std::invalid_argument("Frequency must be positive");
    }
    if (bandType != "shortwave" && bandType != "amateur") {
        throw std::invalid_argument("Band type must be either 'shortwave' or 'amateur'");
    }
}

double Antenna::getHalfWaveLength() const {
    return 468.0 / frequency; // Length in feet
}

double Antenna::getQuarterWaveLength() const {
    return 234.0 / frequency; // Length in feet
}

bool Antenna::isValidFrequency() const {
    if (bandType == "shortwave") {
        return frequency >= 2.5 && frequency <= 30.0; // Shortwave bands 120m to 11m
    } else if (bandType == "amateur") {
        return frequency >= 1.8 && frequency <= 30.0; // Amateur radio bands 160m to 10m
    }
    return false;
}
