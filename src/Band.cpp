#include "../include/Band.h"

Band::Band(const std::string &name) : name(name) {}

std::pair<double, double> Band::getFrequencyRange() const
{
    // Return frequency range for the band (adjust accordingly)
    if (name == "HF")
    {
        return {1.8e6, 30.0e6}; // HF range: 1.8 MHz to 30 MHz
    }
    else
    {
        return {0.0, 0.0}; // Unknown band
    }
}

std::string Band::getName() const
{
    return name;
}
