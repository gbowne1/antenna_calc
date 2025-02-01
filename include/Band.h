#ifndef BAND_H
#define BAND_H

class Band {
public:
    Band(const std::string& name);
    std::pair<double, double> getFrequencyRange() const;
    std::string getName() const;
private:
    std::string name;
};

#endif