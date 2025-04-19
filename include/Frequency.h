#ifndef FREQUENCY_H
#define FREQUENCY_H

// Frequency class to manage frequency data
class Frequency {
public:
    Frequency(double freq);
    double getFrequency() const;

private:
    double frequency;
};

#endif
