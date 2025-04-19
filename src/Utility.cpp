#include "../include/Utility.h"
#include <cstdlib>
#include <string>

namespace Utility
{
    double parseFrequencyArg(int argc, char *argv[])
    {
        if (argc > 1)
        {
            return std::stod(argv[1]); // Assume MHz
        }
        return 14.2; // Default
    }

    double getFrequencyInMHz(double frequency)
    {
        return frequency; // Already in MHz
    }

    double getFrequencyInGHz(double frequency)
    {
        return frequency / 1000.0; // Convert MHz to GHz
    }

    double getFrequencyInKHz(double frequency)
    {
        return frequency * 1000.0; // Convert MHz to kHz
    }

    double getFrequencyInHz(double frequency)
    {
        return frequency * 1.0e6; // Convert MHz to Hz
    }
}
