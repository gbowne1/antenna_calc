#ifndef WAVELENGTH_H
#define WAVELENGTH_H

class Wavelength {
public:
    Wavelength(double value);
    double getWavelength() const;
private:
    double value;
};

#endif