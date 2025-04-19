#ifndef WAVELENGTH_H
#define WAVELENGTH_H

// Wavelength class to calculate wavelength based on given frequency
class Wavelength {
public:
    Wavelength(double value);
    double getWavelength() const;

private:
    double value;
};

#endif
