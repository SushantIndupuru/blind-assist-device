#include "HapticMotor.h"

HapticMotor::HapticMotor(uint8_t pin1, uint8_t pin2)
    : _pin1(pin1), _pin2(pin2), _level(0) {
}

void HapticMotor::begin() {
    pinMode(_pin1, OUTPUT);
    analogWrite(_pin1, 0);
    if (_pin2 != 255) {
        pinMode(_pin2, OUTPUT);
        analogWrite(_pin2, 0);
    }
}

void HapticMotor::setLevel(uint8_t level) {
    _level = level;
    analogWrite(_pin1, _level);
    if (_pin2 != 255) {
        analogWrite(_pin2, _level);
    }
}
