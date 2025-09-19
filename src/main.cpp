#include "utils.h"

namespace antennacalc {

/* Colors */
const std::string RESET = "\033[0m";
const std::string BLACK = "\033[30m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string GRAY = "\033[90m";
const std::string ORANGE = "\033[38;5;208m";  /* 256 color */
const std::string AMBER = "\033[38;5;214m";   /* Approx */
const std::string FLASH = "\033[5m";
const std::string INVERSE = "\033[7m";
const std::string BG_RED = "\033[41m";  /* Example bg */

/* Bands */
const std::map<std::string, double> shortwave_centers = {
    {"120m", (2.3 + 2.495) / 2},
    {"90m", (3.2 + 3.4) / 2},
    {"75m", (3.9 + 4.0) / 2},
    {"60m", (4.75 + 5.06) / 2},
    {"49m", (5.9 + 6.2) / 2},
    {"41m", (7.2 + 7.45) / 2},
    {"31m", (9.4 + 9.9) / 2},
    {"25m", (11.6 + 12.1) / 2},
    {"22m", (13.57 + 13.87) / 2},
    {"19m", (15.1 + 15.8) / 2},
    {"16m", (17.48 + 17.9) / 2},
    {"15m", (18.9 + 19.02) / 2},
    {"13m", (21.45 + 21.85) / 2},
    {"11m", (25.67 + 26.1) / 2}
};

const std::map<std::string, double> amateur_centers = {
    {"160m", (1.8 + 2.0) / 2},
    {"80m", (3.5 + 4.0) / 2},
    {"75m", (3.75 + 4.0) / 2},
    {"60m", (5.3515 + 5.3665) / 2},
    {"40m", (7.0 + 7.3) / 2},
    {"30m", (10.1 + 10.15) / 2},
    {"20m", (14.0 + 14.35) / 2},
    {"17m", (18.068 + 18.168) / 2},
    {"15m", (21.0 + 21.45) / 2},
    {"12m", (24.89 + 24.99) / 2},
    {"10m", (28.0 + 29.7) / 2}
};

/* Draw box */
void drawBox(int width, int height, const std::string& title = "") {
    std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
    if (!title.empty()) {
        std::cout << "| " << title << std::string(width - title.size() - 3, ' ') << "|" << std::endl;
        std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
    }
    for (int i = 0; i < height - 2; ++i) {
        std::cout << "|" << std::string(width - 2, ' ') << "|" << std::endl;
    }
    std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
}

/* Calculate antenna length */
std::pair<double, double> calculateLength(const AntennaParams& params) {
    double vf = 0.95;  // Velocity factor
    double base_len_m = (params.wave == HALF_WAVE ? 300.0 / params.freq_mhz / 2.0 : 300.0 / params.freq_mhz / 4.0) * vf;
    double adjusted_len_m = base_len_m;

    switch (params.type) {
        case YAGI_UDA:
            // Simple 3-element: driven, reflector, director
            // Return driven, reflector
            return {base_len_m, base_len_m * 1.05};  // Director would be 0.95 * base
        case LOOP:
            adjusted_len_m = 306.0 / params.freq_mhz;  // Circumference
            break;
        case INVERTED_V:
            // Assume 90 deg angle
            adjusted_len_m /= std::sin(PI / 4);  // Per leg
            break;
        case FOLDED_DIPOLE:
            // Length same, impedance adjusted
            break;
        default:
            break;
    }

    // Balun doesn't affect length
    (void)params.balun_ratio;
    (void)params.balance;
    (void)params.impedance;

    double len_feet = adjusted_len_m * 3.28084;
    return {adjusted_len_m, len_feet};
}

/* Show menu */
int showMenu(const std::vector<std::string>& options, Utils& utils) {
    int selected = 0;
    int width = 40;
    while (true) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        drawBox(width, options.size() + 2, "Menu");
        for (size_t i = 0; i < options.size(); ++i) {
            std::string sel = (i == selected) ? "=> " : "   ";
            std::string highlight = (i == selected && utils.colorsEnabled()) ? INVERSE : "";
            std::cout << "|" << sel << highlight << options[i] << RESET << std::string(width - options[i].size() - 5, ' ') << "|" << std::endl;
        }
        std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;

        int key = utils.getKey();
        if (key == UP) selected = (selected > 0) ? selected - 1 : options.size() - 1;
        else if (key == DOWN) selected = (selected < static_cast<int>(options.size()) - 1) ? selected + 1 : 0;
        else if (key == ENTER) return selected;
    }
    return -1;
}

/* Login/Register */
bool login(Utils& utils) {
    std::string user, pass;
    bool register_mode = false;

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    drawBox(40, 5, "Login / Register");
    std::cout << "| 1. Login" << std::endl;
    std::cout << "| 2. Register" << std::endl;
    std::cout << "+-------------------------------------+" << std::endl;
    std::string choice;
    std::getline(std::cin, choice);
    if (choice == "2") register_mode = true;

    std::cout << "Username: ";
    std::getline(std::cin, user);
    std::cout << "Password: ";
    std::getline(std::cin, pass);

    std::string hash = utils.sha256(pass);
    std::filesystem::create_directory("data");
    std::string users_file = "data/users.dat";

    if (register_mode) {
        std::ofstream file(users_file, std::ios::app);
        if (file) {
            file << user << ":" << hash << std::endl;
            file.close();
            utils.log("User registered: " + user);
            return true;
        }
        utils.log("Registration failed", true);
        return false;
    } else {
        std::ifstream file(users_file);
        if (file) {
            std::string line;
            while (std::getline(file, line)) {
                size_t colon = line.find(':');
                if (colon != std::string::npos && line.substr(0, colon) == user && line.substr(colon + 1) == hash) {
                    file.close();
                    utils.log("User logged in: " + user);
                    return true;
                }
            }
            file.close();
        }
        utils.log("Login failed", true);
        std::cout << RED << "Invalid credentials" << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return false;
    }
}

/* Settings menu */
void settings(Utils& utils) {
    std::vector<std::string> opts = {"Toggle Colors (current: " + utils.getConfigValue("colors") + ")", "Back"};
    int sel = showMenu(opts, utils);
    if (sel == 0) {
        std::string new_val = utils.getConfigValue("colors") == "on" ? "off" : "on";
        utils.setConfigValue("colors", new_val);
        utils.saveConfig("data/config.cfg");
    }
}

/* Help */
void help() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    drawBox(60, 10, "Help");
    std::cout << "| Use arrows/WASD/IJKL to navigate menus." << std::endl;
    std::cout << "| Enter to select." << std::endl;
    std::cout << "| Calculations use center freq for bands." << std::endl;
    std::cout << "| Lengths in meters/feet." << std::endl;
    std::cout << "| Press Enter to return..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

/* Calculate screen */
void calculate(Utils& utils) {
    // Select band type
    std::vector<std::string> band_types = {"Shortwave", "Amateur", "Custom Freq", "Back"};
    int bt_sel = showMenu(band_types, utils);
    if (bt_sel == 3) return;

    double freq = 0.0;
    if (bt_sel == 2) {
        std::cout << "Enter freq (MHz): ";
        std::string input;
        std::getline(std::cin, input);
        try {
            freq = std::stod(input);
        } catch (const std::invalid_argument&) {
            utils.log("Invalid freq", true);
            return;
        }
    } else {
        const auto& bands = (bt_sel == 0) ? shortwave_centers : amateur_centers;
        std::vector<std::string> band_names;
        for (const auto& p : bands) band_names.push_back(p.first);
        band_names.push_back("Back");
        int b_sel = showMenu(band_names, utils);
        if (b_sel == band_names.size() - 1) return;
        freq = bands.at(band_names[b_sel]);
    }

    if (freq < 1.6 || freq > 30.0) {
        std::cout << RED << "Freq out of range" << RESET << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    // Type
    std::vector<std::string> types = {"Dipole", "Yagi-Uda", "Loop", "Vertical", "Inverted V", "Folded Dipole", "Back"};
    int t_sel = showMenu(types, utils);
    if (t_sel == 6) return;
    AntennaType atype = static_cast<AntennaType>(t_sel);

    // Wave
    std::vector<std::string> waves = {"Half Wave", "Quarter Wave", "Back"};
    int w_sel = showMenu(waves, utils);
    if (w_sel == 2) return;
    WaveType wtype = static_cast<WaveType>(w_sel);

    // Balance
    std::vector<std::string> balances = {"Balanced", "Unbalanced", "Back"};
    int bal_sel = showMenu(balances, utils);
    if (bal_sel == 2) return;
    BalanceType btype = static_cast<BalanceType>(bal_sel);

    // Balun ratio
    std::cout << "Balun ratio (e.g. 1, 4, custom): ";
    std::string br_str;
    std::getline(std::cin, br_str);
    double br = 1.0;
    try {
        br = std::stod(br_str);
    } catch (...) {}

    AntennaParams params = {freq, atype, wtype, btype, br, 50.0};

    // Simulate progress
    for (int i = 0; i <= 100; ++i) {
        utils.showProgress(i, 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    auto [len_m, len_ft] = calculateLength(params);
    std::cout << GREEN << "Length: " << std::fixed << std::setprecision(2) << len_m << " m / " << len_ft << " ft" << RESET << std::endl;
    if (atype == YAGI_UDA) {
        std::cout << "Reflector: " << len_m * 1.05 << " m" << std::endl;
        std::cout << "Director: " << len_m * 0.95 << " m" << std::endl;
    }

    utils.log("Calculation: freq=" + std::to_string(freq) + ", type=" + types[t_sel]);
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.get();
}

/* Main menu */
void mainMenu(Utils& utils) {
    std::vector<std::string> opts = {"Calculate Antenna", "Settings", "Help", "Exit"};
    while (true) {
        int sel = showMenu(opts, utils);
        switch (sel) {
            case 0: calculate(utils); break;
            case 1: settings(utils); break;
            case 2: help(); break;
            case 3: return;
        }
    }
}

int main(int argc, char** argv) {
    Utils utils;

    // Command line
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--version") {
            std::cout << "0.0.1" << std::endl;
            return 0;
        } else if (arg == "--help") {
            std::cout << "Usage: antennacalc [--version] [--help]" << std::endl;
            return 0;
        }
    }

    // Check size
    auto [cols, rows] = utils.getTerminalSize();
    if (cols < 80 || rows < 25) {
        std::cerr << "Terminal too small (min 80x25)" << std::endl;
        return 1;
    }

    // Welcome
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    std::cout << GREEN << "AntennaCalc" << RESET << std::endl;
    std::cout << "Version 0.0.1" << std::endl;
    std::cout << "Copyright 2025" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Login
    if (!login(utils)) {
        return 1;
    }

    // Main menu
    mainMenu(utils);

    return 0;
}

}  // namespace antennacalc
