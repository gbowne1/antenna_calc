#include "../include/Wavelength.h"
#include <cmath>

// Constructor
Wavelength::Wavelength(double value) : value(value) {}

double Wavelength::getWavelength() const
{
    // Wavelength in meters: c = λf => λ = c / f (where c = speed of light in m/s)
    const double c = 299792458.0; // Speed of light in meters per second
    return c / (value * 1.0e6);   // Convert MHz to Hz
}
