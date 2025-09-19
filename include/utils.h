#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <ctime>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

#ifdef HAS_GLOG
#include <glog/logging.h>
#endif

#include <gtest/gtest.h>  /* For tests, but include here if needed */

namespace antennacalc {

/* Utility class for common functions */
class Utils {
public:
    Utils();
    ~Utils();

    /* Getters/Setters */
    std::string getConfigValue(const std::string& key) const;
    void setConfigValue(const std::string& key, const std::string& value);

    /* SHA256 hash */
    std::string sha256(const std::string& input);

    /* Load/Save config (.cfg INI style) */
    bool loadConfig(const std::string& filename);
    bool saveConfig(const std::string& filename);

    /* Log message with timestamp */
    void log(const std::string& message, bool error = false);

    /* Parse INI line */
    void parseIniLine(const std::string& line);

    /* Trim string */
    std::string trim(const std::string& str);

    /* Progress bar */
    void showProgress(int progress, int total);

    /* Get terminal size */
    std::pair<int, int> getTerminalSize();

    /* Get key input (arrows, etc.) */
    int getKey();

    /* Colors on? */
    bool colorsEnabled() const;

private:
    std::map<std::string, std::string> config_;
    std::mutex mutex_;
    std::ofstream log_file_;

    /* SHA256 internal */
    class SHA256Impl;  /* Forward */
    std::unique_ptr<SHA256Impl> sha_impl_;
};

/* Enums */
enum KeyCode { UP = 1000, DOWN, LEFT, RIGHT, ENTER, ESC };
enum AntennaType { DIPOLE, YAGI_UDA, LOOP, VERTICAL, INVERTED_V, FOLDED_DIPOLE };
enum WaveType { HALF_WAVE, QUARTER_WAVE };
enum BalanceType { BALANCED, UNBALANCED };

/* Struct for menu item */
struct MenuItem {
    std::string name;
    int id;
};

/* Struct for antenna params */
struct AntennaParams {
    double freq_mhz;
    AntennaType type;
    WaveType wave;
    BalanceType balance;
    double balun_ratio;
    double impedance;  /* 50 default */
};

}  // namespace antennacalc
