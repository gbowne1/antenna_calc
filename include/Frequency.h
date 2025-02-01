#ifndef FREQUENCY_H
#define FREQUENCY_H

class Frequency {
public:
    Frequency(double freq);
    double getFrequency() const;
private:
    double frequency;
};

#endif