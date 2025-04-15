/*
 * This file is part of antenna_calc.
 *
 * antenna_calc is free software: you can redistribute it and/or modify
 * it under the terms of the <license name> as published by
 * the <license organization>, either version <license version> of the License, or
 * (at your option) any later version.
 *
 * antenna_calc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * <license name> for more details.
 *
 * You should have received a copy of the LICENSE or LICENSE.md
 * along with antenna_calc. If not, see <license URL>.
 */

#include "include/Antenna.h"
#include "include/Band.h"
#include "include/Frequency.h"
#include "include/Spectrum.h"
#include "include/Utility.h" // For CLI argument parsing (optional)
#include "include/Wavelength.h"
#include <iostream>
#include <string>
#include <vector>

void displayAntennaCalculations(double frequency)
{
    Antenna antenna(frequency);
    std::cout << "Antenna length: " << antenna.getLength() << " meters\n";
}

void displayBandInfo(const std::string &bandName)
{
    Band band(bandName);
    auto frequencyRange = band.getFrequencyRange();
    std::cout << "Frequency range for " << band.getName() << " band: "
              << frequencyRange.first << "-" << frequencyRange.second << " Hz\n";
}

void displaySpectrum()
{
    Spectrum spectrum;
    auto frequencyRanges = spectrum.getFrequencyRanges();
    for (const auto &range : frequencyRanges)
    {
        std::cout << "Frequency range for " << spectrum.getBandName(range)
                  << " band: " << range.first << "-" << range.second << " Hz\n";
    }
}

int main(int argc, char *argv[])
{
    std::cout << "Welcome to Antenna Calculator!\n";

    double frequency = 1000000000.0; // Default frequency: 1 GHz
    if (argc > 1)
    {
        frequency = Utility::parseFrequencyArg(argc, argv); // Optional CLI argument parsing
    }

    displayAntennaCalculations(frequency);
    displayBandInfo("HF");
    displaySpectrum();

    return 0;
}
