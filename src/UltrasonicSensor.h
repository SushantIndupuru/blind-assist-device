#pragma once
#include <Arduino.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(uint8_t trigPin, uint8_t echoPin, const char *name,
                     uint8_t smoothingSamples = 3, unsigned long timeoutUs = 70000);

    void begin();

    // Take a new reading and update the smoothed average. Returns raw distance (cm), or -1 on timeout.
    float read();

    // Returns the current smoothed distance (cm), or -1 if no valid samples yet.
    float getSmoothedDistance() const;

    const char *getName() const { return _name; }

private:
    uint8_t _trigPin;
    uint8_t _echoPin;
    const char *_name;
    unsigned long _timeoutUs;

    uint8_t _smoothingSamples;
    float *_history;
    uint8_t _historyIndex;

    float _readRaw();

    float _computeSmoothed() const;
};
