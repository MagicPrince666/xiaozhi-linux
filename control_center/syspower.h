#ifndef __SYS_POWER_H__
#define __SYS_POWER_H__

#include <iostream>

class SysPower {
public:
    SysPower(std::string dev = "battery");
    ~SysPower();

    /**
     * @brief 获取电量
     * 
     * @return uint16_t 
     */
    uint16_t GetCapacity();

    /** 获取当前电压
    */
    float GetVoltageNow();

    /**
     * @brief 是否充电中
     * 
     * @return true 
     * @return false 
     */
    bool IsCharging();

private:
    std::string device_;
    std::string capacity_;
    std::string voltage_now_;
    std::string current_now_;
    std::string status_;

    std::string ReadFileIntoString(const std::string& path);
};

#endif
