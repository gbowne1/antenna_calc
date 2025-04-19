#ifndef UTILITY_H
#define UTILITY_H

#include <string>

namespace Utility {
    double parseFrequencyArg(int argc, char *argv[]);
    double getFrequencyInMHz(double frequency);
    double getFrequencyInGHz(double frequency);
    double getFrequencyInKHz(double frequency);
    double getFrequencyInHz(double frequency);
}

#endif
