#ifndef ANTENNA_H
#define ANTENNA_H

// Antenna.h
class Antenna {
public:

    bool isValidFrequency() const;
    Antenna(double frequency, const std::string &bandType);
    double getHalfWaveLength() const;
    double getQuarterWaveLength() const;
    bool isValidFrequency() const;
    double frequency;
    const std::string& getBandType() const;
    void setBandType(const std::string& bandType);

private:
    std::string bandType;
    double frequency;
};

#endif