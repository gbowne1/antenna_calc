#include "include/Antenna.h"
#include "include/Band.h"
#include "include/Frequency.h"
#include "include/Spectrum.h"
#include "include/Wavelength.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// Function to display a menu and get user's choice
int displayMenu()
{
    std::cout << "\n====================\n";
    std::cout << "Antenna Calculator Menu\n";
    std::cout << "====================\n";
    std::cout << "1. Calculate antenna length\n";
    std::cout << "2. Display band information\n";
    std::cout << "3. Display frequency spectrum\n";
    std::cout << "4. Calculate SWR and Return Loss\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice (1-5): ";

    int choice;
    std::cin >> choice;
    return choice;
}

// Function to handle frequency input (kHz or MHz, optional comma)
double getUserFrequency()
{
    double frequency;
    std::string input = "1,000,000";

    std::cout << "Enter frequency (kHz or MHz): ";
    std::cin >> input;

    // Remove commas if present
    input.erase(std::remove(input.begin(), input.end(), ','), input.end());

    try
    {
        frequency = std::stod(input);
    }
    catch (const std::invalid_argument &)
    {
        std::cerr << "Invalid frequency input. Please try again.\n";
        return getUserFrequency(); // Recursively prompt for valid input
    }

    // Convert to MHz if in kHz
    if (input.find("k") != std::string::npos)
    {
        frequency /= 1000.0; // Convert kHz to MHz
    }
    return frequency;
}

// Function to handle band input
std::string getUserBand()
{
    std::string band;
    std::cout << "Enter the band (e.g., 20m, 80m, 40m): ";
    std::cin >> band;
    return band;
}

// Function to display antenna calculations
void displayAntennaCalculations(double frequency)
{
    Antenna antenna(frequency, "amateur");
    std::cout << "Half-wave length: " << antenna.getHalfWaveLength() << " feet\n";
    std::cout << "Quarter-wave length: " << antenna.getQuarterWaveLength() << " feet\n";
}

// Function to display band info for specific band
void displayBandInfo(const std::string &bandName)
{
    Band band(bandName);
    auto frequencyRange = band.getFrequencyRange();
    std::cout << "Frequency range for " << band.getName() << " band: "
              << frequencyRange.first << " Hz - " << frequencyRange.second << " Hz\n";
}

// Function to display all available frequency ranges in the spectrum
void displaySpectrum()
{
    Spectrum spectrum;
    auto frequencyRanges = spectrum.getFrequencyRanges();
    for (const auto &range : frequencyRanges)
    {
        std::cout << "Frequency range for " << spectrum.getBandName(range)
                  << " band: " << range.first << " Hz - " << range.second << " Hz\n";
    }
}

// Placeholder for SWR and return loss calculation
void calculateSWRAndReturnLoss(double frequency)
{
    std::cout << "\nCalculating SWR and Return Loss for frequency: " << frequency << " MHz...\n";
    // Here, you'd implement SWR and return loss calculation logic
    // Placeholder calculation
    double swr = 1.5;          // Example SWR value
    double returnLoss = -10.0; // Example return loss in dB
    std::cout << "SWR: " << swr << "\n";
    std::cout << "Return Loss: " << returnLoss << " dB\n";
}

// Main function
int main()
{
    std::cout << "Welcome to Antenna Calculator!\n";
    bool running = true;

    while (running)
    {
        int choice = displayMenu();

        switch (choice)
        {
        case 1: // Calculate antenna length
        {
            double frequency = getUserFrequency();
            displayAntennaCalculations(frequency);
            break;
        }
        case 2: // Display band information
        {
            std::string band = getUserBand();
            displayBandInfo(band);
            break;
        }
        case 3: // Display frequency spectrum
            displaySpectrum();
            break;
        case 4: // Calculate SWR and return loss
        {
            double frequency = getUserFrequency();
            calculateSWRAndReturnLoss(frequency);
            break;
        }
        case 5: // Exit
            std::cout << "Exiting program...\n";
            running = false;
            break;
        default:
            std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
