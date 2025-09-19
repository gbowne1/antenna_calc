#include "utils.h"

namespace antennacalc {

/* Constants */
constexpr double PI = 3.14159265358979323846;  /* Already defined in macro, but constexpr */

Utils::Utils() {
    // Open log
    std::filesystem::create_directory("data");
    log_file_.open("data/log.dat", std::ios::app);
    if (!log_file_) {
        std::cerr << "Error opening log file" << std::endl;
    }
    loadConfig("data/config.cfg");
}

Utils::~Utils() {
    if (log_file_.is_open()) {
        log_file_.close();
    }
}

std::string Utils::getConfigValue(const std::string& key) const {
    auto it = config_.find(key);
    if (it != config_.end()) {
        return it->second;
    }
    return "";
}

void Utils::setConfigValue(const std::string& key, const std::string& value) {
    config_[key] = value;
}

bool Utils::loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        parseIniLine(line);
    }
    file.close();
    return true;
}

bool Utils::saveConfig(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        return false;
    }
    for (const auto& pair : config_) {
        file << pair.first << "=" << pair.second << std::endl;
    }
    file.close();
    return true;
}

void Utils::parseIniLine(const std::string& line) {
    if (line.empty() || line[0] == '[' || line[0] == ';') return;  /* Skip sections/comments */
    size_t eq_pos = line.find('=');
    if (eq_pos != std::string::npos) {
        std::string key = trim(line.substr(0, eq_pos));
        std::string value = trim(line.substr(eq_pos + 1));
        config_[key] = value;
    }
}

std::string Utils::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

void Utils::log(const std::string& message, bool error) {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    std::stringstream ss;
    ss << std::put_time(local, "%Y-%m-%d %H:%M:%S %A") << " - " << (error ? "ERROR: " : "INFO: ") << message << std::endl;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (log_file_.is_open()) {
            log_file_ << ss.str();
            log_file_.flush();
        }
#ifdef HAS_GLOG
        if (error) LOG(ERROR) << message;
        else LOG(INFO) << message;
#else
        if (error) std::cerr << ss.str();
        else std::cout << ss.str();
#endif
    }
}

