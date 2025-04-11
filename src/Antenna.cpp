#include "../include/Antenna.h"
#include <cmath>
#include <stdexcept>
#include <string>

Antenna::Antenna(double frequency, const std::string &bandType) : frequency(frequency), bandType(bandType)
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

double Antenna::getHalfWaveLength() const
{
    return 468.0 / frequency; // Length in feet
}

double Antenna::getQuarterWaveLength() const
{
    return 234.0 / frequency; // Length in feet
}

bool Antenna::isValidFrequency() const
{
    if (bandType == "shortwave")
    {
        return frequency >= 2.5 && frequency <= 30.0; // Shortwave bands 120m to 11m
    }
    else if (bandType == "amateur")
    {
        return frequency >= 1.8 && frequency <= 30.0; // Amateur radio bands 160m to 10m
    }
    return false;
}
