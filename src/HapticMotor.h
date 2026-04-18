#pragma once
#include <Arduino.h>

class HapticMotor {
public:
    // Up to 2 motor pins can be driven in parallel (e.g. two motors on one side).
    HapticMotor(uint8_t pin1, uint8_t pin2 = 255);

    void begin();

    void setLevel(uint8_t level); // 0–255
    uint8_t getLevel() const { return _level; }

private:
    uint8_t _pin1;
    uint8_t _pin2;
    uint8_t _level;
};