void Utils::showProgress(int progress, int total) {
    if (!colorsEnabled()) {
        std::cout << progress << "/" << total << std::endl;
        return;
    }
    int bar_width = 50;
    float frac = static_cast<float>(progress) / total;
    int filled = static_cast<int>(frac * bar_width);
    std::cout << "\r[";
    for (int i = 0; i < bar_width; ++i) {
        if (i < filled) std::cout << "#";
        else std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << (frac * 100) << "%" << std::flush;
    if (progress == total) std::cout << std::endl;
}

std::pair<int, int> Utils::getTerminalSize() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return {csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return {w.ws_col, w.ws_row};
#endif
}

int Utils::getKey() {
#ifdef _WIN32
    int ch = _getch();
    if (ch == 224) {
        ch = _getch();
        if (ch == 72) return UP;
        if (ch == 80) return DOWN;
        if (ch == 75) return LEFT;
        if (ch == 77) return RIGHT;
    } else if (ch == 13) return ENTER;
    else if (ch == 27) return ESC;
    else if (tolower(ch) == 'w' || tolower(ch) == 'i') return UP;
    else if (tolower(ch) == 's' || tolower(ch) == 'k') return DOWN;
    else if (tolower(ch) == 'a' || tolower(ch) == 'j') return LEFT;
    else if (tolower(ch) == 'd' || tolower(ch) == 'l') return RIGHT;
    return ch;
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    if (ch == 27) {
        getchar();  // [
        ch = getchar();
        if (ch == 'A') ch = UP;
        else if (ch == 'B') ch = DOWN;
        else if (ch == 'D') ch = LEFT;
        else if (ch == 'C') ch = RIGHT;
    } else if (ch == '\n') ch = ENTER;
    else if (tolower(ch) == 'w' || tolower(ch) == 'i') ch = UP;
    else if (tolower(ch) == 's' || tolower(ch) == 'k') ch = DOWN;
    else if (tolower(ch) == 'a' || tolower(ch) == 'j') ch = LEFT;
    else if (tolower(ch) == 'd' || tolower(ch) == 'l') ch = RIGHT;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

bool Utils::colorsEnabled() const {
    std::string term = std::getenv("TERM") ? std::getenv("TERM") : "";
    return getConfigValue("colors") == "on" && term.find("color") != std::string::npos;
}

/* SHA256 Implementation */
/* Adapted from public domain code at http://www.zedwood.com/article/cpp-sha256-function */

class Utils::SHA256Impl {
protected:
    typedef unsigned char uint8;
    typedef unsigned int uint32;
    typedef unsigned long long uint64;

    const static uint32 k[64];

    void transform(const uint8* message, uint32 block_nb);
    uint32 tot_len_;
    uint32 len_;
    uint8 block_[128];  // 2 * 64
    uint32 h_[8];

public:
    void init();
    void update(const uint8* message, uint32 len);
    void final(uint8* digest);
    static constexpr size_t BLOCK_SIZE = 64;
    static constexpr size_t DIGEST_SIZE = 32;
};

const uint32 Utils::SHA256Impl::k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void Utils::SHA256Impl::transform(const uint8* message, uint32 block_nb) {
    uint32 w[64];
    uint32 wv[8];
    uint32 t1, t2;
    const uint8* sub_block;
    for (uint32 i = 0; i < block_nb; i++) {
        sub_block = message + (i << 6);
        for (uint32 j = 0; j < 16; j++) {
            w[j] = ((uint32)sub_block[j << 2] << 24) | ((uint32)sub_block[(j << 2) + 1] << 16) |
                   ((uint32)sub_block[(j << 2) + 2] << 8) | ((uint32)sub_block[(j << 2) + 3]);
        }
        for (uint32 j = 16; j < 64; j++) {
            uint32 s0 = (w[j - 15] >> 7 | w[j - 15] << 25) ^ (w[j - 15] >> 18 | w[j - 15] << 14) ^ (w[j - 15] >> 3);
            uint32 s1 = (w[j - 2] >> 17 | w[j - 2] << 15) ^ (w[j - 2] >> 19 | w[j - 2] << 13) ^ (w[j - 2] >> 10);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }
        for (uint32 j = 0; j < 8; j++) {
            wv[j] = h_[j];
        }
        for (uint32 j = 0; j < 64; j++) {
            uint32 s1 = (wv[4] >> 6 | wv[4] << 26) ^ (wv[4] >> 11 | wv[4] << 21) ^ (wv[4] >> 25 | wv[4] << 7);
            uint32 ch = (wv[4] & wv[5]) ^ (~wv[4] & wv[6]);
            t1 = wv[7] + s1 + ch + k[j] + w[j];
            uint32 s0 = (wv[0] >> 2 | wv[0] << 30) ^ (wv[0] >> 13 | wv[0] << 19) ^ (wv[0] >> 22 | wv[0] << 10);
            uint32 maj = (wv[0] & wv[1]) ^ (wv[0] & wv[2]) ^ (wv[1] & wv[2]);
            t2 = s0 + maj;
            wv[7] = wv[6];
            wv[6] = wv[5];
            wv[5] = wv[4];
            wv[4] = wv[3] + t1;
            wv[3] = wv[2];
            wv[2] = wv[1];
            wv[1] = wv[0];
            wv[0] = t1 + t2;
        }
        for (uint32 j = 0; j < 8; j++) {
            h_[j] += wv[j];
        }
    }
}

void Utils::SHA256Impl::init() {
    h_[0] = 0x6a09e667;
    h_[1] = 0xbb67ae85;
    h_[2] = 0x3c6ef372;
    h_[3] = 0xa54ff53a;
    h_[4] = 0x510e527f;
    h_[5] = 0x9b05688c;
    h_[6] = 0x1f83d9ab;
    h_[7] = 0x5be0cd19;
    len_ = 0;
    tot_len_ = 0;
}

void Utils::SHA256Impl::update(const uint8* message, uint32 len) {
    uint32 block_nb = len / BLOCK_SIZE;
    uint32 rem_len = len % BLOCK_SIZE;
    transform(message, block_nb);
    std::memcpy(block_ + len_, message + (len - rem_len), rem_len);
    len_ = rem_len;
    tot_len_ += len;
}

void Utils::SHA256Impl::final(uint8* digest) {
    uint32 block_nb = (1 + ((BLOCK_SIZE - 9) < (len_ % BLOCK_SIZE)));
    uint32 len_b = (tot_len_ + len_) << 3;
    uint32 pm_len = block_nb << 6;
    std::memset(block_ + len_, 0, pm_len - len_);
    block_[len_] = 0x80;
    uint32* ptr = reinterpret_cast<uint32*>(block_ + pm_len - 4);
    *ptr = (len_b >> 24) | ((len_b << 8) & 0x00ff0000) | ((len_b >> 8) & 0x0000ff00) | (len_b << 24);  // Swap bytes
    transform(block_, block_nb);
    for (int i = 0; i < 8; i++) {
        uint32* d = reinterpret_cast<uint32*>(digest + (i << 2));
        *d = (h_[i] >> 24) | ((h_[i] << 8) & 0x00ff0000) | ((h_[i] >> 8) & 0x0000ff00) | (h_[i] << 24);
    }
}

std::string Utils::sha256(const std::string& input) {
    SHA256Impl impl;
    impl.init();
    impl.update(reinterpret_cast<const uint8*>(input.c_str()), input.size());
    uint8 hash[SHA256Impl::DIGEST_SIZE];
    impl.final(hash);
    std::stringstream ss;
    for (size_t i = 0; i < SHA256Impl::DIGEST_SIZE; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

}  // namespace antennacalc
