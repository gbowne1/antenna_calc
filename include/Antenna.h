#ifndef ANTENNA_H
#define ANTENNA_H

// Antenna.h
class Antenna {
public:
    Antenna(double frequency);
    double getLength();
private:
    double frequency;
};

#endif