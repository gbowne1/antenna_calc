#include "../include/Antenna.h"
#include <cmath>
#include <stdexcept>

// Constructor with validation
Antenna::Antenna(double frequency, const std::string &bandType)
    : frequency(frequency), bandType(bandType)
{
    validateInputs(); // Validate inputs upon initialization
}

// Get half-wave length
double Antenna::getHalfWaveLength() const
{
    return 468.0 / frequency; // Length in feet
}

// Get quarter-wave length
double Antenna::getQuarterWaveLength() const
{
    return 234.0 / frequency; // Length in feet
}

// Validate whether the frequency is valid for the given band type
bool Antenna::isValidFrequency() const
{
    if (bandType == "shortwave")
    {
        return frequency >= 2.5 && frequency <= 30.0; // Shortwave bands (120m to 11m)
    }
    else if (bandType == "amateur")
    {
        return frequency >= 1.8 && frequency <= 30.0; // Amateur bands (160m to 10m)
    }
    return false;
}

// Set band type with validation
void Antenna::setBandType(const std::string &bandType)
{
    this->bandType = bandType;
    validateInputs(); // Ensure validity after modification
}

// Private method to validate inputs
void Antenna::validateInputs() const
{
    if (frequency <= 0.0)
    {
        throw std::invalid_argument("Frequency must be positive");
    }
    if (bandType != "shortwave" && bandType != "amateur")
    {
        throw std::invalid_argument("Band type must be either 'shortwave' or 'amateur'");
    }
}
