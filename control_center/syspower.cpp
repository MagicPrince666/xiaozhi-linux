#include <sstream>
#include <fstream>
#include "syspower.h"

SysPower::SysPower(std::string dev) : device_(dev)
{
#if defined(__linux__)
    capacity_ = "/sys/class/power_supply/" + dev + "/capacity";
    voltage_now_ = "/sys/class/power_supply/" + dev + "/voltage_now";
    current_now_ = "/sys/class/power_supply/" + dev + "/current_now";
    status_ = "/sys/class/power_supply/" + dev + "/status";
#endif
}

SysPower::~SysPower() {
}

uint16_t SysPower::GetCapacity()
{
    uint16_t capacity = 0;
#if defined(__linux__)
    std::string cap_str = ReadFileIntoString(capacity_);
    capacity = atoi(cap_str.c_str());
#endif
    return capacity;
}

float SysPower::GetVoltageNow()
{
    float voltage_now = 0.0;
#if defined(__linux__)
    std::string vol_str = ReadFileIntoString(voltage_now_);
    voltage_now = atof(vol_str.c_str());
#endif
    return voltage_now;
}

bool SysPower::IsCharging()
{
    bool charging = false;
#if defined(__linux__)
    std::string status_str = ReadFileIntoString(status_);
    if (status_str.find("Charging") != std::string::npos) {
        // Charging / Discharging
        charging = true;
    }
#endif
    return charging;
}

std::string SysPower::ReadFileIntoString(const std::string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        return "";
    }
    std::stringstream buffer;
    buffer << input_file.rdbuf();
    std::string contents(buffer.str());
    input_file.close();
    return contents;
}
