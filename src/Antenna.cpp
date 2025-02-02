/*
 * This file is part of antenna_calc.
 *
 * <project name> is free software: you can redistribute it and/or modify
 * it under the terms of the <license name> as published by
 * the <license organization>, either version <license version> of the License, or
 * (at your option) any later version.
 *
 * <project name> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * <license name> for more details.
 *
 * You should have received a copy of the LICENSE or LICENSE.md
 * along with antenna_calc.  If not, see antenna_calc/LICENSE.
*/

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

#include "../include/Antenna.h"
#include "../include/Spectrum.h"
#include "../include/Band.h"
#include "../include/Frequency.h"
#include "../include/Wavelength.h"

Antenna::Antenna(double frequency) : frequency(frequency) {
    // Constructor implementation
}

double Antenna::getLength() {
    return 3.0; // Example length, replace with your actual formula or logic
}

