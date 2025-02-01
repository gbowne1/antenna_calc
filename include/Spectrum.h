#ifndef SPECTRUM_H
#define SPECTRUM_H

class Spectrum {
public:
    Spectrum();
    std::vector<std::pair<double, double>> getFrequencyRanges() const;
    std::string getBandName(const std::pair<double, double>& range) const;
};

#endif