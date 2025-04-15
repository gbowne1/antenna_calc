#ifndef ANTENNA_H
#define ANTENNA_H

#include <string>

// Antenna class for calculating wave lengths and validating frequency ranges
class Antenna {
public:
    // Constructor
    Antenna(double frequency, const std::string& bandType);

    // Getters for antenna wave lengths
    double getHalfWaveLength() const;
    double getQuarterWaveLength() const;
    double getLength() const;

    // Frequency validation based on band type
    bool isValidFrequency() const;

    // Getters and setters for frequency and band type
    double getFrequency() const { return frequency; }
    const std::string& getBandType() const { return bandType; }
    void setBandType(const std::string& bandType);

private:
    double frequency;
    std::string bandType;

    // Helper method to validate band type
    void validateInputs() const;
};

#endif
