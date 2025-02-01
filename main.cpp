/*
 * This file is part of antenna_calc.
 *
 * antenna_calc is free software: you can redistribute it and/or modify
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

#include "include/Antenna.h"
#include "include/Spectrum.h"
#include "include/Band.h"
#include "include/Frequency.h"
#include "include/Wavelength.h"

int main()
{
	double frequency = 1000000000.0; // Frequency
    Antenna antenna(frequency); // Create an object of the Antenna class with a frequency of 1 GHz
    double antennaLength = antenna.getLength(); // Get the antenna length
    std::cout << "Antenna length: " << antennaLength << " meters" << std::endl; // Print the result

    Band band("HF"); // Create an object of the Band class for the HF band
    std::pair<double, double> frequencyRange = band.getFrequencyRange(); // Get the frequency range
    std::cout << "Frequency range for " << band.getName() << " band: " << frequencyRange.first << "-" << frequencyRange.second << " Hz" << std::endl; // Print the result

    Frequency frequencyObj(1000000000.0); // Create an object of the Frequency class with a frequency of 1 GHz
    double frequencyValue = frequencyObj.getFrequency(); // Get the frequency value
    std::cout << "Frequency: " << frequencyValue << " Hz" << std::endl; // Print the result

    Wavelength wavelength(0.3); // Create an object of the Wavelength class with a wavelength of 0.3 meters
    double wavelengthValue = wavelength.getWavelength(); // Get the wavelength value
    std::cout << "Wavelength: " << wavelengthValue << " meters" << std::endl; // Print the result

    Spectrum spectrum; // Create an object of the Spectrum class
    std::vector<std::pair<double, double>> frequencyRanges = spectrum.getFrequencyRanges(); // Get the frequency ranges
    for (auto range : frequencyRanges) {
        std::cout << "Frequency range for " << spectrum.getBandName(range) << " band: " << range.first << "-" << range.second << " Hz" << std::endl; // Print the result
    }

    return 0;
}