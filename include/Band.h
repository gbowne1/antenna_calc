#ifndef BAND_H
#define BAND_H

#include <string>
#include <utility>

// Band class for managing band names and frequency ranges
class Band {
public:
    Band(const std::string& name);
    std::pair<double, double> getFrequencyRange() const;
    std::string getName() const;

private:
    std::string name;
};

#endif
